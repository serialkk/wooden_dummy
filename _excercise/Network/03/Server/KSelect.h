#pragma once
#include "KNetwork.h"
#include "KUser.h"
class KSelect : public KNetwork
{
public:
	KUser			     m_SessionList[64];
	std::list<KUser*>	 m_pUserList;
public:
	bool	InitSelectServer();
	bool	Run();
	KUser*	GetSession();
	bool	RemoveSession(KUser* pUser);
public:
	KSelect();
	virtual ~KSelect();
};

