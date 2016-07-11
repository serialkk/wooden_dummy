#include "KDXHelperEx.h"
#include "KInput.h"

//ID3D11Buffer*		DX::g_pVertexBuffer;
//ID3D11Buffer*		DX::g_pIndexBuffer;
//ID3D11Buffer*		DX::g_pConstantBuffer;
//ID3D11VertexShader* DX::g_pVertexShader;
//ID3D11PixelShader*  DX::g_pPixelShader;
//ID3D11InputLayout*  DX::g_pInputlayout;
//ID3DBlob*			DX::g_pVSBlob;

HRESULT DX::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}
ID3D11VertexShader*   DX::LoadVertexShaderFile(
	ID3D11Device*  pd3dDevice,
	TCHAR* pLoadShaderFile,
	ID3DBlob** ppVSBlob)
{
	HRESULT hr = S_OK;
	ID3D11VertexShader* pVertexShader = NULL;
	hr = CompileShaderFromFile(
		pLoadShaderFile,
		"VS",
		"vs_5_0",
		ppVSBlob);

	if (FAILED(hr))
	{
		H(hr);
		return NULL;
	}
	ID3DBlob* pVSBlob = *ppVSBlob;
	// Create the vertex shader
	hr = pd3dDevice->CreateVertexShader(
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		NULL,
		&pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		H(hr);
		return NULL;
	}
	return pVertexShader;
};
ID3D11PixelShader*   DX::LoadPixelShaderFile(
	ID3D11Device*  pd3dDevice,
	TCHAR* pLoadShaderFile)
{
	HRESULT hr = S_OK;
	ID3D11PixelShader* pPixelShader = NULL;
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(
		pLoadShaderFile,
		"PS",
		"ps_5_0",
		&pPSBlob);
	if (FAILED(hr))
	{
		H(hr);
		return NULL;
	}

	// Create the pixel shader
	hr = pd3dDevice->CreatePixelShader(
		pPSBlob->GetBufferPointer(),
		pPSBlob->GetBufferSize(), NULL,
		&pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
	{
		H(hr);
		return NULL;
	}
	return pPixelShader;
}

ID3D11InputLayout* DX::CreateInputlayout(
	ID3D11Device*  pd3dDevice,
	D3D11_INPUT_ELEMENT_DESC layout[],
	UINT numElements,
	ID3DBlob* pVSBlob)
{
	HRESULT hr = S_OK;
	ID3D11InputLayout* pInputLayout = NULL;
	// Create the input layout
	hr = pd3dDevice->CreateInputLayout(layout,
		numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&pInputLayout);
	if (FAILED(hr))
	{
		H(hr);
		return NULL;
	}		
	return pInputLayout;
}
ID3D11Buffer* DX::CreateBuffer(
	ID3D11Device*  pd3dDevice,
	void *data,
	UINT iNumCount,
	UINT iSize,
	D3D11_BIND_FLAG bindFlag,
	bool bDynamic)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pBuffer = NULL;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	if (bDynamic)
	{
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
	}
	bd.ByteWidth = iSize * iNumCount;
	bd.BindFlags = bindFlag;
	InitData.pSysMem = data;

	if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &InitData,
		&pBuffer)))
	{
		H(hr);
		return NULL;
	}
		
	return pBuffer;
}

namespace DX
{
	ID3D11RasterizerState*   KDxState::g_pWireFrameRS = 0;
	ID3D11RasterizerState*   KDxState::g_pBackSolidRS = 0;
	ID3D11RasterizerState*   KDxState::g_pFrontSolidRS = 0;
	ID3D11RasterizerState*   KDxState::g_pNoneSolidRS = 0;
	ID3D11RasterizerState*   KDxState::g_pCullSolidRS[3] = { 0, };

