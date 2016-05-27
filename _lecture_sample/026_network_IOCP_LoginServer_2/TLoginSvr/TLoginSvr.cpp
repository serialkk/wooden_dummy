// TLoginSvr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TLoginSvr.h"
#include "TSynchronize.h"
#include "TServerIOCP.h"
#include "TLoginPool.h"

void      TLoginUser::AddPacket(T_PACKET& tPacket)
{
	I_Pool.AddPacket(tPacket);
}

void      TLoginUser::Delete()
{
	closesocket(this->m_sock);
	I_Login.DelUser(this);
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
void  TLoginSvr::Broadcastting(UPACKET* pPacket)
{
	{
		TSynchronize sync(this);
		std::list<TLoginUser*>::iterator iter;
		for (iter = m_tUserList.begin();
			iter != m_tUserList.end();
			iter++)
		{
			DWORD dwSendByte;
			TLoginUser* pUser = (TLoginUser*)*iter;
			
			pUser->m_szWsaBuf.buf = (CHAR *)pPacket;
			pUser->m_szWsaBuf.len = pPacket->ph.len;
			pUser->m_ov.iFlag = OVERLAPPEDEX::MODE_SEND;

			T_PACKET* P = (T_PACKET*)pUser->m_szWsaBuf.buf;

			int iRet = WSASend(pUser->m_sock,
				&(pUser->m_szWsaBuf),
				1,
				&dwSendByte,
				0,
				(LPOVERLAPPED)&pUser->m_ov,
				NULL);
		}
	}
}

TLoginSvr::~TLoginSvr()
{
	I_iocp.Release();
}


int main()
{
	I_Pool.CreateThread();
	I_Login.Set(10000);
	while (I_Login.m_bStarted);
	return 0;
}

