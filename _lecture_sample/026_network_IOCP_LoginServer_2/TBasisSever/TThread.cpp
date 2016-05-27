#include "TThread.h"

unsigned int WINAPI TThread::HandleRunner(LPVOID parameter)
{
	TThread* pThread = (TThread*)parameter;
	if (pThread) pThread->Run();
	return 0;
};
bool      TThread::Run()
{
	return true;
}
void	  TThread::CreateThread()
{
	if (m_bStarted) return;
	m_hThread = _beginthreadex(NULL, 0, HandleRunner,
		(LPVOID)this, 0, &m_iThreadID);
	m_bStarted = true;
}


TThread::TThread()
{
	m_hThread =0;
	m_iThreadID=0;
	m_bStarted = false;
}


TThread::~TThread()
{
	CloseHandle((HANDLE)m_hThread);
}
