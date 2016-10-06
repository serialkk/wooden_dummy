#pragma once
#include "TDxState.h"
#include "TBasisStd.h"

#pragma comment		(lib, "dinput8.lib")
//#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx10d.lib" )
#pragma comment( lib, "d3dx11d.lib" )
#pragma comment( lib, "dxgi.lib" )
#else
#pragma comment( lib, "d3dX10.lib" )
#pragma comment( lib, "d3dx11.lib" )
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "TBasisLib32d.lib" )
#else
#pragma comment( lib, "TBasisLib32R.lib" )
#endif

class TDevice 
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	ID3D11Device*           m_pd3dDevice;		// 디바이스 객체
	IDXGISwapChain*         m_pSwapChain;		// 스왑체인 객체
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰	
	IDXGIFactory*			m_pGIFactory;		// DXGI 객체
	ID3D11DeviceContext*    m_pImmediateContext;
	ID3D11DepthStencilView*	m_pDepthStencilView;	
	
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*    GetContext();
	IDXGISwapChain*			GetSwapChain();
	ID3D11RenderTargetView*	GetRenderTargetView();
	IDXGIFactory*			GetGIFactory();
	ID3D11DepthStencilView*	GetDepthStencilView() { return m_pDepthStencilView;};

public:
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	D3D11_VIEWPORT			m_MainVP;			// 뷰포트 
	D3D_DRIVER_TYPE         m_driverType;		// 디바이스 타입( 디폴트:하드웨어 가속 )	
	D3D_FEATURE_LEVEL       m_FeatureLevel;
	BOOL					m_IsFullScreenMode;	// 풀스크린 디바이스 여부판단
	BOOL					GetFullScreenFlag();
	void					SetFullScreenFlag( BOOL bFlag );
	
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
	HRESULT		CreateDepthStencilView( UINT iWidth, UINT iHeight );

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
