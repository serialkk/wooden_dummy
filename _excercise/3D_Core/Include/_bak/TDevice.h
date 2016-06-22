#pragma once
#include "TStd.h"

class TDevice
{
public:
	HWND		m_hWnd; // ������ �ڵ�
	HINSTANCE	m_hInstance; // ���ఴü �ڵ�
	RECT		m_rtWindow;
	DWORD		m_dwWidth;
	DWORD		m_dwHeight;
public:
	D3D_DRIVER_TYPE         g_driverType;
	D3D_FEATURE_LEVEL       g_featureLevel;
	ID3D11Device*           g_pd3dDevice;
	ID3D11DeviceContext*    g_pImmediateContext;
	IDXGISwapChain*         g_pSwapChain;
	ID3D11RenderTargetView* g_pRenderTargetView;	
	IDXGIFactory*			g_pGIFactory;
	DXGI_SWAP_CHAIN_DESC	m_sd;
public:
	bool   ResizeDevice(UINT iWidth, UINT iHeight);
	HRESULT SetRenderTarget();
	HRESULT SetViewPort();
	HRESULT CreateGIFactory();
	HRESULT InitSwapChain();
	HRESULT InitDevice();
	void	CleanupDevice();
	HRESULT  TDevice::CreateDXResouce();
	HRESULT  TDevice::DeleteDXResouce();
public:
	TDevice();
	virtual ~TDevice();
};

