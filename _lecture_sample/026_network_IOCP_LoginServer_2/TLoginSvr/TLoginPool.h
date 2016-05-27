#pragma once
#include "TPoolPacket.h"
class TLoginPool : public TSingleton<TLoginPool>, public TPoolPacket
{
private:
	friend  class TSingleton<TLoginPool>;
public:
	void	ProcessWork(T_PACKET* pData);
public:
	TLoginPool();
	virtual ~TLoginPool();
};
#define I_Pool  TLoginPool::GetInstance()
