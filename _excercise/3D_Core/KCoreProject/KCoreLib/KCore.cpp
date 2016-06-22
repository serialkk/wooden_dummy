#include "KCore.h"

bool KCore::GameInit()
{
	if (FAILED(CreateGIFactory()))
	{
		return 0;
	}
	if (FAILED(IniKDevice()))
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

	m_Timer.Init();
	m_Input.Init();

	m_fontDefault = CreateFont( 20, 0, 0, FW_BOLD, 
		0,0,0,0,
		HANGEUL_CHARSET, 3,2,1, 
		VARIABLE_PITCH | FF_ROMAN, 
		_T("°íµñ"));
	m_fontDefaultOld = (HFONT)SelectObject(m_hOffScreenDC, m_fontDefault);
	Init();
	return true;
}
bool KCore::GameRelease()
{
	Release();
	DeleteObject(m_fontDefault);	
	m_Timer.Release();
	m_Input.Release();
	CleanupDevice();
	return true;
}
bool KCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
		Frame();
	PostFrame();
	return true;
}
bool KCore::PreRender()
{
	//float ClearColor[4] = { 1.0f, 1.0f,1.0f, 1.0f }; //red,green,blue,alpha
	float ClearColor[4] = { 0.5f, 0.5f,0.0f, 1.0f }; //red,green,blue,alpha

	g_pImmediateContext->ClearRenderTargetView(
		g_pRenderTargetView,
		ClearColor);
	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

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
	//RECT rect;
	//if (m_hOffScreenDC != NULL)
	//{
	//	GetClientRect(m_hWnd, &rect);
	//	SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
	//	SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
	//	SetBkMode(m_hOffScreenDC, TRANSPARENT);
	//	// ±×¸®±â
	//	DrawText(m_hOffScreenDC, m_Timer.m_csBuffer, -1,
	//		&rect, DT_LEFT | DT_VCENTER);	
	//}
	return true;
}
bool KCore::GameRender()
{
	PreRender();
		Render();
		m_Timer.Render();	
		m_Input.Render();
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
	m_Input.MsgEvent(msg);
};
KCore::KCore()
{
}


KCore::~KCore()
{
}
