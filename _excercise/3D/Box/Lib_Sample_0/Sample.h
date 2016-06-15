#pragma once
#pragma comment(lib,"TCoreDx_0.lib")
#include "TCoreDx.h"
#include "TDxBuffer.h"
#include "TShader.h"
#include <xnamath.h>
/*
//#define USED_ONLY_VERTEX
#define MAX_OBJECT 3
struct P_VERTEX
{
	float x, y, z; // 위치
};
struct VS_CONSTANT_BUFFER
{
	float x, y, z, w;
	float time; // 컬러 // 레지스터 단위 (float*4)
	float a, b, c;
};
struct TObject
{
	VS_CONSTANT_BUFFER m_Data;
	P_VERTEX			m_VertexList[6];
	DWORD				m_IndexList[6];
	VS_CONSTANT_BUFFER	m_ConstantList;
	TDxBuffer			m_VB;
	TDxBuffer			m_IB;
	TDxBuffer			m_CB;
	INT					m_iVS;
	INT					m_iPS;
	TShader*			m_pVS;
	TShader*			m_pPS;
	ID3D11InputLayout*  m_pIL;
};
*/
class Sample : public TCoreDx
{


	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};


	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
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

	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;




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

