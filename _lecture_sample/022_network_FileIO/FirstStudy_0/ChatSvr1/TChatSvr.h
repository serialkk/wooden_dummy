#pragma once
#include "TUser.h"
class TChatSvr : public TSingleton<TChatSvr>
{
public:
	SOCKET  listenSock;
	std::list<TUser*>   g_UserList;
	// µø±‚»≠ ∞¥√º
	CRITICAL_SECTION    g_crit;
public:
	bool		Init();
	bool		Set(short iPort);
	bool		Run();
	bool		Release();
	void BroadCastting(TUser* pSendUser, UPACKET* pPacket);
	void PacketProcess(TUser* pUser, UPACKET* pPacket);
	int SendMsg(SOCKET sock, char* msg, WORD type);
	void UserDel(TUser	*pUser);
public:
	TChatSvr();
	virtual ~TChatSvr();
};
#define I_CharSvr TChatSvr::GetInstance()
