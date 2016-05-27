#include "TAcceptor.h"
#include "TPoolPacket.h"
bool	 TAcceptor::AddUser(SOCKET sock, SOCKADDR_IN address)
{
	return true;
}

bool      TAcceptor::Run()
{
	SOCKET client = { 0, };
	SOCKADDR_IN address = { 0, };
	int addlen = sizeof(address);
	while(m_bStarted)
	{
		client = accept(m_ListenSock, (SOCKADDR*)&address,
			&addlen);
		if( client != INVALID_SOCKET)
		{			
			AddUser(client, address);
		}
		if (SwitchToThread() == FALSE)
		{
			Sleep(1);
			// 0 동일한 우선순위 스위칭 가능
			// 1 서로 다른 우선순위 스위칭 가능
		}
	}
	return true;
}
bool	TAcceptor::Set(int iPort, 
					const char* strAddress )
{
	I_Pool.CreateThread();
	// 윈속 초기화
	int iRet;
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);
	this->m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sd = { 0, };
	sd.sin_family = AF_INET;
	if (strAddress== NULL)
	{
		sd.sin_addr.s_addr = htonl(INADDR_ANY);
	}else
	{ 
		sd.sin_addr.s_addr = inet_addr(strAddress);
	}
	sd.sin_port = htons(iPort);
	// 소켓생성,, bind, listen
	bind(m_ListenSock, (SOCKADDR*)&sd, sizeof(SOCKADDR));
	listen(m_ListenSock, SOMAXCONN);
	CreateThread();
	return true;
};
TAcceptor::TAcceptor()
{
}


TAcceptor::~TAcceptor()
{
}
