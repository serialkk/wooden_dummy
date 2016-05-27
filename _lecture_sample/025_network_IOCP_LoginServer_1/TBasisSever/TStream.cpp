#include "TStream.h"
#include "TPoolPacket.h"

void  TStream::Put(char* pBuffer, DWORD dwSize, TUser* pUser)
{
	UPACKET uPack;//tPacket.Data
	T_PACKET tPacket;
	tPacket.pUser = pUser;
	I_Pool.AddPacket(tPacket);
}
TStream::TStream()
{
}


TStream::~TStream()
{
}
