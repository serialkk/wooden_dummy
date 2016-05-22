#pragma once
#include "KPacketPool.h"
#include "KStreamPacket.h"

class KUser
{
public:
	BOOL		m_isConnect;
	DWORD		m_dwSessionID;
	SOCKET		m_Socket;
	SOCKADDR_IN m_UserAddress;
	C_STR		m_szIP;
	DWORD       m_dwPort;
	T_STR		m_szName;
	DWORD		m_dwRecvThreadID;
	HANDLE		m_hThread;
public:
	TStreamPacket		m_RecvStreamPacket;
	std::list<UPACKET>	m_SendPacketList;
public:
	KUser();
	virtual ~KUser();
};

