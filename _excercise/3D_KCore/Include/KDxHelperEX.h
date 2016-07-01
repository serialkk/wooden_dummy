#pragma once
#include "KDxHelper.h"
namespace DX
{
	class KDxState
	{
	public:
		static ID3D11RasterizerState*   g_pWireFrameRS;
		static ID3D11RasterizerState*   g_pBackSolidRS;
		static ID3D11RasterizerState*   g_pFrontSolidRS;
		static ID3D11RasterizerState*   g_pNoneSolidRS;
		static ID3D11RasterizerState*   g_pCullSolidRS[3];

		static HRESULT SetState(ID3D11Device* pDevice);
		static bool Release();
	};

	static void ApplyRS(
		ID3D11DeviceContext*    pContext,
		ID3D11RasterizerState*  pRasterState)
	{
		pContext->RSSetState(pRasterState);
	}

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	ID3D11VertexShader* LoadVertexShaderFile(
		ID3D11Device*  pd3dDevice,
		TCHAR* pLoadShaderFile,
		ID3DBlob** ppVSBlob);
	ID3D11PixelShader* LoadPixelShaderFile(ID3D11Device*  pd3dDevice, TCHAR* pLoadShaderFile);
	ID3D11InputLayout* CreateInputlayout(
		ID3D11Device*  pd3dDevice,
		D3D11_INPUT_ELEMENT_DESC layout[],
		UINT numElements,
		ID3DBlob* pVSBlob);

	ID3D11Buffer* CreateBuffer(
		ID3D11Device*  pd3dDevice,
		void *data,
		UINT iNumCount,
		UINT iSize,
		D3D11_BIND_FLAG bindFlag,
		bool bDynamic = false);

	class KDXHelper
	{
	public:
		KDXHelper::KDXHelper();
		KDXHelper::~KDXHelper();
		ID3D11Buffer*		g_pVertexBuffer;
		ID3D11Buffer*		g_pIndexBuffer;
		ID3D11Buffer*		g_pConstantBuffer;
		ID3D11VertexShader* g_pVertexShader;
		ID3D11PixelShader*  g_pPixelShader;
		ID3D11InputLayout*  g_pInputlayout;
		ID3DBlob*			g_pVSBlob;
		bool m_bWireFrameRender;
		int m_iPrimitiveType;
		int m_iCullMode;
	public:
		bool Frame();
		bool Render(ID3D11DeviceContext*    pContext, UINT VertexSize, UINT VertexCount);
		void  Release();
	};
}