#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TInput.h"
#include "TShape.h"
#include "TObject.h"
#include "TModelViewCamera.h"
#include "TBackViewCamera.h"
#include "TEditer.h"
#include "TDirectWrite.h"

enum CAMERA_TYPE {
	DEBUG_CAMERA = 0,
	MODELVIEW_CAMERA = 1,
	BACKVIEW_CAMERA=2
};

class TCore : public TWindow//, public TSingleton<TCore>
{
public:
	TEditer					m_ShaderEditer;
	//TObject*				m_pDirectionLine;
	TDirectionLineShape*    m_pDirectionLine;
	TCamera*				m_pMainCamera;
	TCamera*				m_pDebugCamera;
	TCamera*				m_pModelViewCamera;
	TCamera*				m_pBackViewCamera;
	CAMERA_TYPE				m_CameraType;
	virtual void			SetCameraType( CAMERA_TYPE type );
	D3DXMATRIX				m_matWorld;
	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;	
	bool					m_bWireFrameRender;
	cbChangesEveryFrame		m_cbEveryFrame;
	cbChangeOnResize		m_cbOnResize;
	TDxBuffer				m_EveryFrameCBuffer;
	TDxBuffer				m_OnResizeCBuffer;
	HRESULT					CreateConstantBuffer(D3D11_USAGE type = D3D11_USAGE_DEFAULT);
	void					SetEveryFrameCBuffer( ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matWorld, D3DXMATRIX& matView );
	void					SetOnResizeCBuffer(ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matProj);
public:
	virtual void		SetLib() {};
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
	TCore(void);
	virtual ~TCore(void);
};
//#define g_Core TCore::GetInstance()