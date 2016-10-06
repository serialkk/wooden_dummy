#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <cassert>
#include <memory>
#include <iterator>
namespace DX
{
	class TDxState
	{
	public:
		static ID3D11RasterizerState* g_pRSWireFrame;
		static ID3D11RasterizerState* g_pRSSolid;
		static ID3D11RasterizerState* g_pRSBackCullSolid;
		static ID3D11RasterizerState* g_pRSNoneCullSolid;
		static ID3D11RasterizerState* g_pRSFrontCullSolid;
		static ID3D11RasterizerState* g_pRSSlopeScaledDepthBias;
		static ID3D11RasterizerState* g_pRS[6];		
		
		static ID3D11BlendState*	  g_pAlphaBlend;
		static ID3D11BlendState*	  g_pNoAlphaBlend;
		static ID3D11BlendState*	  g_pBSColorOne;
		static ID3D11BlendState*	  g_pBSOneOne;
		static ID3D11BlendState*	  g_pBSOneZero;
		static ID3D11BlendState*	  g_pBSAlphaOne;
		static ID3D11BlendState*	  g_pBSMaxOneOne;
		static ID3D11BlendState*      g_pBS[7];

		static ID3D11SamplerState*	  g_pTexSS;
		static ID3D11SamplerState*    g_pSSWrapLinear;
		static ID3D11SamplerState*    g_pSSWrapPoint;
		static ID3D11SamplerState*    g_pSSMirrorLinear;
		static ID3D11SamplerState*    g_pSSMirrorPoint;
		static ID3D11SamplerState*    g_pSSClampLinear;
		static ID3D11SamplerState*    g_pSSClampPoint;
		static ID3D11SamplerState*    g_pSSShadowMap;
		static ID3D11SamplerState*    g_pSS[8];

		static  ID3D11DepthStencilState*	g_pDSSDepthEnable;
		static  ID3D11DepthStencilState*	g_pDSSDepthDisable;
		static  ID3D11DepthStencilState*	g_pDSSDepthEnableNoWrite;
		static  ID3D11DepthStencilState*	g_pDSSDepthDisableNoWrite;		
		static  ID3D11DepthStencilState*	g_pDSSDepthStencilAdd;
		static  ID3D11DepthStencilState*	g_pDSSDepthAlways;
		static  ID3D11DepthStencilState*	g_pDSS[6];

		static HRESULT SetState(ID3D11Device*	pd3dDevice);
		static bool  Release();
	public:
		TDxState::~TDxState();
	};

	static void ApplyRS(ID3D11DeviceContext*   pContext,
		ID3D11RasterizerState* pState)
	{
		assert(pContext);
		pContext->RSSetState(pState);
	}
	static void ApplyDSS(ID3D11DeviceContext*   pContext,
		ID3D11DepthStencilState*	pDepthStencilState,
		UINT iRef = 0x01)
	{
		assert(pContext);
		pContext->OMSetDepthStencilState(pDepthStencilState, iRef);

	};
	static void ApplyBS(ID3D11DeviceContext*   pContext,
		ID3D11BlendState*      pBlendState,
		const FLOAT fBlendFactor[] = 0,
		UINT iMask = 0xffffffff)
	{
		assert(pContext);
		pContext->OMSetBlendState(pBlendState, fBlendFactor, iMask);
	}

	static void ApplySS(ID3D11DeviceContext*   pContext,	ID3D11SamplerState*      pSamplerState,  
		  UINT iSlot = 0, UINT iArray=1 )
	{
		assert(pContext);
		pContext->PSSetSamplers(iSlot, iArray, &pSamplerState);
	}
}