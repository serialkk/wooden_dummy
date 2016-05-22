#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
//#include <unistd.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	//int sock;
	char message[BUF_SIZE];
	int str_len;
	//struct sockaddr_in serv_adr;


	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET  sock;

	//if(argc!=3) {
	//	printf("Usage : %s <IP> <port>\n", argv[0]);
	//	exit(1);
	//}
	
	//sock=socket(PF_INET, SOCK_STREAM, 0);   
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1)
		error_handling("socket() error");
	
	SOCKADDR_IN sa;

	memset(&sa, 0, sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr(argv[1]);
	sa.sin_port = htons(atoi("10000"));;//htons(atoi(argv[2]));
	
	//if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
	//	if (connect(sock, (SOCKADDR*)&sa, sizeof(sa)))
	//	error_handling("connect() error!");
	//else
	//	puts("Connected...........");
	
	int iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		error_handling("connect() error!");
	}
	else
	{
		puts("Connected...........");
	}

	while(1) 
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);
		
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
			break;

		//write(sock, message, strlen(message));
		send(sock, message, strlen(message), 0);

		//str_len=read(sock, message, BUF_SIZE-1);
		str_len = recv(sock, message, BUF_SIZE - 1, 0);
		message[str_len]=0;
		printf("Message from server: %s", message);
	}
	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}