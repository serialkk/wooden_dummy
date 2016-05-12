// Server_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <vector>
#include <list>
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
HANDLE g_hMutex = NULL;

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
DWORD WINAPI ClientThread(LPVOID data)
{
	TUser* tUser = (TUser*)data;
	SOCKET sock = tUser->sock;
	char szBuffer[MAX_PATH] = { 0, };

	DWORD iThID = GetCurrentThreadId();
	while (1)
	{
		printf("0->[%ld]", iThID);
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		int iRecvbyte = recv(sock, szBuffer, sizeof(char)* MAX_PATH, 0);
		if (iRecvbyte == 0 || iRecvbyte == SOCKET_ERROR)
		{
			tUser->bConnect = false;
			printf("\nClient Exit = [%s]",
				inet_ntoa(tUser->clientAddr.sin_addr));
			break;
		}
		printf("\n1->[%ld]", iThID);
		printf("\n[%s]:%s[%d]",
			inet_ntoa(tUser->clientAddr.sin_addr),
			szBuffer,
			iRecvbyte);

		WaitForSingleObject(g_hMutex, INFINITE);
		{
			int iUserCnt = 0;
			for (std::list<TUser*>::iterator itor =
				g_UserList.begin();
				itor != g_UserList.end();
				itor++)
			{
				printf("\n2->[%ld, %d]", iThID, iUserCnt++);
				TUser* user = *itor;
				if (user->bConnect == false) continue;
				int iSendbyte = send(user->sock,
					szBuffer, strlen(szBuffer), 0);
				if (iSendbyte == SOCKET_ERROR)
				{
					printf("\nClient Exit = [%s]",
						inet_ntoa(user->clientAddr.sin_addr));
					break;
				}
			}
		}
		ReleaseMutex(g_hMutex);
		printf("\n3->[%ld]", iThID);
	}

	WaitForSingleObject(g_hMutex, INFINITE);
	UserDel(tUser);
	ReleaseMutex(g_hMutex);
	return 0;
}
// 소켓 프로그래밍
void main()
{
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS,
		FALSE, L"KGCA");
	g_hMutex = CreateMutex(NULL, TRUE, _T("KGCA"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(g_hMutex);
		return;
	}
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

		g_UserList.push_back(pUser);
		// 보내는 하인 등용
		CloseHandle(CreateThread(0,
			0, ClientThread, (LPVOID)pUser, 0,
			&dwSendThreadID));
	}
	closesocket(listenSock);
	// 윈속 해제
	WSACleanup();

	CloseHandle(g_hMutex);
}



