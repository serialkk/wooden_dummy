#include "TWorkThread.h"
#include "TServerIOCP.h"
#include "TUser.h"

bool		TWorkThread::Run()
{
	DWORD dwRet, dwTransfer;
	ULONG_PTR keyValue;
	LPOVERLAPPED ov;

	while (m_bStarted)
	{
		dwRet = ::GetQueuedCompletionStatus(I_iocp.m_hIOCP,
			&dwTransfer, &keyValue, &ov, INFINITE);
		TUser* pUser = (TUser*)keyValue;
		if( dwRet == TRUE)
		{
			if (dwTransfer == 0) {
				pUser->Delete();
			}
			pUser->Dispatch(dwTransfer, ov);
		}
		else
		{
			// 유저가 나갔거나
			// 어떤 오류나 출력하면 된다.
			// 오류가 있거나
			pUser->Delete();
		}

	}
	return true;
}

TWorkThread::TWorkThread()
{
}


TWorkThread::~TWorkThread()
{
}
