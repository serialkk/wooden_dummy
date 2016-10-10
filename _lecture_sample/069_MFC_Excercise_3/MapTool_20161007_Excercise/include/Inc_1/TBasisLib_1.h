#pragma once
#pragma warning( disable:4005)
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TDirectWrite.h"
#include "TShape.h"

class TBasisLib_1 : public TWindow
{
public:
	TTimer					m_Timer;
	TDirectWrite			m_Font;	
	TDxState				m_DxState;
	TDirectionLineShape*	m_pDirectionLine;
	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual int			WndProc( HWND, UINT, WPARAM, LPARAM );

	virtual bool		PreInit();	
	virtual bool		PostInit();	 
		
	virtual bool		PreFrame();		
	virtual bool		PostFrame();

	virtual bool		PreRender();
	virtual bool		PostRender();

	virtual bool		DrawDebug();
	virtual bool		DrawDebugRect(RECT* rcDest = NULL, TCHAR* pString = 0, D3DXCOLOR color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) );


	bool				TInit();
	bool				TFrame();
	bool				TRender();	
	bool				Run();		 
	bool				TRelease();
	
public:
	TBasisLib_1(void);
	virtual ~TBasisLib_1(void);
};
