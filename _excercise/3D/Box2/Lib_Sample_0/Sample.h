#pragma once
#pragma comment(lib,"TCoreDx_0.lib")
#include "TCoreDx.h"
#include "TDxBuffer.h"
#include "TShader.h"
#include <D3DX10math.h>

class Sample : public TCoreDx
{


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




	HRESULT InitDevice();
	void	CleanupDevice();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	//TObject				m_Object[MAX_OBJECT];
	//void    SetRect(RECT& rt, int iObj);
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	Sample();
	virtual ~Sample();
};

