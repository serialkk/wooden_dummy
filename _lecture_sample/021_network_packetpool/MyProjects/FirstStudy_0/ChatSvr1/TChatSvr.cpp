#include "stdafx.h"
#include "TChatSvr.h"

DWORD WINAPI ClientThread(LPVOID data)
{
	TUser* tUser = (TUser*)data;
	SOCKET sock = tUser->sock;
	char szBuffer[MAX_RECV_BUFFER] = { 0, };
	ZeroMemory(szBuffer, sizeof(char)* MAX_RECV_BUFFER);

	int  iRecvData = 0;
	bool bConnect = true;
	while (bConnect)
	{
		int iRet = recv(sock, szBuffer,
			MAX_RECV_BUFFER, 0);
		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			bConnect = false;
			break;
		}
		tUser->RecvProcess(szBuffer, iRet);
		Sleep(1);
	}

	EnterCriticalSection(&I_CharSvr.g_crit);
	UPACKET pack;
	pack.ph.len = PACKET_HEADER_SIZE + sizeof(CHARACTER_INFO);
	pack.ph.type = PACKET_CHAR_DROP;

	CHARACTER_INFO info;
	info.iData[0] = 888;
	info.iIndex = 999;
	strcpy_s(info.szName, "홍길동");
	memcpy(pack.msg, &info, sizeof(info));

	I_CharSvr.BroadCastting(tUser, &pack);

	I_CharSvr.UserDel(tUser);
	LeaveCriticalSection(&I_CharSvr.g_crit);
	return 0;
}
DWORD WINAPI PacketThread(LPVOID data)
{
	//// g_PacketPool[n] -=> process
	//while (1)
	//{
	//	for (g_PacketPool; 30)
	//	{

	//	}
	//	Sleep(1000);
	//}
	return 1;
}
bool TChatSvr::Init()
{
	// 보내는 하인 등용
	DWORD dwPacketThreadID;
	CloseHandle(CreateThread(0,
		0, PacketThread, 0, 0,
		&dwPacketThreadID));
	return true;
}
bool TChatSvr::Set(short iPort)
{
	InitializeCriticalSection(&g_crit);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}
	
	//             주소체계, 소켓타입,  프로토콜 지정.
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	//inet_pton() or InetPton()
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr("127.0.0.1");
	int iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	long iNum = 0x7fffffff;
	// 동시에 접속하는 유저의 개수
	iRet = listen(listenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;
};
bool TChatSvr::Run() 
{
	SOCKADDR_IN clientAddr;
	SOCKET  client;
	while (1)
	{
		int addlength = sizeof(clientAddr);
		//accept는 접속되어야만 반환한다.
		//블록형 함수
		client = accept(listenSock,
			(SOCKADDR*)&clientAddr,
			&addlength);
		printf("\nClient Connect! ip = %s, port=%d",
			inet_ntoa(clientAddr.sin_addr),
			ntohs(clientAddr.sin_port));

		TUser* pUser = new TUser;
		pUser->sock = client;
		pUser->clientAddr = clientAddr;
		DWORD dwSendThreadID;

		UPACKET pack;
		pack.ph.len = PACKET_HEADER_SIZE;
		pack.ph.type = PACKET_CHAR_JOIN;

		int iSendbyte = send(client,
			(char*)&pack,
			pack.ph.len, 0);

		g_UserList.push_back(pUser);
		// 보내는 하인 등용
		CloseHandle(CreateThread(0,
			0, ClientThread, (LPVOID)pUser, 0,
			&dwSendThreadID));
	}	
	return true;
};
bool TChatSvr::Release() {
	closesocket(listenSock);
	// 윈속 해제
	WSACleanup();
	DeleteCriticalSection(&g_crit);
	return true;
};
void TChatSvr::BroadCastting(TUser* pSendUser, UPACKET* pPacket)
{
	EnterCriticalSection(&g_crit);
	{
		int iUserCnt = 0;
		for (std::list<TUser*>::iterator itor =
			g_UserList.begin();
			itor != g_UserList.end();
			itor++)
		{
			TUser* user = *itor;
			//if (user->sock == pSendUser->sock) continue;
			if (user->bConnect == false) continue;
			int iSendbyte = send(user->sock,
				(char*)pPacket,
				pPacket->ph.len, 0);
			if (iSendbyte == SOCKET_ERROR)
			{
				printf("\nClient Exit = [%s]",
					inet_ntoa(user->clientAddr.sin_addr));
				break;
			}
			printf("\nSend=[%d][%d][%d][%d]",
				ntohs(user->clientAddr.sin_port),
				pPacket->msg,
				pPacket->ph.type,
				pPacket->ph.len);
		}
	}
	LeaveCriticalSection(&g_crit);
}
void TChatSvr::PacketProcess(TUser* pUser, UPACKET* pPacket)
{	
}
int TChatSvr::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(UPACKET));
	sendmsg.ph.type = type;
	sendmsg.ph.len = PACKET_HEADER_SIZE + strlen(msg);
	memcpy(sendmsg.msg, msg, strlen(msg));

	int iSendbyte =
		send(sock, (char*)&sendmsg,
			sendmsg.ph.len, 0);
	printf("\nSendMessage = %s[%d]", msg,
		strlen(msg));
	return iSendbyte;
}
void TChatSvr::UserDel(TUser	*pUser)
{
	typedef std::list<TUser*>::iterator ITOR;
	ITOR itor;
	for (itor =
		g_UserList.begin();
		itor != g_UserList.end();
		itor++)
	{
		TUser* user = *itor;
		if (user->sock == pUser->sock)
			break;
	}
	TUser* user = *itor;
	closesocket(user->sock);
	delete user;
	g_UserList.erase(itor);
}
TChatSvr::TChatSvr()
{
}
TChatSvr::~TChatSvr()
{
}


