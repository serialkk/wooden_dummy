#include "TPoolPacket.h"
#include "TSynchronize.h"

void    TPoolPacket::AddPacket(T_PACKET packet)
{
	{
		TSynchronize sync(this);
		m_PacketList.push_back(packet);
	}
};
bool TPoolPacket::Run()
{
	{
		TSynchronize sync(this);		
	}
	return true;
}
TPoolPacket::TPoolPacket()
{
}


TPoolPacket::~TPoolPacket()
{
}
