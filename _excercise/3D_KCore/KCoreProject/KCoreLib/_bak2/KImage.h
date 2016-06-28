#pragma once
#include "KStd.h"
class KImage
{
public:
	T_STR		 m_strName;
	HDC			m_hMemDC;
	HBITMAP	    m_hBitmap;
	HBITMAP	    m_hOldBitmap;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	bool Load( HWND hWnd, 
			 HDC hdc,
		T_STR fileName );
public:
	KImage(void);
	~KImage(void);
};

