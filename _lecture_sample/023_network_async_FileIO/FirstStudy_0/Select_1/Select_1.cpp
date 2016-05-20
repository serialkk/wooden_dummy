// Server_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <vector>
#include <list>
#include "tprotocol.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;

struct TUser
{
	bool   bConnect;
	SOCKET sock;
	SOCKADDR_IN clientAddr;
};
std::list<TUser*>   g_UserList;
// 동기화 객체
CRITICAL_SECTION    g_crit;

void BroadCastting(TUser* pSendUser, UPACKET* pPacket)
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
void  PacketProcess(TUser* pUser, UPACKET* pPacket)
{
	// 1개의 패킷이 완성
	switch (pPacket->ph.type)
	{
	case PACKET_CHAR_MSG:
	{
		BroadCastting(pUser, pPacket);
		printf("\nRecvMessage=%s", pPacket->msg);
	}break;
	}
}
int SendMsg(SOCKET sock, char* msg, WORD type)
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
void UserDel(TUser	*pUser)
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
DWORD UserRecv(LPVOID data)
{
	TUser* tUser = (TUser*)data;
	SOCKET sock = tUser->sock;
	char szBuffer[MAX_PATH] = { 0, };
	int  iRecvData = 0;
	bool bConnect = true;
	while (bConnect)
	{
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		int iRet = recv(sock, &szBuffer[iRecvData],
			PACKET_HEADER_SIZE - iRecvData, 0);
		iRecvData += iRet;
		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			bConnect = false;
			break;
		}
		if (iRecvData == PACKET_HEADER_SIZE)
		{
			UPACKET* pPacket = (UPACKET*)&szBuffer;
			// 5
			int iRecvSize = pPacket->ph.len - PACKET_HEADER_SIZE;
			// 4 < 9
			int iRet = 0;
			while (iRecvData < pPacket->ph.len)
			{
				iRecvSize -= iRet;
				iRet = recv(sock, &szBuffer[iRecvData],
					iRecvSize, 0);
				iRecvData += iRet;
				if (iRet == 0 || iRet == SOCKET_ERROR)
				{
					bConnect = false;
					break;
				}
			}
			// 완성된 패킷에 대한 처리
			PacketProcess(tUser, pPacket);
			iRecvData = 0;
		}
		Sleep(1);
	}

	//EnterCriticalSection(&g_crit);
	//UPACKET pack;
	//pack.ph.len = PACKET_HEADER_SIZE + sizeof(CHARACTER_INFO);
	//pack.ph.type = PACKET_CHAR_DROP;

	//CHARACTER_INFO info;
	//info.iData[0] = 888;
	//info.iIndex = 999;
	//strcpy_s(info.szName, "홍길동");
	//memcpy(pack.msg, &info, sizeof(info));

	//BroadCastting(tUser, &pack);

	//UserDel(tUser);
	//LeaveCriticalSection(&g_crit);
	return 0;
}
// 소켓 프로그래밍
void main()
{
	InitializeCriticalSection(&g_crit);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET  listenSock;
	//             주소체계, 소켓타입,  프로토콜 지정.
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	//inet_pton() or InetPton()
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr("127.0.0.1");
	int iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	long iNum = 0x7fffffff;
	// 동시에 접속하는 유저의 개수
	iRet = listen(listenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	

	SOCKADDR_IN clientAddr;
	SOCKET  client;
	FD_SET  rSet, wSet;

	while (1)
	{
		// 1 단계
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_SET(listenSock, &rSet);
		for (std::list<TUser*>::iterator itor =
			g_UserList.begin();
			itor != g_UserList.end();
			itor++)
		{
			TUser* user = *itor;			
			FD_SET(user->sock, &rSet);
		}

		timeval time;
		time.tv_sec = 0;
		time.tv_usec = 1;
		int iRet = select(0, &rSet, &wSet, NULL, &time);
		if (iRet == SOCKET_ERROR) return;
		if (iRet > 0)
		{
			if (FD_ISSET(listenSock, &rSet))
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
				g_UserList.push_back(pUser);
			}

			for (std::list<TUser*>::iterator itor =
				g_UserList.begin();
				itor != g_UserList.end();
				itor++)
			{
				TUser* user = *itor;
				if (FD_ISSET(user->sock, &rSet))
				{
					UserRecv(user);
				}
				if (FD_ISSET(user->sock, &wSet))
				{
					UserSend(user);
				}
			}
		}
	}
	closesocket(listenSock);
	// 윈속 해제
	WSACleanup();

	DeleteCriticalSection(&g_crit);
}



