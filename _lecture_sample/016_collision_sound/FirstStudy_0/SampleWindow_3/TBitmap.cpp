#include "TBitmap.h"
#include "TSys.h"
bool     TBitmap::Load(TCHAR* pFileName)
{
	m_hScreenDC = g_hScreenDC;
	m_hOffScreenDC = g_hOffScreenDC;
	//HANDLE'���� 'HBITMAP'(��)�� ��ȯ�� �� �����ϴ�.
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
		pFileName, IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_hBitInfo);
	// �޸� DC �Ҵ�( ȭ�� DC�� ȣȯ������ �� 2�� DC ����)
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	// �޸� DC�� ��Ʈ���� ����
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	TCHAR SaveName[MAX_PATH] = { 0, };
	_tsplitpath_s(pFileName, Drive, Dir, Name, Ext);
	_stprintf_s(SaveName, _T("%s%s"), Name, Ext);
	_tcscpy_s(m_szName, SaveName);
	return true;
}
bool     TBitmap::Load( HDC hScreenDC, 
						HDC hOffScreenDC,
						TCHAR* pFileName)
{
	m_hScreenDC = hScreenDC;
	m_hOffScreenDC = hOffScreenDC;
	//HANDLE'���� 'HBITMAP'(��)�� ��ȯ�� �� �����ϴ�.
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
		pFileName, IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_hBitInfo);
	// �޸� DC �Ҵ�( ȭ�� DC�� ȣȯ������ �� 2�� DC ����)
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	// �޸� DC�� ��Ʈ���� ����
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

bool TBitmap::Init()
{
	return true;
}

bool TBitmap::Frame()
{
	return true;
}

bool TBitmap::Render()
{
	BitBlt(m_hOffScreenDC, 0, 0,
		m_hBitInfo.bmWidth,
		m_hBitInfo.bmHeight,		
		m_hMemDC, 0, 0, SRCCOPY);//  ����
	//StretchBlt( m_hOffScreenDC, 
	//			0,
	//			0,
	//			800,
	//			600,		
	//			m_hMemDC, 
	//	100,//m_hBitInfo.bmWidth/2, 
	//	m_hBitInfo.bmHeight/2,
	//			m_hBitInfo.bmWidth,
	//			m_hBitInfo.bmHeight,
	//			SRCCOPY);//  ����
	return true;
}

bool TBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}
TBitmap::TBitmap()
{
	m_iIndex = -1;
}


TBitmap::~TBitmap()
{
}
