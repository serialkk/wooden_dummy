#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include "KStd.h"
#pragma comment( lib, "dwrite.lib")
#pragma comment	(lib, "d2d1.lib")

class KWrite
{
public:
	ID2D1Factory*		m_pD2DFactory;	
	ID2D1RenderTarget*  m_pRT;

	IDWriteFactory*		m_WriteFactory;
	IDWriteTextFormat*  m_TextFormat;

	ID2D1SolidColorBrush*  m_pRedBrush;
public:
	bool   Init();
	bool   Release();
	void   Begin();
	void   End();
	bool   Set(IDXGISurface1*  pSurface);
	HRESULT DrawText(RECT rt,
		TCHAR* pText,
		D2D1::ColorF Color);
	HRESULT CreateDeviceIndendentResource();
	HRESULT CreateDeviceResources(IDXGISurface1* pSurface);
public:
	KWrite();
	virtual ~KWrite();
};

