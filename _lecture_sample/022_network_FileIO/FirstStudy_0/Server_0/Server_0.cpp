// Server_0.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
// ����ȭ ��ü
CRITICAL_SECTION    g_crit;

void BroadCastting( TUser* pSendUser, UPACKET* pPacket)
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
	// 1���� ��Ŷ�� �ϼ�
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
	for ( itor =
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
DWORD WINAPI ClientThread(LPVOID data)
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
			// �ϼ��� ��Ŷ�� ���� ó��
			PacketProcess(tUser,pPacket);
			iRecvData = 0;
		}
		Sleep(1);
	}
	
	EnterCriticalSection(&g_crit);
	UPACKET pack;
	pack.ph.len = PACKET_HEADER_SIZE+sizeof(CHARACTER_INFO);
	pack.ph.type = PACKET_CHAR_DROP;

	CHARACTER_INFO info;
	info.iData[0] = 888;
	info.iIndex = 999;
	strcpy_s( info.szName, "ȫ�浿");
	memcpy(pack.msg, &info, sizeof(info));

	BroadCastting(tUser, &pack);

	UserDel(tUser);
	LeaveCriticalSection(&g_crit);
	return 0;
}
// ���� ���α׷���
void main()
{
	InitializeCriticalSection(&g_crit);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET  listenSock;
	//             �ּ�ü��, ����Ÿ��,  �������� ����.
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
	// ���ÿ� �����ϴ� ������ ����
	iRet = listen(listenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return;
	}

	SOCKADDR_IN clientAddr;
	SOCKET  client;
	while (1)
	{
		int addlength = sizeof(clientAddr);
		//accept�� ���ӵǾ�߸� ��ȯ�Ѵ�.
		//����� �Լ�
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
		// ������ ���� ���
		CloseHandle(CreateThread(0,
			0, ClientThread, (LPVOID)pUser, 0,
			&dwSendThreadID));
	}
	closesocket(listenSock);
	// ���� ����
	WSACleanup();

	DeleteCriticalSection(&g_crit);
}



