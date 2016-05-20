// PacketClass.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TPacket.h"

struct TUserData
{
	// send
	int   iID;
	char  name[9];
	float fAve;
};
struct TUserData2
{
	// send	
	int   iID;
	int  dwError;
	char  name[9];
	DWORD dwError2;
	float fAve;
};
void SetUserPacket(TUserData data)
{
	TPacket packet;
	int iLen = sizeof(data) + 4;
	packet << iLen;
	packet << 3002;
	packet << data.iID << data.name << data.fAve;
}

int main()
{
	TUserData data = { 3, "홍길동", 34.3f };
	TPacket packet;
	packet << data.iID << data.name<< data.fAve ;

	TUserData2 recv;
	char buffer[30] = { 0, };
	packet >> recv.iID >> buffer >> recv.fAve;
	strcpy_s(recv.name, buffer );
    return 0;
}

