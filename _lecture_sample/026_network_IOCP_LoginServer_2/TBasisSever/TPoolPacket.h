#pragma once
#include "TThread.h"
#include "TStream.h"

class TPoolPacket :  public TThread
{
public:
	std::list<T_PACKET>  m_RecvList;
	std::list<T_PACKET>  m_SendList;
public:
	virtual void    AddPacket(T_PACKET& packet);
	virtual void	ProcessWork(T_PACKET* pData);
	bool	Run();
public:
	TPoolPacket();
	virtual ~TPoolPacket();
};

