#pragma once
#include "TWorkThread.h"
#define WORKER_THREAD_COUNT 2
class TServerIOCP : public TSingleton<TServerIOCP>, public TServerObj
{
	friend  class TSingleton<TServerIOCP>;
public:
	HANDLE          m_hIOCP;
	TWorkThread		m_WorkerThread[WORKER_THREAD_COUNT];
public:
	bool			Init();
	bool			Release();
	void			AddHandleToIOCP(
		HANDLE sock, 
		DWORD  dwKey);
public:
	TServerIOCP();
	virtual ~TServerIOCP();
};

#define I_iocp  TServerIOCP::GetInstance()