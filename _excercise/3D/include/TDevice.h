#pragma once
#include "TDxStd.h"
#include "TWindow.h"
#include "TInput.h"
#include "TTimer.h"

#include <D3Dcompiler.h>
#include <assert.h>
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR4 Color;
};


struct ConstantBuffer
{
	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;
};

class TDevice : public TWindow
{
public:
	BOOL					m_IsFullScreenMode;	// 풀스크린 디바이스 여부판단
	IDXGIFactory*			g_pGIFactory;		// DXGI 객체
	D3D11_VIEWPORT			g_ViewPort;
	//DXGI_SWAP_CHAIN_DESC	g_SwapChainDesc;
	HRESULT			CreateDevice();
	void			SetFullScreenFlag(BOOL bFlag);
	HRESULT			CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen);
	IDXGIFactory*	GetGIFactory();
	HRESULT			CreateGIFactory();
	//bool			ResizeClient(UINT iWidth, UINT iHeight);
	HRESULT			SetRenderTargetView();
	HRESULT			SetViewPort();
	bool			ResizeDevice(UINT iWidth, UINT iHeight);
public:


	TInput m_Input;
	TTimer m_Timer;
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;


	D3DXMATRIX                g_World;
	D3DXMATRIX                g_View;
	D3DXMATRIX                g_Projection;

	bool PreRender();
	bool PostRender();	
	bool	GameRun();
	bool	GameInit(); 
	bool   GameRelease();
public:


	HRESULT InitDevice();
	//HRESULT InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen);
	void	CleanupDevice();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

	TDevice();
	virtual ~TDevice();
};

