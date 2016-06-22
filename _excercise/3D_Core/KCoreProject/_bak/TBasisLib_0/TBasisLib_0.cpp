#include "TBasisLib_0.h"


int TBasisLib_0::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	return -1;
}
bool TBasisLib_0::PreInit()
{
	if( FAILED( InitDevice(m_hWnd,this->m_iWindowWidth, this->m_iWindowHeight) ) )
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return false;
	}
	if( !m_Timer.Init() )	return false;	
	// DirectX Input 생성 
	if( !I_Input.InitDirectInput( m_hInstance , m_hWnd, true, true ) )
	{
		return false;
	}
	// DirectX Input 초기화
	if( !I_Input.Init() )
	{
		return false;
	}
	return true;
}
bool TBasisLib_0::Init()
{
	return true;
}
bool TBasisLib_0::PostInit()
{
	return true;
}
bool TBasisLib_0::TInit()
{
	if( !PreInit() ) return false;
	if( !Init() ) return false;
	if( !PostInit() ) return false;
	return true;
}

bool TBasisLib_0::PreFrame()
{
	if( !m_Timer.Frame() ) return false;
	if( !I_Input.Frame() ) return false;	
	return true;
}
bool TBasisLib_0::PostFrame()
{
	return true;
}
bool TBasisLib_0::Frame()
{
	return true;
}
bool TBasisLib_0::Release()
{
	return true;
}
bool TBasisLib_0::TRelease()
{
	CleanupDevice();
	if( !m_Timer.Release() ) return false;		
	//if( !m_Font.Release() ) return false;	
	if( !m_Font.Release() ) return false;	
	if( !I_Input.Release() ) return false;	
	return Release();
}
bool TBasisLib_0::TFrame()
{
	PreFrame();
	Frame();
	PostFrame();
	return true;
}
bool TBasisLib_0::TRender()
{
	PreRender();
	Render();
	DrawDebug();
	PostRender();
	I_Input.PostProcess();
	return true;
}

bool TBasisLib_0::Render()
{
	return true;
}
bool TBasisLib_0::PreRender()
{
	// Just clear the backbuffer
    float ClearColor[4] = { 0.125f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( GetRenderTargetView(), ClearColor );
	return true;
}
bool TBasisLib_0::DrawDebug()
{
	// FPS 출력
	TCHAR pBuffer[256];
	memset( pBuffer, 0, sizeof( TCHAR ) * 256 );
	_stprintf_s( pBuffer, _T("FPS:%d"), m_Timer.GetFPS() );	
	
	m_Font.Begin();
	m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};
	m_Font.DrawText( rc1, pBuffer,  D2D1::ColorF(1.0f, 1.0f, 1.0f,0.5));		
	m_Font.End();
	return true;
}

bool TBasisLib_0::DrawDebugRect(RECT* rcDest, TCHAR* pString, D3DXCOLOR color )
{
	if( rcDest == NULL ) return false;	

	if( m_Font.m_pTextFormat)
	{
		D2D1_SIZE_F rtSize = m_Font.m_pRT->GetSize ();
        //Draw a grid background.
        int width = static_cast <int> (rtSize.width);
        int height = static_cast <int> (rtSize.height);


		m_Font.Begin();
		m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		//RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};
		m_Font.DrawText( *rcDest, pString,  D2D1::ColorF(color.r,color.g,color.b,0.5f));		
		m_Font.End();
	}

	return true;
}
bool TBasisLib_0::PostRender()
{	
	GetSwapChain()->Present( 0, 0 );
	return true;
}
bool TBasisLib_0::ToolRun()
{
	if( !TInit() ) return false;
	
	//TFrame();
    //TRender();        
	
	return true;
}
bool TBasisLib_0::Run()
{
	if( !TInit() ) return false;
	// Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			TFrame();
            TRender();
        }
    }
	if( !TRelease() ) return false;
	return true;
}
HRESULT TBasisLib_0::CreateDxResource()
{
	IDXGISurface1*		pBackBuffer=NULL;
	HRESULT hr = GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);	
	m_Font.Set(m_hWnd, m_iWindowWidth,
				m_iWindowHeight, pBackBuffer );		
	if( pBackBuffer )	pBackBuffer->Release();

	CreateResource();
	return S_OK;
}
HRESULT TBasisLib_0::DeleteDxResource()
{
	if( !m_Font.Release() ) return false;	
	DeleteResource();
	return S_OK;
}
HRESULT TBasisLib_0::CreateResource()
{
	return S_OK;
}
HRESULT TBasisLib_0::DeleteResource()
{
	return S_OK;
}
TBasisLib_0::TBasisLib_0(void)
{	
}

TBasisLib_0::~TBasisLib_0(void)
{
}
