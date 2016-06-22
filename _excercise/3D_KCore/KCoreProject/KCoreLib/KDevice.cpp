#include "KDevice.h"
HRESULT  KDevice::DeleteDXResouce()
{
	g_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if(g_pRenderTargetView ) g_pRenderTargetView->Release();
	return S_OK;
}
HRESULT  KDevice::CreateDXResouce()
{
	return S_OK;
}
bool   KDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	HRESULT hr;
	if (g_pd3dDevice == NULL || g_pSwapChain == NULL) return true;
	// 사전에 생성된 객체들을 삭제
	DeleteDXResouce();
	m_dwWidth = iWidth;
	m_dwHeight = iHeight;
	// 다시 크기를 조정해서 객체 생성	
	g_pSwapChain->GetDesc(&m_sd);
	if (FAILED(hr = g_pSwapChain->ResizeBuffers(
		m_sd.BufferCount,
		iWidth, iHeight,
		m_sd.BufferDesc.Format,
		m_sd.Flags)))
	{
		return false;
	}
	if (FAILED(hr = SetRenderTarget()))
	{
		return false;
	}
	if (FAILED(hr = SetViewPort()))
	{
		return false;
	}

	DXGI_SWAP_CHAIN_DESC sd;
	g_pSwapChain->GetDesc(&sd);
	return true;
}
HRESULT KDevice::SetRenderTarget()
{
	HRESULT hr = S_OK;
	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer,
		NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	return hr;
}
HRESULT KDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_dwWidth;
	vp.Height = (FLOAT)m_dwHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);
	return hr;
}
HRESULT KDevice::CreateGIFactory()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&g_pGIFactory)))
	{
		return  hr;
	}
	UINT i = 0;
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;
	while (g_pGIFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++i;
	}
	DXGI_ADAPTER_DESC desc;
	vAdapters[0]->GetDesc(&desc);

	i = 0;
	IDXGIOutput * pOutput;
	std::vector<IDXGIOutput*> vOutputs;
	while (vAdapters[0]->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND)
	{
		vOutputs.push_back(pOutput);
		++i;
	}
	DXGI_OUTPUT_DESC od;
	vOutputs[0]->GetDesc(&od);
	vOutputs[1]->GetDesc(&od);
	return hr;
}
HRESULT KDevice::InitSwapChain()
{
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_dwWidth = rc.right - rc.left;
	m_dwHeight = rc.bottom - rc.top;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_dwWidth;
	sd.BufferDesc.Height = m_dwHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = g_pGIFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain)))
	{
		return hr;
	}
	return hr;
}
HRESULT KDevice::IniKDevice()
{
	HRESULT hr = S_OK;
#pragma region Device
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	IDXGIAdapter* pAdapter = NULL;
	g_pGIFactory->EnumAdapters(0, &pAdapter);


	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes;
	driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(pAdapter,
			g_driverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION,
			&g_pd3dDevice, &g_featureLevel,
			&g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

#pragma endregion 
	return S_OK;
}
//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void KDevice::CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
	if (g_pGIFactory) g_pGIFactory->Release();
}

KDevice::KDevice()
{
}


KDevice::~KDevice()
{
}
