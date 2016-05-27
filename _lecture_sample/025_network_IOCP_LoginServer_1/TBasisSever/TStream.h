#pragma once
#include "TServerStd.h"
#include "TProtocol.h"

class TUser;
struct T_PACKET
{
	UPACKET  Data;
	TUser*   pUser;
};
class TStream //: public TServerObj
{
public:
	void  Put(char* pBuffer, DWORD dwSize, TUser* pUser);
public:
	TStream();
	virtual ~TStream();
};

