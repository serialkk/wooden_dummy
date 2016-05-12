// Client_0.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI SendThread(LPVOID data)
{
	SOCKET sock = (SOCKET)data;
	char szBuffer[MAX_PATH] = { 0, };
	while (1)
	{
		ZeroMemory(szBuffer, sizeof(char)* MAX_PATH);
		fgets(szBuffer, MAX_PATH, stdin);
		int iMessageSize = strlen(szBuffer);
		int iSendbyte = send(sock, szBuffer, iMessageSize, 0);
		printf("\nSendMessage = %s[%d]", szBuffer,
			iMessageSize);
	}
	return 0;
}
// ���� ���α׷���
void main()
{
	HANDLE g_hMutex = CreateMutex(NULL, TRUE, _T("KGCA"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, _T("�̹� ���� �������Դϴ�.!"), _T("Error"), MB_OK);
		CloseHandle(g_hMutex);
		return;
	}

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
	sa.sin_addr.s_addr = inet_addr("192.168.0.100");
	int iRet = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	DWORD dwSendThreadID;
	// ������ ���� ���
	HANDLE hThread = CreateThread(0, 
		0, SendThread, (LPVOID)sock, 0,
		&dwSendThreadID);

	char szBuffer[MAX_PATH] = { 0, };
	while (1)
	{	
		ZeroMemory(szBuffer, sizeof(char)*MAX_PATH);
		int iRecvByte = recv(sock, szBuffer, sizeof(char)*MAX_PATH, 0);
		if (iRecvByte == 0)
		{
			printf("\nServer DisConnect!");
			break;
		}
		printf("\nRecvMessage = %s[%d]", szBuffer,
			strlen(szBuffer));
	}
	CloseHandle(hThread);
	_getch();
	// ���� ����
	WSACleanup();
}


