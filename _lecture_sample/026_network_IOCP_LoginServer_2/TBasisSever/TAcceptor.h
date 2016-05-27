#pragma once
#include "TThread.h"
class TAcceptor : public TThread
{
public:
	SOCKET		m_ListenSock;
public:
	bool		Run();
	bool		Set( int iPort, const char* strAddress = 0);
	virtual bool	AddUser(SOCKET sock, SOCKADDR_IN address );
public:
	TAcceptor();
	virtual ~TAcceptor();
};

// �α��� ���� 
// class TLoginSvr : public TAcceptor
// class TUpdateSvr : public TAcceptor
// class TNPCSvr : public TAcceptor
// class TGameSvr : public TAcceptor
// class TDBSvr : public TAcceptor