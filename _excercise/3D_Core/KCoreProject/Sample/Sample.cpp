#include "Sample.h"
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR4 Color0;
	D3DXVECTOR4 Color1;
};
// �������
// ����� ���Ǵ� ����
// ��ǥ�� ��ȯ�� ���ؼ� ����Ѵ�.
struct ConstantBuffer
{
	D3DXMATRIX mWorld; // ���� ���
	D3DXMATRIX mView;  // ��(ī�޶�)  ���
	D3DXMATRIX mProj;  // ���� ���
};
ConstantBuffer cb;
ConstantBuffer cb_game;
D3DXVECTOR3 g_Eye;
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
bool	Sample::ResizeClient(UINT iWidth, UINT iHeight)
{
	GetClientRect(m_hWnd, &m_rtWindow);
	g_rtWindow = m_rtWindow;
	// ���� ��� ���
	// (D3DXMATRIX *pOut,  ���� ���� ��� ��ȯ
	FLOAT fovy = D3DX_PI * 0.5f;  // �þ߰�
	FLOAT Aspect = m_dwWidth / (float)m_dwHeight;// ȭ�� ����( 1.33f )
	FLOAT zn = 1.0f; // �ٴܸ� �Ÿ�
	FLOAT zf = 10000.0f;   // ���ܸ� �Ÿ�
	D3DXMatrixPerspectiveFovLH(&cb_game.mProj, fovy, Aspect, zn, zf);

	return ResizeDevice(iWidth, iHeight);
}
//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
bool Sample::Init()
{
	HRESULT hr;

	hr = g_pGIFactory->MakeWindowAssociation( m_hWnd,
		DXGI_MWA_NO_PRINT_SCREEN | DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr))
	{
		return hr;
	}

	// font 
	IDXGISurface1*  pSurface;
	hr = g_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface1),
		(LPVOID*)&pSurface);	
	m_Font.Set(pSurface);
	pSurface->Release();

	D3DXMatrixIdentity(&cb.mWorld); 
	D3DXMatrixIdentity(&cb.mView);
	D3DXMatrixIdentity(&cb.mProj);

	// ���� ��� ���
	// (D3DXMATRIX *pOut,  ���� ���� ��� ��ȯ
	FLOAT fovy = D3DX_PI * 0.5f;  // �þ߰�
	FLOAT Aspect = m_dwWidth / (float)m_dwHeight;// ȭ�� ����( 1.33f )
	FLOAT zn = 1.0f; // �ٴܸ� �Ÿ�
	FLOAT zf = 10000.0f;   // ���ܸ� �Ÿ�
	D3DXMatrixPerspectiveFovLH(&cb_game.mProj, fovy, Aspect, zn, zf);


	g_Eye.x = 0.0f;
	g_Eye.y = 0.0f;
	g_Eye.z = -35.0f;
	//// ������۸� �ʱ�ȭ	
	//// ������ķ� ���� ����� �����.
	//D3DXMatrixIdentity(&cb.mWorld); 
	//D3DXMatrixRotationY(&cb.mWorld, D3DXToRadian(180.0f));// m_Timer.m_fAccumulation);
	//// �� ��� ���
	//D3DXVECTOR3 Eye = D3DXVECTOR3(0.0f, 0.0f, 35.0f);
	//D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXMatrixLookAtLH(&cb.mView, &Eye, &At, &Up);
	//// ���� ��� ���
	//// (D3DXMATRIX *pOut,  ���� ���� ��� ��ȯ
	//FLOAT fovy = D3DX_PI * 0.5f;  // �þ߰�
	//FLOAT Aspect = 800.0f / 600.0f;// ȭ�� ����( 1.33f )
	//FLOAT zn = 1.0f; // �ٴܸ� �Ÿ�
	//FLOAT zf = 10000.0f;   // ���ܸ� �Ÿ�
	//D3DXMatrixPerspectiveFovLH(&cb.mProj, fovy, Aspect, zn, zf);

	//// ��ġ ��� ��ȯ
	//D3DXMatrixTranspose(&cb.mWorld, &cb.mWorld);
	//D3DXMatrixTranspose(&cb.mView, &cb.mView);
	//D3DXMatrixTranspose(&cb.mProj, &cb.mProj);
	// Compile the vertex shader
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(
		L"hlsl.xx",
		"VShader",
		"vs_4_0",
		&pVSBlob);

	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader(
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		NULL,
		&g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLORa",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLORb",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,28,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	// NUM = sizeof(layout) / sizeof(layout[0])
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout,
		numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;


	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"hlsl.xx", "PS", "ps_4_0", &pPSBlob);
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
	//  ������ǥ��
	//      0,0                 800,0
	//   -1.0f, 1.0f,       1.0f,1.0f
	//
	//           0.0f, 0.0f
	//
	//   0, 600                 800, 600
	//  -1.0f, -1.0f           1.0f, -1.0f
	// ��Į ��ǥ��
	SimpleVertex vertices[] =
	{
		//  0, 1, 2
		//  0, 2, 3
		// 0,��,��
		D3DXVECTOR3(-10.5f, 10.5f, 0.0f),	D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		// 1,��,��
		D3DXVECTOR3(10.5f, 10.5f, 0.0f),	D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		// 2,��,��
		D3DXVECTOR3(10.5f, -10.5f, 0.0f),	D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		// 3,��,��
		D3DXVECTOR3(-10.5f, -10.5f, 0.0f),D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),	

		//// tri 0
		//XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT3(0.5f, 0.5f, 0.5f),	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT3(0.5f, -0.5f, 0.5f),XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),		
		//// tri 1
		//XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT3(0.5f, -0.5f, 0.5f),XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		//XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		//XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	};
	SimpleVertex verticesLine[] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(1000.f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),

		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f),
	};
	int iNumVertex = sizeof(vertices) / sizeof(vertices[0]);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * iNumVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData,
		&g_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	iNumVertex = sizeof(verticesLine) / sizeof(verticesLine[0]);
	bd.ByteWidth = sizeof(SimpleVertex) * iNumVertex;
	InitData.pSysMem = verticesLine;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData,
		&g_pVBLine);
	if (FAILED(hr))
		return hr;

	DWORD indices[] =
	{
		0,1,2,0,2,3,
	};
	int iNumIndex = sizeof(indices) / sizeof(indices[0]);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DWORD) * iNumIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	InitData.pSysMem = indices;

	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData,
		&g_pIndexBuffer);
	if (FAILED(hr))
		return hr;



	// ������۸� ����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &cb;

	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData,
		&g_pConstantBuffer);
	if (FAILED(hr))
		return false;
	return true;
}
bool Sample::Frame()
{
	// ������۸� �ʱ�ȭ	
	// ������ķ� ���� ����� �����.
	D3DXMatrixIdentity(&cb_game.mWorld);
	//D3DXToRadian(180.0f));//
	//D3DXMatrixRotationY(&cb_game.mWorld,  m_Timer.m_fAccumulation);
	// �� ��� ���
	byte data = DIK_W;
	byte data2 = 'W';
	if (m_Input.KeyCheck(DIK_W) == KEY_HOLD)
	{
		g_Eye.z += 10.0f * m_Timer.GetSPF();
	}
	if (m_Input.KeyCheck(DIK_S) == KEY_HOLD)
	{
		g_Eye.z -= 10.0f * m_Timer.GetSPF();
	}
	if (m_Input.KeyCheck(DIK_A) == KEY_HOLD)
	{
		g_Eye.x += 10.0f * m_Timer.GetSPF();
	}
	if (m_Input.KeyCheck(DIK_D) == KEY_HOLD)
	{
		g_Eye.x -= 10.0f * m_Timer.GetSPF();
	}
	if (m_Input.KeyCheck(DIK_0) == KEY_PUSH)
	{
		BOOL bFullScreen;
		g_pSwapChain->GetFullscreenState(&bFullScreen, NULL);
		g_pSwapChain->SetFullscreenState(!bFullScreen, NULL);
	}
	D3DXVECTOR3 Eye = g_Eye;
	D3DXVECTOR3 At = D3DXVECTOR3(g_Eye.x, g_Eye.y, g_Eye.z+100.0f);
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&cb_game.mView, &Eye, &At, &Up);

	// ��ġ ��� ��ȯ
	D3DXMatrixTranspose(&cb.mWorld, &cb_game.mWorld);
	D3DXMatrixTranspose(&cb.mView, &cb_game.mView);
	D3DXMatrixTranspose(&cb.mProj, &cb_game.mProj);

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,
		0, NULL, &cb, 0, 0);

	return true;
}
bool Sample::Render()
{	
	// Render a triangle
	// Set the input layout
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1,
		&g_pVertexBuffer, &stride, &offset);
	// �ε��� ����
	g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, 
		DXGI_FORMAT_R32_UINT, 0 );
	// ��� ����
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);

	// �������۸� ���� ���
	//g_pImmediateContext->Draw(6, 0);	
	// �ε��� ���۰� ���� ���
	g_pImmediateContext->DrawIndexed(6, 0, 0);

	//if (m_Input.KeyCheck(DIK_V) == KEY_HOLD)
	//{
		g_pImmediateContext->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		g_pImmediateContext->IASetVertexBuffers(0, 1,
			&g_pVBLine, &stride, &offset);
		g_pImmediateContext->Draw(6, 0);
	
		{

			TCHAR pBuffer[256];
			memset(pBuffer, 0, sizeof(TCHAR) * 256);
			_stprintf_s(pBuffer, _T("FPS:%d SecPerFrame:%10.5f Elapsed : %10.2f"), m_Timer.GetFPS(),
				m_Timer.GetSPF(),
				m_Timer.GetElapsedTime());

			m_Font.Begin();
				RECT  rt = { 0, 0, 800, 600 };
				m_Font.m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				m_Font.DrawText(rt, pBuffer, D2D1::ColorF(0, 0, 0, 1.0f));
			m_Font.End();
		}
	//}
	return true;
}
bool Sample::Release()
{
	m_Font.Release();
	if (g_pConstantBuffer) g_pConstantBuffer->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pVBLine) g_pVertexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	return true;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}

KCORE_RUN(KCore Sample, 800, 600)
//TCORE_RUN( _T("Sample Win"), 800, 600)