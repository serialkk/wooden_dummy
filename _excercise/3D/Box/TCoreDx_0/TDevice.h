#pragma once
#include "TWindow.h"

class TDevice : public TWindow
{
public:
	ID3D11Debug*			m_pDebug;
	IDXGIFactory*			m_pGIFactory;
	// �׷��� ī�� ��ġ �������̽�(���ҽ� ����)
	ID3D11Device*			m_pd3dDevice;
	// ��� ����,���� �� ���� �������̽�
	ID3D11DeviceContext*	m_pImmediateContext;
	// ������ũ�� (������۸� ���)�������̽�
	IDXGISwapChain*			m_pSwapChain;
	// ������ũ�� ��� ����
	ID3D11RenderTargetView*	m_pRTV;
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	D3D11_VIEWPORT			m_ViewPort;
	D3D_DRIVER_TYPE			m_DriverType;
	ID3D11Device*			GetDevice() 
	{	return m_pd3dDevice;	};
	ID3D11DeviceContext*	GetContext() 
	{	return m_pImmediateContext;	};
	ID3D11DepthStencilView*   m_pDSV;
public:
	bool		Init();
	bool		PreRender();
	bool		PostRender();
	bool		Release();
public:
	HRESULT     CreateGIFactory();
	HRESULT		CreateDevice();
	HRESULT		CreateSwapChain();
	HRESULT		SetRenderTargetView();
	HRESULT		SetViewPort();
	HRESULT		CreateDepthStencilState();
	bool		Reset(UINT iWidth, UINT iHeight);
public:
	TDevice();
	virtual ~TDevice();
};

