#ifndef TBASIS_H
#define TBASIS_H	
	#define DIRECTINPUT_VERSION 0x0800
	#define _CRT_SECURE_NO_WARNINGS
	#ifndef UNICODE
	#error "TBASIS�� �����ڵ�� ������ �ؾ� �մϴ�."
	#endif
	#pragma warning( disable:4005)

	#include "TStructure.h"
	#include "TUtils.h"
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	extern ID3D11Device*           g_pd3dDevice;		// ����̽� ��ü
	extern IDXGISwapChain*         g_pSwapChain;		// ����ü�� ��ü
	extern ID3D11RenderTargetView* g_pRenderTargetView;// ���� ����Ÿ�� ��	
	extern IDXGIFactory*		   g_pGIFactory;		// DXGI ��ü
	extern ID3D11DeviceContext*    g_pImmediateContext;
	extern D3D_FEATURE_LEVEL       g_FeatureLevel;
	using namespace TBASIS_BASE;

#endif //TBASIS_H