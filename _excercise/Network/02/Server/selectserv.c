#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 1024
void ErrorHandling(char *message);


///////////////////////////////////////////////
// 3초당 보낸 횟수, 보낸 바이트를 출력하기위함.

#ifdef _WIN64
volatile LONG64 g_iSendCount = 0;
volatile LONG64 g_iSendByte = 0;
#else
volatile LONG g_iSendCount = 0;
volatile LONG g_iSendByte = 0;
#endif


DWORD WINAPI PrintThread(LPVOID arg)
{
	while (1) {
		printf("3초당 [보낸 횟수]:%d 번 [보낸 바이트]:%d byte\n", g_iSendCount, g_iSendByte);

#ifdef _WIN64
		InterlockedExchange64(&g_iSendCount, 0);
		InterlockedExchange64(&g_iSendByte, 0);
#else

		InterlockedExchange(&g_iSendCount, 0);
		InterlockedExchange(&g_iSendByte, 0);
#endif	
		Sleep(3000);
	}
}
///////////////////////////////////////////////



int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;

	int adrSz;
	int strLen, fdNum, i, j;
	char buf[BUF_SIZE];

	//if(argc!=2) {
	//	printf("Usage : %s <port>\n", argv[0]);
	//	exit(1);
	//}
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 

	//hServSock=socket(PF_INET, SOCK_STREAM, 0);
	hServSock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	//servAdr.sin_port=htons(atoi(argv[1]));
	servAdr.sin_port = htons(atoi("10000"));
	
	if(bind(hServSock, (SOCKADDR*) &servAdr, sizeof(servAdr))==SOCKET_ERROR)
		ErrorHandling("bind() error");
	if(listen(hServSock, 5)==SOCKET_ERROR)
		ErrorHandling("listen() error");

	FD_ZERO(&reads);
	FD_SET(hServSock, &reads);

	DWORD dwPrintThreadID;
	CloseHandle(CreateThread(0, 0, PrintThread, (LPVOID)0, 0, &dwPrintThreadID));

	while(1)
	{
		cpyReads=reads;
		timeout.tv_sec=5;
		timeout.tv_usec=5000;

		if((fdNum=select(0, &cpyReads, 0, 0, &timeout))==SOCKET_ERROR)
			break;
		
		if(fdNum==0)
			continue;

		for(i=0; i<reads.fd_count; i++)
		{
			if(FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if(reads.fd_array[i]==hServSock)     // connection request!
				{
					adrSz=sizeof(clntAdr);
					hClntSock=
						accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hClntSock, &reads);
					//printf("connected client: %d \n", hClntSock);

					printf("IP:[%s], PORT:[%d], 클라이언트 접속\n",
						inet_ntoa(clntAdr.sin_addr), ntohs(clntAdr.sin_port));
				}
				else    // read message!
				{
					strLen=recv(reads.fd_array[i], buf, BUF_SIZE-1, 0);
					if(strLen==0)    // close request!
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client: %d \n", cpyReads.fd_array[i]);
					}
					else
					{
						//send(reads.fd_array[i], buf, strLen, 0);    // echo!

						// broadcast
						for (j = 0; j < reads.fd_count; j++)
						{
							int iSendByte = send(reads.fd_array[j], buf, strLen, 0);
							if (iSendByte != -1) {
#ifdef _WIN64
								InterlockedIncrement64(&g_iSendCount);
								InterlockedExchange64(&g_iSendByte, g_iSendByte += iSendByte);
#else
								InterlockedIncrement(&g_iSendCount);
								InterlockedExchange(&g_iSendByte, g_iSendByte += iSendByte);
#endif
							}
						}
					}
				}
			}
		}
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}