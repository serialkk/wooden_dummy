#pragma once
#pragma warning( disable:4005)
#include "TDefine.h"

struct TRtBuffer
{
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰	
	ID3D11DepthStencilView*	m_pDepthStencilView;
	D3D11_VIEWPORT			m_ViewPort;			// 뷰포트 
};

class TDevice 
{
public:
	TRtBuffer				m_DefaultRTBuffer;
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	ID3D11Device*           m_pd3dDevice;		// 디바이스 객체
	IDXGISwapChain*         m_pSwapChain;		// 스왑체인 객체
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰
	D3D11_VIEWPORT			m_ViewPort;			// 뷰포트 
	D3D_DRIVER_TYPE         m_driverType;		// 디바이스 타입( 디폴트:하드웨어 가속 )
	IDXGIFactory*			m_pGIFactory;		// DXGI 객체
	ID3D11DeviceContext*    m_pImmediateContext;
	D3D_FEATURE_LEVEL       m_FeatureLevel;
	BOOL					m_IsFullScreenMode;	// 풀스크린 디바이스 여부판단
public:
	BOOL					GetFullScreenFlag();
	void					SetFullScreenFlag( BOOL bFlag );
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
	IDXGISwapChain*			GetSwapChain();
	ID3D11RenderTargetView*	GetRenderTargetView();
	IDXGIFactory*			GetGIFactory();
public:
	//--------------------------------------------------------------------------------------
	// 디바이스 및 스왑체인 생성 : InitDevice()
	//--------------------------------------------------------------------------------------
	HRESULT		InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen= FALSE);
	// 0, InitDevice()
	// 1, CreateGIFactory()
	// 2, CreateDevice()
	// 3, CreateSwapChain()
	// 4, SetRenderTargetView()
	// 5, SetViewPort()
	//--------------------------------------------------------------------------------------
	HRESULT		CreateDevice( );
	HRESULT		CreateGIFactory();
	HRESULT		CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh, BOOL IsFullScreen = FALSE);
	HRESULT		CreateDeviceAndSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh, BOOL IsFullScreen = FALSE);
	//--------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------	
	bool		CleanupDevice();
	void		ClearD3D11DeviceContext( ID3D11DeviceContext* pd3dDeviceContext );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정한다.
	//--------------------------------------------------------------------------------------
	HRESULT		ResizeDevice( UINT iWidth, UINT iHeight);
	virtual		HRESULT		SetRenderTargetView();
	virtual		HRESULT		SetViewPort();
	virtual		HRESULT		DeleteDxResource();
	virtual		HRESULT		CreateDxResource();

public:
	TDevice(void);
	virtual ~TDevice(void);
};
