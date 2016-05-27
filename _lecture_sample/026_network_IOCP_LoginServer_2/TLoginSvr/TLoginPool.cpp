#include "stdafx.h"
#include "TLoginPool.h"
#include "TLoginProtocol.h"
#include "TLoginSvr.h"
void TLoginPool::ProcessWork( T_PACKET*	pData)
{
	switch(pData->packet.ph.type)
	{
		case PACKET_CHAR_MSG:
		{
			I_Login.Broadcastting(&pData->packet);
		}break;
	}
}

TLoginPool::TLoginPool()
{
}


TLoginPool::~TLoginPool()
{
}
