#ifndef TBASIS_H
#define TBASIS_H	
	#define DIRECTINPUT_VERSION 0x0800
	#define _CRT_SECURE_NO_WARNINGS
	#ifndef UNICODE
	#error "TBASIS는 유니코드로 컴파일 해야 합니다."
	#endif
	#pragma warning( disable:4005)

	#include "TStructure.h"
	#include "TUtils.h"
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	extern ID3D11Device*           g_pd3dDevice;		// 디바이스 객체
	extern IDXGISwapChain*         g_pSwapChain;		// 스왑체인 객체
	extern ID3D11RenderTargetView* g_pRenderTargetView;// 메인 랜더타켓 뷰	
	extern IDXGIFactory*		   g_pGIFactory;		// DXGI 객체
	extern ID3D11DeviceContext*    g_pImmediateContext;
	extern D3D_FEATURE_LEVEL       g_FeatureLevel;
	using namespace TBASIS_BASE;

#endif //TBASIS_H