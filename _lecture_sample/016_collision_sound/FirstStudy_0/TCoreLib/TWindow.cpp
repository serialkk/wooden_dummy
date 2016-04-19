#include "TWindow.h"
//1>  TCoreLib.vcxproj->D:\MyProjects\FirstStudy
//_0\TCoreLib\..
/// .. / output / TCoreLib\TCoreLib.lib
HWND g_hWnd= NULL;
HINSTANCE g_hInstance;
void TWindow::SetRect(int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
}
// �ü���� �޼��� ����ϴ� �Լ��� �ȴ�.
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,// �ΰ����� ������
	LPARAM lParam)// �ΰ����� ������
{
	switch (msg)
	{	
	case WM_SIZE:
	{
		if (wParam == SIZE_MINIMIZED)
		{
			INT KKK = 0;
		}
		if (wParam == SIZE_MAXIMIZED)
		{
			INT KKK = 0;
		}
		UINT iWidth = LOWORD(lParam);
		UINT iHeight = HIWORD(lParam);
		TCHAR strBuffer[MAX_PATH] = { 0, };
		_stprintf_s(strBuffer, L"%ld %ld\n", iWidth, iHeight);
		OutputDebugString(strBuffer);
		//MessageBox(hWnd, strBuffer, L"WM_SIZE", MB_OK);

	}break;
	case WM_DESTROY:
	{
		// �ݱ� �޼����� ������ ���ν����� ����Ѵ�.
		// �޼��� ť�� ���� �ڿ� WM_QUIT �� �߰�
		PostQuitMessage(0);
	}
	}
	// ������ �޼����� �ü���� �˾Ƽ� ó���ض�.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool TWindow::SetWindow( HINSTANCE hInstatnce,
	TCHAR* titleName,
	int iX, int iY, int iWidth,
	int iHeight)
{
	m_hInstance = hInstatnce;
	g_hInstance = hInstatnce;
	if (m_iWidth == 0 && m_iHeight == 0)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}
	// 1, ������ Ŭ���� ��ü �ü���� ���
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.lpszClassName = L"KGCA";
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstatnce;
	// ��Ʈ��( ����Ǿ� �ִ�. )
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.cbClsExtra = 0;// ������ Ŭ�������� ����Ϸ��� ������ �޸� ũ��
	wc.cbWndExtra = 0;// �����쿡�� ����Ϸ��� ������ �޸� ũ��
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	RECT rt = { 0,0,m_iWidth ,m_iHeight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// 2, ��ϵ� Ŭ���� ��ü�� ����Ͽ� ������ ����
	m_hWnd = CreateWindowEx(
		// �۾�ǥ���� ��ܿ� ��ġ�ض�.
		WS_EX_APPWINDOW, //DWORD dwExStyle,
		L"KGCA",
		titleName,
		WS_OVERLAPPEDWINDOW,//WS_OVERLAPPEDWINDOW, //WS_POPUPWINDOW, //DWORD dwStyle,
		iX, //int X,
		iY,//int Y,
		rt.right - rt.left,//int nWidth,
		rt.bottom - rt.top,//int nHeight,
		NULL, //HWND hWndParent,
		NULL,//HMENU hMenu,
		hInstatnce,//HINSTANCE hInstance,
		NULL);  //LPVOID lpParam);
	if (m_hWnd != NULL)
	{
		// 3, ������ ��Ÿ����, ��ħ, ������ �ٿ��
		ShowWindow(m_hWnd, SW_SHOW);
	}
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);

	CenterWindow();

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	return true;
}
void TWindow::CenterWindow()
{
	// ��ü ��ũ���� ũ��
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (
		m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (
		m_rtWindow.bottom - m_rtWindow.top)) / 2;


	MoveWindow(m_hWnd, x, y, 
		m_rtWindow.right- m_rtWindow.left,
		m_rtWindow.bottom- m_rtWindow.top, true);
}
TWindow::TWindow()
{
	m_iWidth = 0;
	m_iHeight = 0;
}


TWindow::~TWindow()
{
}
