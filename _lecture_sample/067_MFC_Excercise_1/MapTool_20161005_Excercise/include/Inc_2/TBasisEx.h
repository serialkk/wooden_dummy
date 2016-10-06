#ifndef TBASIS_EXTERN_H
#define TBASIS_EXTERN_H
#include <d3dx11.h> 
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	extern ID3D11Device*           g_pd3dDevice;		// 디바이스 객체
	extern IDXGISwapChain*         g_pSwapChain;		// 스왑체인 객체
	extern ID3D11RenderTargetView* g_pRenderTargetView;// 메인 랜더타켓 뷰	
	extern IDXGIFactory*		   g_pGIFactory;		// DXGI 객체
	extern ID3D11DeviceContext*    g_pImmediateContext;
	extern D3D_FEATURE_LEVEL       g_FeatureLevel;
#endif