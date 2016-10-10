#pragma once
#pragma warning( disable:4005)
#include "TViewRT.h"
#include "TViewDS.h"
#include <d3dx10math.h>

class TRenderTexture
{
public:
	TViewRT*		m_pViewRT;
	TViewDS*		m_pViewDS;
	D3D11_TEXTURE2D_DESC m_rtTexDesc;
	D3D11_TEXTURE2D_DESC m_dsTexDesc;
	D3D11_VIEWPORT			m_ApplyVP;

	//Store the old viewport
    D3D11_VIEWPORT			m_OldVP;
    ID3D11RenderTargetView* m_pOldRT;
    ID3D11DepthStencilView* m_pOldDS;

	bool			Begin(ID3D11DeviceContext*    pImmediateContext,
						  D3DXVECTOR4 vClearColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f),
						  bool bColorWrite = true );
	void			End(ID3D11DeviceContext*    pImmediateContext);
	bool			Create(	ID3D11Device* pd3dDevice, 
							ID3D11DeviceContext*    pImmediateContext, 
							UINT iSize,
							bool bColorWrite=true,
							DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM	);
	bool			Release();
public:
	TRenderTexture(void);
	virtual ~TRenderTexture(void);
};

