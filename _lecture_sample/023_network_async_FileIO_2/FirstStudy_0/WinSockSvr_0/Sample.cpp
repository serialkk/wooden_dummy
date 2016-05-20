#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
// 소켓 프로그래밍
void main()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET  sock;
	//             주소체계, 소켓타입,  프로토콜 지정.
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	//inet_pton() or InetPton()
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr("127.0.0.1");
	int iRet = bind(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	long iNum = 0x7fffffff;
	// 동시에 접속하는 유저의 개수
	iRet = listen(sock, SOMAXCONN);
	if(iRet == SOCKET_ERROR)
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
		client = accept(sock,
			(SOCKADDR*)&clientAddr, 
			&addlength);
		printf("\nClient Connect! ip = %s, port=%d",
			inet_ntoa(clientAddr.sin_addr),
			ntohs(clientAddr.sin_port));

		char szBuffer[MAX_PATH] = { 0 };
		while (1)
		{
			ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
			//recv는 데이터를 보내줘야만 반환한다.
			//블록형 함수
			int iRecvByte = recv(client,
				szBuffer, sizeof(char)*MAX_PATH, 0);
			if (iRecvByte == SOCKET_ERROR)
			{
				break;
			}
			if (iRecvByte == 0)
			{
				printf("\nClient DisConnect! ip = %s, port=%d",
					inet_ntoa(clientAddr.sin_addr),
					ntohs(clientAddr.sin_port));
				break;
			}
			printf("\nRecv Message = %s[%d]", 
				szBuffer, strlen(szBuffer));
			int iSendByte = send(client,
				szBuffer, strlen(szBuffer), 0);
			if (iSendByte == SOCKET_ERROR)
			{
				break;
			}
			printf("\nSend Message = %s[%d]", 
				szBuffer, strlen(szBuffer));
		}

	}
	// 윈속 해제
	WSACleanup();
}


