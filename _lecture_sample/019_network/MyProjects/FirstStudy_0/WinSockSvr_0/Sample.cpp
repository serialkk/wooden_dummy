#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
// ���� ���α׷���
void main()
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET  sock;
	//             �ּ�ü��, ����Ÿ��,  �������� ����.
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
	// ���ÿ� �����ϴ� ������ ����
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
		//accept�� ���ӵǾ�߸� ��ȯ�Ѵ�.
		//����� �Լ�
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
			//recv�� �����͸� ������߸� ��ȯ�Ѵ�.
			//����� �Լ�
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
	// ���� ����
	WSACleanup();
}


