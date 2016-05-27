#pragma once
#include "TThread.h"
#include "TStream.h"

class TPoolPacket : public TSingleton<TPoolPacket>, 
	   public TThread
{
private:
	friend  class TSingleton<TPoolPacket>;
	std::list<T_PACKET>  m_RecvList;
	std::list<T_PACKET>  m_SendList;
public:
	void    AddPacket(T_PACKET packet);
	bool	Run();
public:
	TPoolPacket();
	virtual ~TPoolPacket();
};
#define I_Pool  TPoolPacket::GetInstance()
