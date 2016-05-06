#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
// ���� ����
// ������, TCP��������(SOCK_STREAM,IPPROTO_TCP)
// �񿬰���, UDP ��������(SOCK_DGRAM,IPPROTO_UDP)

UINT WINAPI ClientThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	//printf("\n ���� ������ �Է��Ͻÿ�?");
	SOCKADDR_IN  clientaddr;
	while (1)
	{
		ZeroMemory(&buf, sizeof(char) * 256);
		int iRecvByte = recv(sock, buf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("Ŭ���̾�Ʈ ���� ����\n");
			//printf("Ŭ���̾�Ʈ ���� ���� : IP:%s, PORT:%d\n",
			//	inet_ntoa(clientaddr.sin_addr),
			//	ntohs(clientaddr.sin_port));
			break; // Ŭ���̾�Ʈ ����
		}
		buf[iRecvByte] = 0;
		printf("\n%s", buf);
		int iSendByte = send(sock, buf, iRecvByte, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("Ŭ���̾�Ʈ ���� ����\n");
			break; // Ŭ���̾�Ʈ ����
		}
	}
	closesocket(sock);
	return 0;
}

int main(int argc, char* argv[])
{
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
			SOCKADDR_IN  clientaddr;
			SOCKET client;
			while (1)
			{
				int addlen = sizeof(clientaddr);
				client = accept(listenSock, (SOCKADDR*)&clientaddr, &addlen);
				printf("Ŭ���̾�Ʈ ���� : IP:%s, PORT:%d\n",
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				char buf[256] = { 0, };
				int iLen = 0;
				while (1)
				{
					int iRecvByte = recv(client, buf, 256, 0);
					if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
					{
						printf("Ŭ���̾�Ʈ ���� ���� : IP:%s, PORT:%d\n",
							inet_ntoa(clientaddr.sin_addr),
							ntohs(clientaddr.sin_port));
						break; // Ŭ���̾�Ʈ ����
					}
					buf[iRecvByte] = '\n';
					printf("\n%s", buf);
					int iSendByte = send(client, buf, iRecvByte, 0);
				}
				closesocket(client);
			}
		}
		closesocket(listenSock);
	}
	// ������ ���� �Ҹ�
	iRet = WSACleanup();
	return iRet;
}