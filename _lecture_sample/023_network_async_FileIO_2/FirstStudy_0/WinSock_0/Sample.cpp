#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
// 소켓 프로그래밍
void main()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0 )
	{
		return;
	}
	SOCKET  sock;
	//             주소체계, 소켓타입,  프로토콜 지정.
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family= AF_INET;
	//inet_pton() or InetPton()
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	int iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	char szBuffer[MAX_PATH] = { 0, };
	while (1)
	{
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		fgets(szBuffer, MAX_PATH, stdin);
		int iMessageSize = strlen(szBuffer);
		int iSendbyte = send(sock, szBuffer, iMessageSize, 0);
		printf("\nSendMessage = %s[%d]", szBuffer,
			iMessageSize);
		int iRecvByte = recv(sock, szBuffer, strlen(szBuffer) , 0);
		if (iRecvByte == 0)
		{
			printf("\nServer DisConnect!");
			break;
		}
		printf("\nRecvMessage = %s[%d]", szBuffer,
			strlen(szBuffer));
	}
	_getch();
	// 윈속 해제
	WSACleanup();
}


