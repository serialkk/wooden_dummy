#pragma once
#include "KStd.h"
class KBitmap
{
public:
	int		 m_iIndex;
	TCHAR    m_szName[MAX_PATH];
	HDC		 m_hScreenDC;
	HDC		 m_hOffScreenDC;
	HDC      m_hMemDC;
	HBITMAP  m_hBitmap;
	HBITMAP  m_hOldBitmap;
	BITMAP   m_hBitInfo;
public:
	// ���� ���� ����� ����.(HDC)
	bool     Load(TCHAR* pFileName);
	bool     Load( HDC hScreenDC, 
				   HDC hOffScreenDC,
				  TCHAR* pFileName);
	bool     Init();
	bool     Frame();
	bool     Render();
	bool     Release();
public:
	KBitmap();
	virtual ~KBitmap();
};

