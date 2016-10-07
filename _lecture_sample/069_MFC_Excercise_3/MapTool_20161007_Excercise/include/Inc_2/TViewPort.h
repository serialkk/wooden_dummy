#pragma once
#include "TBasisStd.h"

class TViewPort
{
public:
	D3D11_VIEWPORT				m_vp;
	ID3D11DepthStencilView*		m_pDepthStencilView;
	D3DXMATRIX					m_matProj;
public:
	HRESULT			Set(	/*ID3D11Device* pDevice,
							ID3D11RenderTargetView* pRTV,*/
							INT TopLeftX,   
							INT TopLeftY,   
							UINT Width,   
							UINT Height,   
							FLOAT MinDepth = 0.0f,  
							FLOAT MaxDepth = 1.0f);
	HRESULT			CreateDepthStencilView(	UINT iWidth, UINT iHeight, 
											ID3D11Device* pDevice,
											ID3D11DeviceContext*    pImmediateContext,
											ID3D11RenderTargetView* pRTV );
	void			Bind(ID3D11DeviceContext*    pImmediateContext, ID3D11RenderTargetView* pRTV);
	void			Apply(	ID3D11DeviceContext*    pImmediateContext,
							ID3D11RenderTargetView* pRTV = 0,
							bool bDepthClear = true, 
							bool bStencilClear = true );
	void			Apply(	ID3D11DeviceContext*    pImmediateContext, 
							ID3D11DepthStencilView* pDepthStencilView, 
							bool bDepthClear = true, 
							bool bStencilClear = true );

public:
	bool			Release();

public:
	TViewPort(void);
	virtual ~TViewPort(void);
};
