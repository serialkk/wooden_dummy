#pragma once
#include "TSeverStd.h"
class TPacketPool
{
	std::list<UPACKET>  g_PacketPool;
public:
	TPacketPool();
	virtual ~TPacketPool();
};

