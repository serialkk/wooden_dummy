#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <cassert>
//#include <assert.h>

class TDxState
{
public:
	static ID3D11RasterizerState* g_pRSWireFrame;
	static ID3D11RasterizerState* g_pRSSolid;
	static ID3D11RasterizerState* g_pRSBackCullSolid;
	static ID3D11RasterizerState* g_pRSNoneCullSolid;
	static ID3D11RasterizerState* g_pRSFrontCullSolid;
	static ID3D11DepthStencilState* g_pEnableDSS;
	static ID3D11DepthStencilState* g_pDisableDSS;
	static ID3D11SamplerState*	   g_pTexSS;
	static ID3D11BlendState*	  g_pAlphaBlend;
	static ID3D11BlendState*	  g_pNoAlphaBlend;
	static ID3D11BlendState*	  g_pColorBlend;
	static HRESULT SetState(ID3D11Device*	pd3dDevice);
	static bool  Release();
};

static void ApplyRS(	ID3D11DeviceContext*   pImmediateContext, 
						ID3D11RasterizerState* pState )
{
	assert( pImmediateContext );
	pImmediateContext->RSSetState( pState );
}
static void ApplyDSS(	ID3D11DeviceContext*   pImmediateContext, 
							ID3D11DepthStencilState*	pDepthStencilState,
							UINT iRef = 0x01)
{
	assert( pImmediateContext );
	pImmediateContext->OMSetDepthStencilState( pDepthStencilState, iRef );	 	

};
static void ApplyBS(ID3D11DeviceContext*   pImmediateContext,
					ID3D11BlendState*      pBlendState,
					const FLOAT fBlendFactor[] = 0, 
					UINT iMask = 0xffffffff )
{
	assert( pImmediateContext );
	pImmediateContext->OMSetBlendState( pBlendState, fBlendFactor, iMask );
}