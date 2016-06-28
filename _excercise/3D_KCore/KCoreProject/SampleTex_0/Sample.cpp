#include "Sample.h"

bool	Sample::Init()
{
#pragma region g_pVertexShader
	m_Object.g_pVertexShader =
		LoadVertexShaderFile(g_pd3dDevice,
			L"Shader.hlsl",
			&m_Object.g_pVSBlob);
#pragma endregion
#pragma region g_pPixelShader
	m_Object.g_pPixelShader =
		DX::LoadPixelShaderFile(g_pd3dDevice, L"Shader.hlsl");
#pragma endregion
#pragma region g_pInputlayout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,28,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	m_Object.g_pInputlayout = CreateInputlayout(g_pd3dDevice,
		layout, numElements,
		m_Object.g_pVSBlob);
#pragma endregion
#pragma region g_pVertexBuffer
	SimpleVertex vertices[] =
	{
		//  0, 1, 2
		//  0, 2, 3
		// 0,╩С,аб
		-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		// 1,╩С,©Л
		0.5f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		// 2,го,©Л
		0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		// 3,го,аб
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	};

	int iNumVertex = sizeof(vertices) / sizeof(vertices[0]);
	m_Object.g_pVertexBuffer =
		DX::CreateBuffer(g_pd3dDevice, vertices,
			iNumVertex, sizeof(SimpleVertex),
			D3D11_BIND_VERTEX_BUFFER);
#pragma endregion
#pragma region g_pIndexBuffer
	DWORD indices[] = { 0,1,2, 0,2,3, };
	int iNumIndex = sizeof(indices) / sizeof(indices[0]);
	m_Object.g_pIndexBuffer =
		CreateBuffer(g_pd3dDevice, indices,
			iNumIndex, sizeof(DWORD),
			D3D11_BIND_INDEX_BUFFER);
#pragma endregion
#pragma region g_pConstantBuffer
	m_Object.g_pConstantBuffer =
		CreateBuffer(g_pd3dDevice, &m_cbData,
			1, sizeof(VS_CONSTANT_BUFFER),
			D3D11_BIND_CONSTANT_BUFFER,
			true);
#pragma endregion

	HRESULT hr;
	
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
		g_pd3dDevice,
		L"../../data/checker_with_numbers.bmp", 
		NULL, NULL, &m_pTexSRV, 
		NULL)))
	{
		H(hr);
		return false;
	}
	
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = 0.0f;
	sd.BorderColor[1] = 0.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 1.0f;
	if (FAILED(hr = g_pd3dDevice->CreateSamplerState(&sd, &m_pSamplerState)))
	{
		H(hr);
		return false;
	}
	return true;
}
bool	Sample::Frame() {
	return m_Object.Frame();
}
bool	Sample::Render() {
	g_pImmediateContext->PSSetConstantBuffers(0, 1,
		&m_Object.g_pConstantBuffer);

	g_pImmediateContext->PSSetShaderResources(0, 1,
			&m_pTexSRV);
	
	g_pImmediateContext->PSSetSamplers(0, 1,
		&m_pSamplerState);

	m_Object.Render(g_pImmediateContext,
		sizeof(SimpleVertex), 6);
	return true;
}
bool	Sample::Release() {

	if (m_pTexSRV) m_pTexSRV->Release();
	if (m_pSamplerState) m_pSamplerState->Release();
	m_Object.Release();
	return true;
}

Sample::Sample()
{
	m_cbData.r = 1.0f;
	m_cbData.g = 0.0f;
	m_cbData.b = 0.0f;
	m_cbData.a = 1.0f;
}


Sample::~Sample()
{
}
KCORE_RUN(_T("Sample Lib"), 800, 600)