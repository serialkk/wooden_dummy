#include "KSelect.h"

bool KSelect::RemoveSession(KUser* pUser)
{
	closesocket(pUser->m_Socket);
	pUser->m_isConnect = FALSE;
	pUser->m_dwSessionID = 0;
	pUser->m_Socket = INVALID_SOCKET;
	printf("\n ip=%s, port=%d 나감!",
		inet_ntoa(pUser->m_UserAddress.sin_addr),
		ntohs(pUser->m_UserAddress.sin_port));
	return true;
}
KUser* KSelect::GetSession()
{
	for (int icnt = 0; icnt < 64; icnt++)
	{
		if (!m_SessionList[icnt].m_isConnect)
		{
			m_SessionList[icnt].m_dwSessionID = icnt;
			return &m_SessionList[icnt];
		}
	}
	return NULL;
}
bool	KSelect::InitSelectServer()
{
	if (KNetwork::Init()==true)
	{
		SOCKADDR_IN server;
		ZeroMemory(&server, sizeof(SOCKADDR_IN));
		server.sin_family = AF_INET;
		server.sin_port = htons(10000);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		int iRet = bind(m_Sock, (SOCKADDR*)&server, sizeof(server));
		if (iRet == SOCKET_ERROR)  return false;
		iRet = listen(m_Sock, SOMAXCONN);
		if (iRet == SOCKET_ERROR)  return false;
		u_long on = TRUE;
		iRet = ioctlsocket(m_Sock, FIONBIO, &on);
		if (iRet == SOCKET_ERROR)  return false;
	}
	return true;
};
bool KSelect::Run()
{
	FD_SET     rSet;
	FD_SET     wSet;
	SOCKADDR_IN	clientaddr;
	SOCKET		client_sock;
	int			addrlen;

	// (1)초기화
	FD_ZERO(&rSet);
	FD_ZERO(&wSet);
	// (2)세팅
	FD_SET( m_Sock, &rSet);
	for (std::list<KUser*>::iterator itor = m_pUserList.begin();
		itor != m_pUserList.end();
			itor++)
	{
		KUser* pUser = (KUser*)*itor;
		FD_SET(pUser->m_Socket, &rSet);
		if (pUser->m_SendPacketList.size() > 0)
		{
			FD_SET(pUser->m_Socket, &wSet);
		}
	}
	// (3) Select함수 호출
	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 1;

	int iRet = select(0, &rSet, &wSet, NULL, &time);
	if (iRet == SOCKET_ERROR) return false;
	// 정상적인 처리
	if( iRet > 0 )
	{
		// (4) 네트워크 이벤트가 누구냐?
		if (FD_ISSET(m_Sock, &rSet))
		{
			addrlen = sizeof(clientaddr);
			client_sock = accept(m_Sock,(SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET)
			{
				if ( WSAGetLastError() != WSAEWOULDBLOCK)
				{
					return false;
				}				
			}
			else
			{
				KUser* pUser = GetSession();
				pUser->m_dwPort = ntohs(clientaddr.sin_port);
				pUser->m_Socket = client_sock;
				pUser->m_isConnect = TRUE;
				pUser->m_UserAddress = clientaddr;
					printf("\n ip=%s, port=%d",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port));
				m_pUserList.push_back(pUser);
			}
		}
		for (std::list<KUser*>::iterator itor = m_pUserList.begin();itor != m_pUserList.end();	itor++)
		{
			KUser* pUser = (KUser*)*itor;
			if (FD_ISSET(pUser->m_Socket, &rSet))
			{
				// recv
				char buf[1024] = { 0, };
				iRet = recv(pUser->m_Socket, buf, 1024, 0);// > 0)
				// 에러 또는 클라이언트 종료
				if (iRet == SOCKET_ERROR || iRet == 0 )
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						return false;
					}
					else
					{
						RemoveSession(pUser);
					}
				}
				else
				{
					pUser->m_RecvStreamPacket.Put(buf, iRet, pUser);
				}
			}
			else if (FD_ISSET(pUser->m_Socket, &wSet))
			{
				for (std::list<UPACKET>::iterator itor = pUser->m_SendPacketList.begin();
						itor != pUser->m_SendPacketList.end();itor++)
				{
					UPACKET packet = (UPACKET)*itor;
					int iRet = send(pUser->m_Socket,(char*)&packet, packet.ph.len, 0);
					if (iRet == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							return false;
						}
						break;
					}
					else
					{
						pUser->m_SendPacketList.erase(itor);
						if (pUser->m_SendPacketList.size() <= 0) break;
					}
				}
			}
		}
	}	
	
	return true;
}
KSelect::KSelect()
{
}


KSelect::~KSelect()
{
}
