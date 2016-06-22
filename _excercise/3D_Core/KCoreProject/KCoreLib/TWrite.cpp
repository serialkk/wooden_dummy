#include "TWrite.h"
bool   TWrite::Set(IDXGISurface1*  pSurface)
{
	HRESULT hr = S_OK;
	hr = CreateDeviceIndendentResource();
	hr = CreateDeviceResources(pSurface);
	return true;
}
void   TWrite::Begin()
{
	m_pRT->BeginDraw();
}
void   TWrite::End()
{
	m_pRT->EndDraw();
}

bool   TWrite::Init()
{
	
	return true;
}
HRESULT TWrite::CreateDeviceIndendentResource()
{
	HRESULT hr = S_OK;
	// d2d
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
						&m_pD2DFactory);
	// dwrite
	hr = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED,
						__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_WriteFactory));

	hr = m_WriteFactory->CreateTextFormat(
		L"¸¼Àº°íµñ",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_ITALIC,
		DWRITE_FONT_STRETCH_NORMAL, 
		30,
		L"ko-kr",  //L"en-us"
		&m_TextFormat);	
	return hr;
};
HRESULT TWrite::DrawText(RECT rt,
	TCHAR* pText,
	D2D1::ColorF Color)
{
	HRESULT hr = S_OK;
	D2D1_RECT_F layoutRect = D2D1::RectF(
		static_cast<FLOAT>(rt.left),
		static_cast<FLOAT>(rt.top),
		static_cast<FLOAT>(rt.right),
		static_cast<FLOAT>(rt.bottom));
	m_pRedBrush->SetColor(Color);
	m_pRT->DrawText(pText,	wcslen(pText),	m_TextFormat,
		layoutRect,	m_pRedBrush);

	return hr;
}
HRESULT TWrite::CreateDeviceResources(IDXGISurface1* pSurface)
{
	HRESULT hr = S_OK;
	FLOAT m_fdpiX, m_fdpiY;
	m_pD2DFactory->GetDesktopDpi(&m_fdpiX, &m_fdpiY);

	// d3d rt -> d2d rt
	D2D1_RENDER_TARGET_PROPERTIES props = 
		D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, 
			D2D1_ALPHA_MODE_PREMULTIPLIED),
		static_cast<float>(m_fdpiX),
		static_cast<float>(m_fdpiY));
	
	hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
		pSurface,
		(const D2D1_RENDER_TARGET_PROPERTIES *)&props,
		&m_pRT);


	m_pRT->CreateSolidColorBrush( D2D1::ColorF(D2D1::ColorF::Red), 
								  &m_pRedBrush);
	return hr;
};
bool   TWrite::Release()
{
	SAFE_RELEASE(m_WriteFactory);
	SAFE_RELEASE(m_TextFormat);
	SAFE_RELEASE(m_pRedBrush);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pRT);
	return true;
}

TWrite::TWrite()
{
}


TWrite::~TWrite()
{
}
