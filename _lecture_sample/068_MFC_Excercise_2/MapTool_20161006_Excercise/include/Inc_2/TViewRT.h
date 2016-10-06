#pragma once
#pragma warning( disable:4005)
#include <d3d11.h>
#include <d3dx11.h> 

class TViewRT 
{
public:
    ID3D11Texture2D*			m_pTexture;
    ID3D11RenderTargetView*		m_pRTV;
    ID3D11ShaderResourceView*	m_pSRV;

	bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*    pImmediateContext, DWORD dwWidth=1024, DWORD dwHeight=1024 );

    TViewRT( ID3D11Device* pd3dDevice, ID3D11DeviceContext*    pImmediateContext,D3D11_TEXTURE2D_DESC* pTexDesc );
	TViewRT();
    virtual ~TViewRT();
};

