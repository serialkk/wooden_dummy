#include "Sample.h"


D3DXVECTOR3            g_Eye;
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT Sample::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT Sample::InitDevice()
{
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

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);

	// Compile the vertex shader
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial04.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial04.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f) },//0
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f) }, //1
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f) },  //2
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) }, //3
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f) },//4
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f) }, //5
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f) }, //6
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f) }, //7
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Create index buffer
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};

	//인덱스버퍼와 정점버퍼의 차이는 크기와 데이터만 달라진다
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0; // CPU가 GPU의 메모리에 엑세스 할 수 있는지에 대한 flag .
	InitData.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pConstantBuffer);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrix
	D3DXMatrixIdentity(&g_World );

	// Initialize the view matrix
	D3DXVECTOR3 Eye = D3DXVECTOR3(0.0f, 0.0f, 35.0f);
	D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_View,&Eye, &At, &Up);

	// Initialize the projection matrix
	D3DXMatrixPerspectiveFovLH(&g_Projection, D3DX_PI * 0.5f, width / (FLOAT)height, 0.01f, 100.0f);

	g_Eye.x = 0.0f;
	g_Eye.y = 0.0f;
	g_Eye.z = -5.0f;

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void Sample::CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();

	if (g_pConstantBuffer) g_pConstantBuffer->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}


bool	Sample::Init()
{

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}
	

	return true;
}
bool	Sample::Render()
{
	HRESULT hr;


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

	//
	// Update variables
	//
	//ConstantBuffer cb;
	//D3DXMatrixTranspose(&cb.mWorld,&g_World);
	//D3DXMatrixTranspose(&cb.mView,&g_View);
	//D3DXMatrixTranspose(&cb.mProjection,&g_Projection);
	//g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	//
	// Renders a triangle
	//
	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);

	//
	g_pImmediateContext->DrawIndexed(36, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list

													   //
													   // Present our back buffer to our front buffer
													   //
	g_pSwapChain->Present(0, 0);

	return true;
}
bool    Sample::Frame()
{
	HRESULT hr;

	//Clear constant buffer
	//단위행렬로 월드 행렬을 만듦.
	D3DXMatrixIdentity(&cb_game.mWorld);

	TCHAR buf[80];

	if (m_Input.KeyCheck('W') == KEY_HOLD){
		g_Eye.z += 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD){
		g_Eye.z -= 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('A') == KEY_HOLD) {
		g_Eye.x -= 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD) {
		g_Eye.x += 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}





	//D3DXVECTOR3 Eye = D3DXVECTOR3(0.0f, 0.0f, -5.0f); // 카메라의 위치
	//g_Eye.z = 10.00f;
	D3DXVECTOR3 Eye = g_Eye;
	D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 카메라가 보는 
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&cb_game.mView, &Eye, &At, &Up);// 뷰 행렬 계산





													   // 투영 행렬 계산
													   // (D3DXMATRIX *pOut,  계산된 투영 행렬 반환
	FLOAT fovy = D3DX_PI * 0.5f;  // 시야각
	FLOAT Aspect = 800.0f / 600.0f;// 화면 비율( 1.33f )
	FLOAT zn = 0.1f; // 근단면 거리
	FLOAT zf = 1000.0f;   // 원단면 거리

	D3DXMatrixPerspectiveFovLH(&cb_game.mProjection, fovy, Aspect, zn, zf); // ==>> 투영 좌표


																	  // 전치 행렬 변환
																	  // Update variables
	D3DXMatrixTranspose(&cb.mWorld, &cb_game.mWorld);
	D3DXMatrixTranspose(&cb.mView, &cb_game.mView);
	D3DXMatrixTranspose(&cb.mProjection, &cb_game.mProjection);

	// Update constant buffer in every frame
	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	return true;
}
bool	Sample::Release()
{

	CleanupDevice();

	return true;
}

Sample::Sample()
{
}

Sample::~Sample()
{

}
TCORE_RUN(DxSample_1, 800, 600)
//TCORE_START;
//if (sample.SetWindow(hInstance,
//	L"SampleScene_0", 800, 600, WS_POPUPWINDOW))
//{
//	sample.Run();
//}
//TCORE_END;