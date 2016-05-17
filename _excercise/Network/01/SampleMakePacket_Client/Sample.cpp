#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "TProtocol.h"
#pragma comment(lib, "ws2_32.lib")

HANDLE g_hEvent;
SOCKET sock;
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.type = type;// PACKET_CHAT_MSG;
						   // ��� 1
	memcpy(sendmsg.msg, msg, strlen(msg));
	// ��� 2
	//sprintf_s(sendmsg.msg,"%s", "[����]ȯ���մϴ�.");
	sendmsg.ph.len = strlen(sendmsg.msg) + PACKET_HEADER_SIZE;
	int iRet = send(sock, (char*)&sendmsg, sendmsg.ph.len, 0);
	return iRet;
}

DWORD WINAPI ConnectThread(LPVOID arg)
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;//sockaddr name;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);// host byte ���� to network byte ���� short
	//sa.sin_addr.s_addr = inet_addr("192.168.0.100");
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	int iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) { return 1; }
	linger optval;
	int iLength = sizeof(optval);
	getsockopt(sock, SOL_SOCKET, SO_LINGER, (char*)&optval, &iLength);
	optval.l_onoff = 1;
	optval.l_linger = 1000;
	setsockopt(sock, SOL_SOCKET, SO_LINGER, (char*)&optval, iLength);


	SetEvent(g_hEvent);
	//ResetEvent(g_hEvent);
	return 0;
}
DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	while (1)
	{
		ZeroMemory(buf, sizeof(char) * 256);
		fgets(buf, 256, stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if (strlen(buf) == 0 ||
			_stricmp(buf, "quit") == 0)
		{
			SendMsg(sock, buf, PACKET_GAME_END);
			break; // ���ʹ� ����!
		}

		int iSendByte = SendMsg(sock, buf, PACKET_CHAT_MSG);
		if (iSendByte == SOCKET_ERROR) break;
		printf("\t%d ����Ʈ�� �����Ͽ����ϴ�.", iSendByte);
	}
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	return 0;
}
DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char buf[2048] = { 0, };
	printf("\n���� ������ �Է��Ͻÿ�?");
	int iRecvByte = 0;
	int iStartByte = 0;
	ZeroMemory(buf, sizeof(char) * 2048);
	while (1)
	{		
		int iLen = 0;
		iRecvByte += recv(sock, &buf[iStartByte], PACKET_HEADER_SIZE-iRecvByte, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
		{
			printf("[��������]: %s", "���� ������ ���Ͽ� ����Ǿ���.");
			break;
		}
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET* pPacket = (UPACKET*)&buf;
			while (iRecvByte < pPacket->ph.len)
			{
				iRecvByte += recv(sock, &buf[iRecvByte],
					pPacket->ph.len - iRecvByte, 0);
			}
			if(iRecvByte == pPacket->ph.len)
			{
				UPACKET recvmsg;
				memset(&recvmsg, 0, sizeof(recvmsg));
				memcpy(&recvmsg, pPacket, pPacket->ph.len);
				switch (recvmsg.ph.type)
				{
					case PACKET_CHAT_MSG:
					{
						printf("\n[�����޼���]: %s", recvmsg.msg);
						printf("\n���� ������ �Է��Ͻÿ�?");
					}break;
				}		
				iStartByte = iRecvByte = 0;
			}
		}
		else
		{
			iStartByte += iRecvByte;
		}
	}
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	return 0;
}
int main(int argc, char* argv[])
{
	HANDLE hExecuteMutex=0;// = CreateMutex(NULL, FALSE, L"OnceClinetMutex");
	//if (GetLastError() == ERROR_ALREADY_EXISTS)
	//{
	//	CloseHandle(hExecuteMutex);
	//	MessageBox(NULL, L"�̹� �ٸ� �ν��Ͻ��� ���� ���Դϴ�.", L"�˸�", MB_OK);
	//	return 1;
	//}

	// 2 : FALSE(�ڵ����� �̺�Ʈ ),TRUE( �������� �̺�Ʈ )
	// 3 : �ʱⰪ(FALSE: ��ñ׳�, TRUE:�ñ׳�)
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, L"ConnectEvent");


	if (argc != 3)
	{
		printf("\n[�����] xxx.exe [port] [ip]");
		printf("\n[��뿹��] xxx.exe 10000 192.168.0.100");
		//return 1;		
	}
	//unsigned short iPort = atoi(argv[1]);
	//char* ip = argv[2];

	HANDLE hSendThread, hRecvThread, hConnectThread;
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }
	{
		// ���� ����
		DWORD dwConnectThreadID;
		hConnectThread = CreateThread(0, 0,
			ConnectThread,
			(LPVOID)0,
			0,
			&dwConnectThreadID);

		//WaitForSingleObject(hConnectThread, INFINITE);
		WaitForSingleObject(g_hEvent, INFINITE);
		//while (g_bConnect == false);
		//ResetEvent(g_hEvent);

		{
			// ���� ����
			DWORD dwSendThreadID;

			hSendThread = CreateThread(0, 0,
				SendThread,
				(LPVOID)sock,
				0,
				&dwSendThreadID);
			DWORD dwRecvThreadID;
			hRecvThread = CreateThread(0, 0,
				RecvThread,
				(LPVOID)sock,
				0,
				&dwRecvThreadID);
		}

	}
	// �����尡 ����Ǿ����� Ȯ��
	WaitForSingleObject(hSendThread, INFINITE);
	WaitForSingleObject(hRecvThread, INFINITE);

	CloseHandle(hSendThread);
	CloseHandle(hRecvThread);

	// ������ ���� �Ҹ�
	iRet = WSACleanup();
	CloseHandle(hExecuteMutex);
	CloseHandle(g_hEvent);
	return iRet;
}

