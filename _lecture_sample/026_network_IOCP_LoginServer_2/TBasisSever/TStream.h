#pragma once
#include "TServerStd.h"
#include "TProtocol.h"
#define MAX_RECV_SIZE 10000
class TUser;
struct T_PACKET
{
	UPACKET  packet;
	TUser*   pUser;
};
class TStream //: public TServerObj
{
public:
	UPACKET*			m_pPacket;
	char				m_RecvBuffer[MAX_RECV_SIZE];
	int					m_iStartPos;
	int					m_iWritePos;
	int					m_iReadPos;
public:
	void  Put(char* pBuffer, DWORD dwSize, TUser* pUser);
public:
	TStream();
	virtual ~TStream();
};

