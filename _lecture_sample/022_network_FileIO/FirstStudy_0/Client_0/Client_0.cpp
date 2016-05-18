// Client_0.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#include "TProtocol.h"
#pragma comment(lib, "ws2_32.lib")

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(UPACKET));
	sendmsg.ph.type = type;
	sendmsg.ph.len = PACKET_HEADER_SIZE + strlen(msg);
	memcpy(sendmsg.msg, msg, strlen(msg));
	int iSendbyte = 0;
	char* szSend = (char*)&sendmsg;
	while (1)
	{
		iSendbyte +=
			send(sock, szSend,
				sendmsg.ph.len - iSendbyte, 0);
		if (sendmsg.ph.len == iSendbyte)
		{
			break;
		}
		szSend += iSendbyte;
	}
	//printf("SendMessage=%s", sendmsg.msg );
	return iSendbyte;
}
void  PacketProcess(UPACKET* pPacket)
{
	// 1개의 패킷이 완성
	switch (pPacket->ph.type)
	{
		case PACKET_CHAR_MSG:
		{
			printf("RecvMessage=%s", pPacket->msg);
		}break;
		case PACKET_CHAR_JOIN:
		{
			printf("이름을 입력하시오");
		}break;
		case PACKET_CHAR_DROP:
		{
			CHARACTER_INFO info;
			memcpy(&info, pPacket->msg, sizeof(CHARACTER_INFO));
			printf("[%s]유저가 나갔습니다.", info.szName);
		}break;
	}
}
DWORD WINAPI SendThread(LPVOID data)
{
	SOCKET sock = (SOCKET)data;
	char szBuffer[MAX_PATH] = { 0, };
	while (1)
	{
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		fgets(szBuffer, MAX_PATH, stdin);
		if (_stricmp(szBuffer, "exit") == 0) break;
		int iMessageSize = strlen(szBuffer);
		int iRet = SendMsg(sock, szBuffer, PACKET_CHAR_MSG);
		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			break;
		}
		Sleep(1);
	}
	closesocket(sock);
	return 0;
}
DWORD WINAPI RecvThread(LPVOID data)
{
	SOCKET sock = (SOCKET)data;
	char szBuffer[MAX_PATH] = { 0, };
	int  iRecvData = 0;
	bool bConnect = true;
	while (bConnect)
	{				
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		int iRet = recv( sock, &szBuffer[iRecvData],
			PACKET_HEADER_SIZE-iRecvData, 0 );
		iRecvData += iRet;
		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			bConnect = false;
			break;
		}
		UPACKET* pPacket = (UPACKET*)&szBuffer;
		if (iRecvData == PACKET_HEADER_SIZE)
		{		
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
			// 완성된 패킷에 대한 처리
			PacketProcess(pPacket);
			iRecvData = 0;
		}		
		Sleep(1);
	}
	closesocket(sock);
	//MessageBox(NULL, _T("서버가 종료되었습니다.!"), _T("Error"), MB_OK);
	return 1;
}
// 소켓 프로그래밍
void main()
{
	/*HANDLE g_hMutex = CreateMutex(NULL, FALSE, _T("CLIENT"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, _T("이미 게임 실행중입니다.!"), _T("Error"), MB_OK);
		CloseHandle(g_hMutex);
		return;
	}*/

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
	sa.sin_addr.s_addr = inet_addr("192.168.0.100");
	int iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}

	DWORD dwSendThreadID;
	// 보내는 하인 등용
	HANDLE hSendThread = CreateThread(0, 
		0, SendThread, (LPVOID)sock, 0,
		&dwSendThreadID);

	DWORD dwRecvThreadID;
	HANDLE hRecvThread = CreateThread(0,
		0, RecvThread, (LPVOID)sock, 0,
		&dwRecvThreadID);

	// 두개의 스레드의 종료 확인
	WaitForSingleObject(hRecvThread, INFINITE);
	//WaitForSingleObject(hSendThread, INFINITE);	

	CloseHandle(hSendThread);
	CloseHandle(hRecvThread);
	//_getch();
	// 윈속 해제
	WSACleanup();
}


