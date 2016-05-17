#pragma once
#include "TServerStd.h"
#include "TProtocol.h"
class TUser;
#define MAX_RECV_SIZE 10000

class TStreamPacket
{
public:	
	UPACKET*			m_pPacket;
	char				m_RecvBuffer[MAX_RECV_SIZE];
	int					m_iStartPos;
	int					m_iWritePos;
	int					m_iReadPos;
public:
	void    Put(char* redvBuffer, int iSize, TUser* = NULL);
public:
	TStreamPacket();
	virtual ~TStreamPacket();
};

