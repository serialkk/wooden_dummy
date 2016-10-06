#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TDirectWrite.h"
#include "TShape.h"

class TBasisLib_0 : public TWindow
{
public:
	TTimer					m_Timer;
	TDirectWrite			m_Font;
	UINT					m_iPrimitiveType;
	UINT					m_iCullMode;
	UINT					m_iSamplerMode;
	bool					m_bWireFrameRender;
	bool					m_bDebugPrint;
	TDirectionLineShape		m_AxisLine;
	T_STR					m_LineShaderFile;
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
	 
	virtual bool		Update(ID3D11DeviceContext*    pContext);
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
