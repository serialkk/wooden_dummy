#include "TShape.h"

void   TShape::SetMatrix(D3DXMATRIX* pWorld,
	D3DXMATRIX* pView,
	D3DXMATRIX* pProj)
{
	m_matWorld = *pWorld;
	m_matView = *pView;
	m_matProj= *pProj;
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}
HRESULT TShape::LoadShaderResourceView(TCHAR* pTextureFile)		
{
	m_Object.g_pTexSRV =
		CreateShaderResourceView(m_pd3dDevice,
			pTextureFile);
	return S_OK;
}
HRESULT TShape::LoadShaderFile(TCHAR* pShaderFile)
{
	m_Object.g_pVertexShader =
		LoadVertexShaderFile(m_pd3dDevice,
			pShaderFile,
			&m_Object.g_pVSBlob);
	m_Object.g_pPixelShader =
		DX::LoadPixelShaderFile(m_pd3dDevice,
			pShaderFile);
	return S_OK;
}

HRESULT TShape::CreateConstantBuffer()
{
	m_Object.g_pConstantBuffer =
		CreateBuffer(g_pd3dDevice, &m_cbData,
			1, sizeof(VS_CONSTANT_BUFFER),
			D3D11_BIND_CONSTANT_BUFFER);
	return S_OK;
}
bool  TShape::Create(ID3D11Device* pd3dDevice,
	TCHAR* pShaderFile,
	TCHAR* pTextureFile)
{
	HRESULT hr = S_OK;
	m_pd3dDevice = pd3dDevice;
#pragma region CreateVertexBuffer
	if (FAILED(hr= CreateVertexBuffer()))
	{
		return false;
	}
#pragma endregion
#pragma region CreateIndexBuffer
	if (FAILED(hr = CreateIndexBuffer()))
	{
		return false;
	}
#pragma endregion
#pragma region g_pConstantBuffer
	if (FAILED(hr = CreateConstantBuffer()))
	{
		return false;
	}
#pragma endregion
#pragma region LoadShaderFile
	if (FAILED(hr = LoadShaderFile(pShaderFile)))
	{
		return false;
	}
#pragma endregion
#pragma region g_pInputlayout
	if (FAILED(hr = SetInputlayout()))
	{
		return false;
	}
#pragma endregion
#pragma region LoadShaderResourceView
	if (FAILED(hr = LoadShaderResourceView(pTextureFile)))
	{
		return false;
	}
#pragma endregion
	
	return true;
}
bool TShape::Render(ID3D11DeviceContext*   pContext)
{
	pContext->UpdateSubresource(
		m_Object.g_pConstantBuffer, 0, NULL,
		&m_cbData, 0, 0);

	ApplySS(pContext,KDxState::g_pSamplerState);

	m_Object.Render(pContext, 
		m_Object.m_iVertexSize, 
		m_Object.m_iNumIndex);
	return true;
}
TShape::TShape()
{

}


TShape::~TShape()
{
}

HRESULT TPlaneShape::CreateVertexBuffer()
{
	HRESULT hr=S_OK;
#pragma region g_pVertexBuffer
	m_VertexList.resize(4);
	m_VertexList[0] = PCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	m_Object.m_iNumVertex = m_VertexList.size();
	m_Object.m_iVertexSize = sizeof(PCT_VERTEX);
	m_Object.g_pVertexBuffer =
		DX::CreateBuffer(g_pd3dDevice, 
			&m_VertexList.at(0),
			m_Object.m_iNumVertex, 
			m_Object.m_iVertexSize,
			D3D11_BIND_VERTEX_BUFFER);
	if (m_Object.g_pVertexBuffer == nullptr)
	{
		return E_FAIL;
	}
#pragma endregion
	return hr;
}

HRESULT TPlaneShape::CreateIndexBuffer()
{
	HRESULT hr=S_OK;

	m_IndexList.resize(6);
	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 0;
	m_IndexList[4] = 2;
	m_IndexList[5] = 3;
	
	m_Object.m_iNumIndex = m_IndexList.size();
	m_Object.g_pIndexBuffer =
		CreateBuffer(g_pd3dDevice, &m_IndexList.at(0),
			m_Object.m_iNumIndex, sizeof(DWORD),
			D3D11_BIND_INDEX_BUFFER);
	if (m_Object.g_pIndexBuffer == nullptr)
	{
		return E_FAIL;
	}
#pragma endregion
	return hr;
}

HRESULT TPlaneShape::SetInputlayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	m_Object.g_pInputlayout = CreateInputlayout(g_pd3dDevice,
		layout, numElements,
		m_Object.g_pVSBlob);
	return S_OK;
}