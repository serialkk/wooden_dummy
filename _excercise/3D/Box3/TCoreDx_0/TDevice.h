#pragma once
#include "TDxStd.h"
#include "TWindow.h"
#include "TInput.h"
#include "TTimer.h"

#include <D3Dcompiler.h>

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR4 Color;
};


struct ConstantBuffer
{
	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;
};

class TDevice : public TWindow
{
public:


	TInput m_Input;
	TTimer m_Timer;
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
	ID3D11VertexShader*     g_pVertexShader = NULL;
	ID3D11PixelShader*      g_pPixelShader = NULL;
	ID3D11InputLayout*      g_pVertexLayout = NULL;
	ID3D11Buffer*           g_pVertexBuffer = NULL;
	//아래 2개 인터페이스가 추가가됨.(필요한 버퍼: 정점, 인덱스, 상수 버퍼.)
	ID3D11Buffer*           g_pIndexBuffer = NULL; //인덱스 버퍼
	ID3D11Buffer*           g_pConstantBuffer = NULL; //상수 버퍼

	D3DXMATRIX                g_World;
	D3DXMATRIX                g_View;
	D3DXMATRIX                g_Projection;

	bool PreRender();
	bool PostRender();	
	bool	GameRun();
	bool	GameInit(); 
	bool   GameRelease();
public:


	HRESULT InitDevice();
	void	CleanupDevice();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

	TDevice();
	virtual ~TDevice();
};

