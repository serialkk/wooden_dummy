#include "TServerIOCP.h"

bool			TServerIOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(
	  INVALID_HANDLE_VALUE,
		0, 0, WORKER_THREAD_COUNT);
	for (int iThread = 0; iThread < WORKER_THREAD_COUNT; iThread++)
	{
		m_WorkerThread[iThread].CreateThread();
	}
	return true;
}
void			TServerIOCP::AddHandleToIOCP(
	HANDLE sock,
	DWORD  dwKey)
{
	::CreateIoCompletionPort(
		sock,
		m_hIOCP, 
		dwKey,
		0);
}
bool			TServerIOCP::Release()
{
	return true;
}

TServerIOCP::TServerIOCP()
{
}


TServerIOCP::~TServerIOCP()
{
}
