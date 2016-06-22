#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TDirectWrite.h"

class TBasisLib_0 : public TWindow
{
public:
	TTimer					m_Timer;
	TDirectWrite			m_Font;

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
	 
	 
	virtual	bool		PreRender();
	virtual bool		DrawDebug();
	virtual bool		DrawDebugRect(RECT* rcDest = NULL, TCHAR* pString = 0, D3DXCOLOR color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) );
	virtual	bool		PostRender();

	bool				TInit();
	bool				TFrame();
	bool				TRender();	
	bool				Run();		 
	bool				ToolRun();
	bool				TRelease();

				HRESULT		CreateDxResource();
				HRESULT		DeleteDxResource();
	virtual		HRESULT		CreateResource();
	virtual		HRESULT		DeleteResource();
	
public:
	TBasisLib_0(void);
	virtual ~TBasisLib_0(void);
};
