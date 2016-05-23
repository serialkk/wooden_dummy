#pragma once
#include <windows.h>
#include <tchar.h>
#define  MAX_WORK_THREAD 4
#define  MAX_BUFFER_SIZE 1000
#define  ASYNCFLAG_READ  0
#define  ASYNCFLAG_WRITE 1

typedef struct OVERLAPPED_ex : OVERLAPPED
{
	DWORD  flag;// ASYNCFLAG_READ, ASYNCFLAG_WRITE
}OVERLAPPEDEX, *LPOVERLAPPEDEX;

class Tiocp
{
public:
	HANDLE		m_hIOCP;// 입출력완료포트 핸들
	HANDLE		m_hThread[MAX_WORK_THREAD];
	HANDLE		m_hRead;
	HANDLE		m_hWrite;
	OVERLAPPEDEX m_ovRead;
	OVERLAPPEDEX m_ovWrite;
	char		 m_szBuffer[MAX_BUFFER_SIZE];
	HANDLE		m_hKillEvent;
public:
	static  DWORD WINAPI WorkerThread(LPVOID parm);
	bool		Init();
	void		Run();
	bool		WaitForRead();
	bool		DispatchRead(DWORD dwByte);
	bool		DispatchWrite(DWORD dwByte);
public:
	Tiocp();
	virtual ~Tiocp();
};