	HRESULT KDxState::SetState(ID3D11Device* pDevice)
	{
		HRESULT hr = S_OK;
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pDevice->CreateRasterizerState(&rd,
			&g_pWireFrameRS)))
		{
			H(hr);
			return false;
		};
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pDevice->CreateRasterizerState(&rd,
			&g_pBackSolidRS)))
		{
			H(hr);
			return false;
		};
		g_pCullSolidRS[2] = g_pBackSolidRS;
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_FRONT;
		if (FAILED(hr = pDevice->CreateRasterizerState(&rd,
			&g_pFrontSolidRS)))
		{
			H(hr);
			return false;
		};
		g_pCullSolidRS[1] = g_pFrontSolidRS;
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_NONE;
		if (FAILED(hr = pDevice->CreateRasterizerState(&rd,
			&g_pNoneSolidRS)))
		{
			H(hr);
			return false;
		};
		g_pCullSolidRS[0] = g_pNoneSolidRS;
		return hr;
	}
	bool KDxState::Release()
	{
		if (g_pWireFrameRS) g_pWireFrameRS->Release();
		if (g_pBackSolidRS) g_pBackSolidRS->Release();
		if (g_pFrontSolidRS) g_pFrontSolidRS->Release();
		if (g_pNoneSolidRS) g_pNoneSolidRS->Release();
	
		return true;
	}


	KDXHelper::KDXHelper()
	{
		g_pVertexBuffer = NULL;
		g_pIndexBuffer = NULL;
		g_pConstantBuffer = NULL;
		g_pVertexShader = NULL;
		g_pPixelShader = NULL;
		g_pInputlayout = NULL;
		g_pVSBlob = NULL;
		m_bWireFrameRender = false;
		m_iPrimitiveType = 4;
		m_iCullMode = 0;
	}
	KDXHelper::~KDXHelper()
	{
		Release();
	}
	bool KDXHelper::Frame()
	{
		if (I_Input.KeyCheck(DIK_1) == KEY_UP)
		{
			m_bWireFrameRender = !m_bWireFrameRender;
		}
		if (I_Input.KeyCheck(DIK_2) == KEY_UP)
		{
			++m_iPrimitiveType;
			if (m_iPrimitiveType > 5)
			{
				m_iPrimitiveType = 1;
			}
			m_iPrimitiveType = min(m_iPrimitiveType, 5);
		}
		if (I_Input.KeyCheck(DIK_3) == KEY_UP)
		{
			++m_iCullMode;
			if (m_iCullMode > 3)
			{
				m_iCullMode = 1;
			}
			m_iCullMode = min(m_iCullMode, 3);
		}
		return true;
	}
	bool KDXHelper::Render(
		ID3D11DeviceContext*    pContext,
		UINT VertexSize, UINT VertexCount)
	{

		ApplyRS(pContext, KDxState::g_pCullSolidRS[m_iCullMode]);
		if( m_bWireFrameRender)
			ApplyRS(pContext, KDxState::g_pWireFrameRS);


		pContext->IASetPrimitiveTopology(
			(D3D11_PRIMITIVE_TOPOLOGY)m_iPrimitiveType);

		pContext->IASetInputLayout(
			g_pInputlayout);
		// Set vertex buffer
		UINT stride = VertexSize;
		UINT offset = 0;
		pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
		pContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);

		pContext->VSSetShader(g_pVertexShader, NULL, 0);
		pContext->PSSetShader(g_pPixelShader, NULL, 0);
		pContext->DrawIndexed(VertexCount, 0, 0);
		return true;
	}
	void  KDXHelper::Release()
	{
		if (g_pVertexBuffer) g_pVertexBuffer->Release();
		if (g_pIndexBuffer) g_pIndexBuffer->Release();
		if (g_pConstantBuffer) g_pConstantBuffer->Release();
		if (g_pVertexShader) g_pVertexShader->Release();
		if (g_pPixelShader) g_pPixelShader->Release();
		if (g_pInputlayout) g_pInputlayout->Release();
		if (g_pVSBlob) g_pVSBlob->Release();
		g_pVertexBuffer = NULL;
		g_pIndexBuffer = NULL;
		g_pConstantBuffer = NULL;
		g_pVertexShader = NULL;
		g_pPixelShader = NULL;
		g_pInputlayout = NULL;
		g_pVSBlob = NULL;
	}
}