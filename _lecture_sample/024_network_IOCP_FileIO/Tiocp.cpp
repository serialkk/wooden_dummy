#include "Tiocp.h"
DWORD WINAPI Tiocp::WorkerThread(LPVOID parm)
{
	Tiocp*  pIocp = (Tiocp*)parm;
	HANDLE  hIOCP = pIocp->m_hIOCP;
	DWORD  byteTransfer;
	ULONG_PTR   key;
	OVERLAPPEDEX*   ov;
	BOOL     rVal;
	while (1)
	{
		if (WaitForSingleObject( pIocp->m_hKillEvent, 1)
			==  WAIT_OBJECT_0 )
		{
			break;
		}
		rVal = GetQueuedCompletionStatus(
			hIOCP, 
			&byteTransfer,
			&key, 
			(LPOVERLAPPED*)&ov,
			1);
		if (rVal == TRUE)
		{
			if (byteTransfer != 0)
			{
				if (ov->flag == ASYNCFLAG_READ)
				{
					pIocp->DispatchRead(byteTransfer);
				}
				else if (ov->flag == ASYNCFLAG_WRITE)
				{
					pIocp->DispatchWrite(byteTransfer);
				}
			}
			else
			{
				// 작업 종료
				SetEvent(pIocp->m_hKillEvent);
			}
 
		}
		else
		{ 
			DWORD dwError = GetLastError();
			if (dwError == WAIT_TIMEOUT) continue;
			else
			{
				if(ov != NULL)
				{ 
					if (dwError == ERROR_HANDLE_EOF)
					{
						 //정상 종료
						SetEvent(pIocp->m_hKillEvent);
					}
				}
				else
				{
					 // 비정상 종료
					SetEvent(pIocp->m_hKillEvent);
				}
			}
		}
	}
	return 0;
};
bool		Tiocp::DispatchRead(DWORD dwByte)
{
	DWORD writeBytes = 0;
	if (WriteFile(m_hWrite, m_szBuffer, dwByte,
		&writeBytes,
		(LPOVERLAPPED)&m_ovWrite) == FALSE)
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_IO_PENDING &&
			dwError != ERROR_SUCCESS) {
			return false;
		}
	}
	
	LARGE_INTEGER  Li;
	Li.QuadPart = dwByte;
	m_ovRead.Offset += Li.LowPart;
	m_ovRead.OffsetHigh += Li.HighPart;

	if (WaitForRead() == false)
	{
		// 종료
		return false;
	}
	return true;
}
bool		Tiocp::DispatchWrite(DWORD dwByte)
{
	LARGE_INTEGER  Li;
	Li.QuadPart = dwByte;
	m_ovWrite.Offset += Li.LowPart;
	m_ovWrite.OffsetHigh += Li.HighPart;
	return true;
}
bool Tiocp::Init()
{
	// 1, IOCP 핸들 생성
	m_hIOCP = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE, 0,0,0);
	if (m_hIOCP == INVALID_HANDLE_VALUE)	{
		return false;
	}
	// 2, 작업장 쓰레드 생성( 쓰레드 풀)
	DWORD  id;
	for (int iThread = 0; iThread < MAX_WORK_THREAD; iThread++)
	{
		m_hThread[iThread] = CreateThread(0, 0, WorkerThread,
			this, 0, &id);
	}

	m_hKillEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
	::ResetEvent(m_hKillEvent);

	// 3, 핸들 생성
	m_hRead = ::CreateFile(L"data.dat",
		GENERIC_READ,
		0, 0, OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED | FILE_ATTRIBUTE_NORMAL, 0);
	if (m_hRead == INVALID_HANDLE_VALUE) return false;

	m_hWrite = ::CreateFile(L"datacopy.dat",
		GENERIC_WRITE,
		0, 0, CREATE_ALWAYS,
		FILE_FLAG_OVERLAPPED | FILE_ATTRIBUTE_NORMAL, 0);
	if (m_hWrite == INVALID_HANDLE_VALUE) return false;

	//4, 생성된 핸들 IOCP 핸들에 바인딩
	CreateIoCompletionPort(m_hRead, this->m_hIOCP, 
		1000, 0);
	CreateIoCompletionPort(m_hWrite, this->m_hIOCP, 
		(DWORD)m_hWrite, 0);
	return true;
}
void Tiocp::Run()
{
	ZeroMemory(&m_ovRead, sizeof(m_ovRead));
	ZeroMemory(&m_ovWrite, sizeof(m_ovRead));
	m_ovRead.flag = ASYNCFLAG_READ;
	m_ovWrite.flag = ASYNCFLAG_WRITE;
	WaitForRead();
	while(
		WaitForMultipleObjects(MAX_WORK_THREAD, m_hThread, TRUE, 1)
		);
}
bool  Tiocp::WaitForRead()
{
	DWORD readBytes = 0;
	DWORD bufSize = MAX_BUFFER_SIZE;
	if( ReadFile(m_hRead, m_szBuffer, bufSize, 
		&readBytes, 
		(LPOVERLAPPED)&m_ovRead ) == FALSE)
	{ 
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_PENDING) return true;
		return false;
		if (dwError != ERROR_IO_PENDING &&
			dwError != ERROR_SUCCESS)		{
			return false;
		}
	}
	else
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_HANDLE_EOF ||
			readBytes == 0)
		{
			return false;
		}
	}
	return true;
}
Tiocp::Tiocp()
{
}


Tiocp::~Tiocp()
{
	CloseHandle(m_hIOCP);
	CloseHandle(m_hRead);
	CloseHandle(m_hWrite);
}
