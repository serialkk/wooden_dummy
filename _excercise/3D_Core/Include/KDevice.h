#pragma once
#include "KStd.h"

class KDevice
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
	HRESULT IniKDevice();
	void	CleanupDevice();
	HRESULT  KDevice::CreateDXResouce();
	HRESULT  KDevice::DeleteDXResouce();
public:
	KDevice();
	virtual ~KDevice();
};

