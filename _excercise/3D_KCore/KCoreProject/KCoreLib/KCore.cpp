#include "KCore.h"

bool KCore::GameInit()
{
	HRESULT hr;
	if (FAILED(CreateGIFactory()))
	{
		return 0;
	}
	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}
	if (FAILED(InitSwapChain()))
	{
		return 0;
	}
	if (FAILED(SetRenderTarget()))
	{
		return 0;
	}
	if (FAILED(SetViewPort()))
	{
		return 0;
	}
	KDxState::SetState(g_pd3dDevice);

	m_Timer.Init();
	I_Input.Init();

	// font 
	IDXGISurface1*  pSurface;
	hr = g_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface1),
		(LPVOID*)&pSurface);
	m_Font.Set(pSurface);
	pSurface->Release();

	Init();
	return true;
}
bool KCore::GameRelease()
{
	KDxState::Release();
	Release();
	m_Timer.Release();
	I_Input.Release();
	m_Font.Release();
	CleanupDevice();
	return true;
}
bool KCore::GameFrame()
{
	m_Timer.Frame();
	
	I_Input.Frame();
	PreFrame();
		Frame();
	PostFrame();
	return true;
}
bool KCore::PreRender()
{
	float ClearColor[4] = { 0.5f, 0.5f,1.0f, 1.0f }; //red,green,blue,alpha
	g_pImmediateContext->ClearRenderTargetView(
		m_DefaultRT.m_pRenderTargetView,
		ClearColor);

	g_pImmediateContext->ClearDepthStencilView(
		m_DefaultRT.m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
		1.0f, 0);

	g_pImmediateContext->OMSetRenderTargets(1,
		&m_DefaultRT.m_pRenderTargetView, m_DefaultRT.m_pDSV);

	ApplyDSS(g_pImmediateContext, KDxState::g_pDepthStencilAddDSS );
	
	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_pImmediateContext->RSSetViewports(1, &m_vp);
	return true;
}
bool KCore::PostRender()
{
	g_pSwapChain->Present(0, 0);
	return true;
}
bool KCore::DrawDebug(TCHAR* pString, int iX, int iY)
{	
	return true;
}
bool KCore::DrawDebug()
{
	if (I_Input.KeyCheck(DIK_V) == KEY_HOLD)
	{	
		m_Font.Begin();
		RECT  rt = { 0, 0, 800, 600 };
		m_Font.m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_Font.DrawText(rt, m_Timer.m_csBuffer, D2D1::ColorF(0, 0, 0, 1.0f));
		m_Font.End();		
	}
	return true;
}
bool KCore::GameRender()
{
	PreRender();
		Render();
		m_Timer.Render();	
		I_Input.Render();
		DrawDebug();
	PostRender();
	return true;
}
bool KCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
};
void KCore::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
};
KCore::KCore()
{
}


KCore::~KCore()
{
}
