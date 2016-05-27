#include "TPoolPacket.h"
#include "TSynchronize.h"

void    TPoolPacket::AddPacket(T_PACKET& packet)
{
	{
		TSynchronize sync(this);
		m_RecvList.push_back(packet);
	}
};
bool TPoolPacket::Run()
{
	while(m_bStarted)
	{
		TSynchronize sync(this);	
		std::list<T_PACKET>::iterator iter;
		for (iter = m_RecvList.begin();
			iter != m_RecvList.end();
			iter++)
		{
			T_PACKET* pData = (T_PACKET*)&(*iter);
			ProcessWork(pData);
		}
		m_RecvList.clear();
		Sleep(1);
	}
	return true;
}
void TPoolPacket::ProcessWork(T_PACKET* pData)
{

}
TPoolPacket::TPoolPacket()
{
}


TPoolPacket::~TPoolPacket()
{
}
