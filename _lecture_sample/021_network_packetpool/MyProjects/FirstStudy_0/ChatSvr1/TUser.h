#pragma once
#include "TStreamPacket.h"
class TUser
{
public:
	TStreamPacket  m_RecvSP;
	bool   bConnect;
	SOCKET sock;
	SOCKADDR_IN clientAddr;
public:
	void RecvProcess( char* pbuffer, int iRecvSize)
	{}
	TUser();
	virtual ~TUser();
};

