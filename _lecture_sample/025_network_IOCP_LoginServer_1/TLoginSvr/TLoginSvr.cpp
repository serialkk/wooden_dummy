// TLoginSvr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TLoginSvr.h"
#include "TSynchronize.h"
#include "TServerIOCP.h"

TLoginSvr  svr;
void      TLoginUser::Delete()
{
	closesocket(this->m_sock);
	svr.DelUser(this);
}
void      TLoginUser::Create()
{
	ZeroMemory(&m_ov, sizeof(m_ov));
	WaitForpacketReceive();
}
void      TLoginUser::WaitForpacketReceive()
{
	DWORD  dwTrans, flag = 0;
	m_ov.iFlag = OVERLAPPEDEX::MODE_RECV;
	m_szWsaBuf.buf = m_szBuffer;
	m_szWsaBuf.len = 4096;	
	int iRet = WSARecv(m_sock, &m_szWsaBuf, 1,  &dwTrans, &flag,
		  (LPOVERLAPPED)&m_ov, NULL );
	if( iRet == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			int k = 0;
		}
	}

}
bool  TLoginSvr::AddUser(SOCKET sock, SOCKADDR_IN address)
{
	{
		TSynchronize sync(this);
		TLoginUser* pUser = new TLoginUser;
		m_tUserList.push_back(pUser);
		I_iocp.AddHandleToIOCP((HANDLE)sock, (DWORD)pUser);		
		pUser->m_sock = sock;
		pUser->m_Address = address;
		pUser->Create();
	}
	return true;
}
bool  TLoginSvr::DelUser(TUser* pUser)
{
	{
		TSynchronize sync(this);	
	}
	return true;
}
TLoginSvr::TLoginSvr()
{
	I_iocp.Init();
}


TLoginSvr::~TLoginSvr()
{
	I_iocp.Release();
}


int main()
{
	
	svr.Set(10000);
	while (svr.m_bStarted);
	return 0;
}

