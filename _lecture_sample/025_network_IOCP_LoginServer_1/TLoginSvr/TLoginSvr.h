#pragma once
#include "TAcceptor.h"
#include "TUser.h"

class TLoginUser : public TUser
{
public:
	void      Create();
	void      Delete();
	void      WaitForpacketReceive();
public:
	TLoginUser() {}
	~TLoginUser() {}
};

class TLoginSvr : public TAcceptor
{
public:
	std::list<TLoginUser*>  m_tUserList;
public:
	bool  AddUser(SOCKET sock, SOCKADDR_IN address);
	bool  DelUser(TUser* pUser);
public:
	TLoginSvr();
	virtual ~TLoginSvr();
};

