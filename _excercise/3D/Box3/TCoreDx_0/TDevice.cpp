#include "TDevice.h"

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------

bool  TDevice::ResizeClient(UINT iWidth, UINT iHeight)
{
	if (g_pSwapChain == NULL || g_pd3dDevice == NULL) return true;
	
	HRESULT hr;

	//--------------------------------------------------------------------------------------
	// 랜더타켓과 깊이스텐실 버퍼를 해제한다.
	//--------------------------------------------------------------------------------------
	g_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (g_pRenderTargetView) g_pRenderTargetView->Release();

	//--------------------------------------------------------------------------------------
	// 백버퍼의 크기를 조정한다.
	//--------------------------------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	g_pSwapChain->GetDesc(&CurrentSD);
	hr = g_pSwapChain->ResizeBuffers(CurrentSD.BufferCount,
		iWidth, iHeight,
		CurrentSD.BufferDesc.Format,
		CurrentSD.Flags);
	if (FAILED(hr))
	{
		//DXTRACE_ERR_MSGBOX( DXGetErrorDescription(hr),hr);
	}

	// 랜더타켓뷰 생성 및 적용한다.
	if (FAILED(hr = SetRenderTargetView()))
	{
		return hr;
	}
	// 뷰포트를 세팅하고 적용한다.
	if (FAILED(hr = SetViewPort()))
	{
		return hr;
	}
	return S_OK;
}

//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateGIFactory()
{
	HRESULT hr;
	if (g_pd3dDevice == NULL) return E_FAIL;
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)&g_pGIFactory)))
	{
		//DXTRACE_ERR_MSGBOX( DXGetErrorDescription(hr),hr);
	}

	//HRESULT hr;// = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory) );
	//IDXGIDevice * pDXGIDevice;
	//hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	//     
	//IDXGIAdapter * pDXGIAdapter;
	//hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	//IDXGIFactory * pIDXGIFactory;
	//pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pGIFactory);
	//
	//pDXGIDevice->Release();
	//pDXGIAdapter->Release();
	return hr;
}

HRESULT		TDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	// Create a render target view
	ID3D11Texture2D* pBackBuffer;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	return hr;


	//// Create a render target view
	//ID3D11Texture2D* pBackBuffer = NULL;
	//hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//if (FAILED(hr))
	//	return hr;

	//hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	//pBackBuffer->Release();
	//if (FAILED(hr))
	//	return hr;

	//g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
}
HRESULT		TDevice::SetViewPort()
{
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC Desc;
	g_pSwapChain->GetDesc(&Desc);

	// Setup the viewport    
	g_ViewPort.Width = Desc.BufferDesc.Width;
	g_ViewPort.Height = Desc.BufferDesc.Height;
	g_ViewPort.MinDepth = 0.0f;
	g_ViewPort.MaxDepth = 1.0f;
	g_ViewPort.TopLeftX = 0;
	g_ViewPort.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &g_ViewPort);


	//// Setup the viewport
	//D3D11_VIEWPORT vp;
	//vp.Width = (FLOAT)width;
	//vp.Height = (FLOAT)height;
	//vp.MinDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//g_pImmediateContext->RSSetViewports(1, &vp);

	return hr;
}
HRESULT TDevice::CreateDevice() {
	HRESULT hr = S_OK;

	RECT rc;

	GetClientRect(m_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
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

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;
}
HRESULT TDevice::InitDevice()
{
	


	BOOL IsFullScreen = true;
	RECT rc;

	GetClientRect(m_hWnd, &rc);
	UINT iWidth = rc.right - rc.left;
	UINT iHeight = rc.bottom - rc.top;







	// Initialize the world matrix
	D3DXMatrixIdentity(&g_World);

	// Initialize the view matrix
	D3DXVECTOR3 Eye = D3DXVECTOR3(0.0f, 0.0f, 35.0f);
	D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up);

	// Initialize the projection matrix
	D3DXMatrixPerspectiveFovLH(&g_Projection, D3DX_PI * 0.5f, iWidth / (FLOAT)iHeight, 0.01f, 100.0f);








	HRESULT hr = S_OK;
	if (FAILED(hr = CreateDevice()))
	{
		MessageBox(0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK);
		return hr;
	}

	if (FAILED(hr = CreateSwapChain(m_hWnd, iWidth, iHeight, IsFullScreen)))
	{
		MessageBox(0, _T("CreateSwapChain  실패"), _T("Fatal error"), MB_OK);
		return hr;
	}

	if (FAILED(hr = SetRenderTargetView()))
	{
		MessageBox(0, _T("SetRenderTargetView  실패"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = SetViewPort()))
	{
		MessageBox(0, _T("SetViewPort  실패"), _T("Fatal error"), MB_OK);
		return hr;
	}

	// Alt + Enter 키를 막는다.
	//if (FAILED(hr = g_pGIFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	//{
	//	return hr;
	//}

	return S_OK;
}
IDXGIFactory* TDevice::GetGIFactory()
{
	assert(g_pGIFactory);
	return g_pGIFactory;
}
void TDevice::SetFullScreenFlag(BOOL bFlag)
{
	m_IsFullScreenMode = bFlag;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr = S_OK;
	SetFullScreenFlag(IsFullScreen);
	if (g_pGIFactory == NULL) return S_FALSE;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = iWidth;
	sd.BufferDesc.Height = iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = !m_IsFullScreenMode;
	// 추가
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = g_pGIFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain)))
	{
		return hr;
	}
	return hr;
}
//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void	TDevice::CleanupDevice()
{
	// 초기 풀스크린윈도우에서 응용프로그램이 닫히는 경우에는 윈도우 전환 후에 
	// 객체들을 소멸해야 한다. (메모리 누수를 막을 수 있다.)
	g_pSwapChain->SetFullscreenState(false, NULL);

	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();

	g_pd3dDevice = NULL;
	g_pSwapChain = NULL;
	g_pRenderTargetView = NULL;
	g_pImmediateContext = NULL;
	g_pGIFactory = NULL;
}
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT TDevice::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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



bool	TDevice::Init() { 
	


	return true; 
}

bool	TDevice::Frame() { 
	
	return true; }

bool	TDevice::PreRender() {

	// Update our time
	static float t = 0.0f;
	if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)D3DX_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	//
	// Animate the cube
	//
	//g_World = XMMatrixRotationY(t);
	//g_World = XMMatrixRotationX(t);

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

	return true;
}
bool TDevice::PostRender() {
	g_pSwapChain->Present(0, 0);
	return true;
}
bool	TDevice::Render() { 

	return true; 
}

bool	TDevice::GameRun() { 
	m_Timer.Frame();
	m_Input.Frame();
	PreRender();
	Frame();
	Render();
	PostRender();

	return true; };
bool	TDevice::GameInit() { 

	m_Input.Init();
	m_Timer.Init();
	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}
	Init();

	return true; 
};
bool   TDevice::GameRelease() { 
	Release();
	CleanupDevice();
	m_Input.Release();
	m_Timer.Release();

	return true; 
};


bool	TDevice::Release() { 
	
	return true; }

TDevice::TDevice()
{
	g_driverType = D3D_DRIVER_TYPE_NULL;
	//g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	g_pd3dDevice = NULL;
	g_pSwapChain = NULL;
	g_pRenderTargetView = NULL;
	g_pImmediateContext = NULL;
	g_pGIFactory = NULL;
}


TDevice::~TDevice()
{
}
