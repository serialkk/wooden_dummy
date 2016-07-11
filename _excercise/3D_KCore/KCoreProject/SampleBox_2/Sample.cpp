#include "Sample.h"


bool Sample::Init() { 
	
	HRESULT hr;

	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
		g_pd3dDevice,
		L"../../data/Front.bmp",
		NULL, NULL, &m_pTexSRV[0], NULL)))
	{
		H(hr);
		return false;
	}
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
		g_pd3dDevice,
		L"../../data/checker_with_numbers.bmp",
		NULL, NULL, &m_pTexSRV[1], NULL)))
	{
		H(hr);
		return false;
	}
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
		g_pd3dDevice,
		L"../../data/Splash.jpg",
		NULL, NULL, &m_pTexSRV[2], NULL)))
	{
		H(hr);
		return false;
	}
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
		g_pd3dDevice,
		L"../../data/Back.bmp",
		NULL, NULL, &m_pTexSRV[3],
		NULL)))
	{
		H(hr);
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	m_pTexSRV[0]->GetDesc(&srvd);
	int iMaxLod = srvd.Texture2D.MipLevels;

	if (m_pSamplerState)m_pSamplerState->Release();
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_ANISOTROPIC;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = 0.0f;
	sd.BorderColor[1] = 0.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 1.0f;
	sd.MaxAnisotropy = 16;
	sd.MinLOD = 0;
	sd.MaxLOD = 0;
	if (FAILED(hr = g_pd3dDevice->CreateSamplerState(&sd, &m_pSamplerState)))
	{
		H(hr);
		return false;
	}

#pragma region g_pVertexShader
	m_Object.g_pVertexShader = LoadVertexShaderFile(g_pd3dDevice, L"Shader.hlsl", &m_Object.g_pVSBlob);
#pragma endregion

	return true; 
}
bool Sample::Frame() { 



	return true;
}
bool Sample::Render() { 
	
	
	return true; 
}
bool Sample::Release() { 
	
	
	return true; 
}

Sample::Sample()
{
}


Sample::~Sample()
{
}
KCORE_RUN(_T("Sample Lib"), 800, 600)