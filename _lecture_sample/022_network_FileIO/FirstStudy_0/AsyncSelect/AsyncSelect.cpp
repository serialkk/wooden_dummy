// AsyncSelect.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#define WM_SOCKET  (WM_USER+10)

HWND g_hWnd;
void NetworkProcess(WPARAM wParam, LPARAM lParam)
{
	// 오류여부 판단
	if (WSAGETSELECTERROR(lParam))
	{
		WORD dwError = WSAGETSELECTERROR(lParam);
		closesocket(wParam);
	}
	else
	{
		// 어떤 네트워크 이벤트 냐?
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
		{
			SOCKET clientSock = accept();
			WSAAsyncSelect(clientSock, g_hWnd, WM_SOCKET,
				// 네트워크인벤트
				FD_READ | FD_WRITE | FD_CLOSE);
		}break;
		case FD_READ:
		{
			//int iRet = UserRecv(wParam, lParam);
			int iRet = recv(wParam, &buffer, 1024, 0);
			if (iRet == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// 정상
				}
				else
				{
					closesocket(wParam);
					RemoveClient(wParam);

				}
			}
			else if (iRet != WSAEWOULDBLOCK)
			{
				PostMessage(g_hWnd, WM_SOCKET, wParam, FD_READ);
			}
		}break;
		case FD_WRITE:
		{}break;
		case FD_CLOSE:
		{
			PostMessage(g_hWnd, WM_SOCKET, wParam, FD_READ);
		}break;
		default :
		{
			WORD wError = WSAGETSELECTEVENT( lParam );
		}
		}
	}
}
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_SOCKET:
		{
			NetworkProcess(wParam,lParam);
		}break;
	}
}
HWND MakeWindow()
{
	HWND hWnd = CreateWindow();
	return hWnd;
}
int main()
{
	g_hWnd = MakeWindow();
	SOCKET listenSock;
	// bind
	// listen
	WSAAsyncSelect(listenSock, g_hWnd, WM_SOCKET, 
		// 네트워크인벤트
		FD_ACCEPT | FD_CLOSE );




    return 0;
}

