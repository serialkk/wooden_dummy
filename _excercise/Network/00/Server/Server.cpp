//#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <process.h>
#include <list>
#pragma comment(lib, "ws2_32.lib")

using namespace std;



CRITICAL_SECTION cs;


typedef struct _TUser {
	SOCKET client;
	SOCKADDR_IN  clientaddr;
} TUser;

list<TUser*> g_listUser;

UINT WINAPI ClientThread(LPVOID arg)
{
	TUser* user = (TUser*)arg;
	//SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	char buf2[256] = { 0, };
	//printf("\n ���� ������ �Է��Ͻÿ�?");
	//SOCKADDR_IN  clientaddr;
	int length = 0;
	
	while (1)
	{

		ZeroMemory(&buf, sizeof(char) * 256);
		ZeroMemory(&buf2, sizeof(char) * 256);
		length = 0;
		int iRecvByte = recv(user->client, buf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("IP:[%s]: Ŭ���̾�Ʈ ���� ����\n", inet_ntoa(user->clientaddr.sin_addr));
			//printf("Ŭ���̾�Ʈ ���� ���� : IP:%s, PORT:%d\n",
			//	inet_ntoa(clientaddr.sin_addr),
			//	ntohs(clientaddr.sin_port));

			break; // Ŭ���̾�Ʈ ����
		}
		strcpy(buf2, "[");
		strcat(buf2, inet_ntoa(user->clientaddr.sin_addr));
		strcat(buf2, "]");
		strcat(buf2, ":");
		strcat(buf2, buf);

		strcat(buf2, "\0");
		length = strlen(buf2);
		//buf[length] = 0;
		printf("%s\n", buf2);

		EnterCriticalSection(&cs);
		list<TUser*>::iterator _F = g_listUser.begin();
		list<TUser*>::iterator _L = g_listUser.end();

		for (; _F != _L; ++_F)
		{
			if((*_F)!=0){
				int iSendByte = send((*_F)->client, buf2, length, 0);
			}
		}
		LeaveCriticalSection(&cs);

		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("IP:[%s]: Ŭ���̾�Ʈ ���� ����\n", inet_ntoa(user->clientaddr.sin_addr));
			


			break; // Ŭ���̾�Ʈ ����

		}
	}

	EnterCriticalSection(&cs);
	list<TUser*>::iterator _F = g_listUser.begin();
	list<TUser*>::iterator _L = g_listUser.end();

	for (; _F != _L; ++_F)
	{
		if (user == (*_F)) {
			closesocket((*_F)->client);
			delete (*_F);
			*_F = 0;
		}
	}
	LeaveCriticalSection(&cs);


	//closesocket(user->client);
	//delete user;

	return 0;
}

// ���� ����
// ������, TCP��������(SOCK_STREAM,IPPROTO_TCP)
// �񿬰���, UDP ��������(SOCK_DGRAM,IPPROTO_UDP)
int main(int argc, char* argv[])
{

	InitializeCriticalSection(&cs);
	/*if (argc != 2)
	{
	printf("\n[�����] xxx.exe [port]");
	printf("\n[��뿹��] xxx.exe 10000");
	return 1;
	}*/
	unsigned short iPort = 10000;// atoi(argv[1]);
								 // ������ ����(����) �ʱ�ȭ
	WSADATA wsa;
	int iRet;
	HANDLE hThread;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }
	{
		SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
		{
			SOCKADDR_IN sa;
			ZeroMemory(&sa, sizeof(sa));
			sa.sin_family = AF_INET;
			sa.sin_port = htons(iPort);
			sa.sin_addr.s_addr = htonl(INADDR_ANY);
			// ������ ��� ip�� �����ض�.
			iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
			if (iRet == SOCKET_ERROR) return -1;
			iRet = listen(listenSock, SOMAXCONN);
			if (iRet == SOCKET_ERROR) return -1;
			//SOCKADDR_IN  clientaddr;
			//SOCKET client;
			while (1)
			{
				TUser* user = new TUser;

				int addlen = sizeof(user->clientaddr);
				user->client = accept(listenSock, (SOCKADDR*)&(user->clientaddr), &addlen);
				printf("IP:[%s], PORT:[%d], Ŭ���̾�Ʈ ����\n",
					inet_ntoa(user->clientaddr.sin_addr), ntohs(user->clientaddr.sin_port));

				g_listUser.push_back(user);

				DWORD dwRecvThreadID;
				hThread = (HANDLE)_beginthreadex(0, 0,
					ClientThread,
					(LPVOID)user,
					0,
					(unsigned int*)&dwRecvThreadID);

				EnterCriticalSection(&cs);
				list<TUser*>::iterator _F = g_listUser.begin();
				while (_F != g_listUser.end())
				{
					if (*_F == 0) {

						_F = g_listUser.erase(_F);
					}
					else {
						_F++;
					}
				}
				LeaveCriticalSection(&cs);

			}
		}
		closesocket(listenSock);
	}
	// ������ ���� �Ҹ�
	iRet = WSACleanup();
	return iRet;
}