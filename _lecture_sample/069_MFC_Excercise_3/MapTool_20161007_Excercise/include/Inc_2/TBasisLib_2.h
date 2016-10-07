#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TShape.h"
#include "TModelViewCamera.h"
#include "TBackViewCamera.h"
#include "TEditer.h"
#include "TDirectWrite.h"
enum CAMERA_TYPE {
	DEBUG_CAMERA = 0,
	MODELVIEW_CAMERA = 1,
	BACKVIEW_CAMERA=2
};
class TBasisLib_2 : public TWindow
{
public:
	TEditer					m_ShaderEditer;
	TShape*					m_pDirectionLine;
	TCamera*				m_pMainCamera;
	TCamera*				m_pDebugCamera;
	TCamera*				m_pModelViewCamera;
	TCamera*				m_pBackViewCamera;
	CAMERA_TYPE				m_CameraType;
	TDxState				m_DxState;
	virtual void			SetCameraType( CAMERA_TYPE type );

	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;
	bool					m_bWireFrameRender;

public:
	virtual void		SetLib();
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
	virtual bool		DrawDebug(bool bDrawString = true, bool bDrawLine=true);
	virtual bool		DrawDebugRect(RECT* rcDest = NULL, TCHAR* pString = 0, D3DXCOLOR color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) );

	virtual	bool		PostRender();

	bool				TInit();
	bool				TFrame();
	bool				TRender();	
	bool				Run();		 
	bool				TRelease();
	int					MsgProc( HWND, UINT, WPARAM, LPARAM );
public:
	bool				CheckWindowSize();
	
	//--------------------------------------------------------------------------------------
	// 리셋 지원 함수
	//--------------------------------------------------------------------------------------
	virtual HRESULT		DeleteResource();
	virtual HRESULT		CreateResource();	
	HRESULT				DeleteDxResource();
	HRESULT				CreateDxResource();
public:
	TBasisLib_2(void);
	virtual ~TBasisLib_2(void);
};