// TMapControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "TMapControl.h"


// TMapControl

IMPLEMENT_DYNAMIC(TMapControl, CDockablePane)

TMapControl::TMapControl()
{

}

TMapControl::~TMapControl()
{
}


BEGIN_MESSAGE_MAP(TMapControl, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// TMapControl 메시지 처리기입니다.




void TMapControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(
			NULL, 
			0, 0, cx, cy, SWP_NOZORDER );
	}
}


int TMapControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	RECT rect;
	GetClientRect(&rect);
	//m_wndForm = (TMapForm*)(RUNTIME_CLASS(TMapForm)->CreateObject());
	//m_wndForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 0, NULL);

	m_wndForm = TMapForm::CreateOne(this);

	return 0;
}


int TMapControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd*  pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


void TMapControl::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CRect rectClient;
	GetClientRect(rectClient);
	dc.FillRect(rectClient, &afxGlobalData.brWindow);

}
