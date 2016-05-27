#pragma once
#include "TAcceptor.h"
#include "TUser.h"

class TLoginUser : public TUser
{
public:
	void      Create();
	void      Delete();
	void      AddPacket(T_PACKET& tPacket);
	void      WaitForpacketReceive();
public:
	TLoginUser() {}
	~TLoginUser() {}
};

class TLoginSvr : public TAcceptor,
	 public TSingleton<TLoginSvr>
{
private:
	friend class TSingleton<TLoginSvr>;
public:
	std::list<TLoginUser*>  m_tUserList;
public:
	bool  AddUser(SOCKET sock, SOCKADDR_IN address);
	bool  DelUser(TUser* pUser);
	void  Broadcastting(UPACKET* pPacket);
public:
	TLoginSvr();
	virtual ~TLoginSvr();
};
#define I_Login TLoginSvr::GetInstance()
