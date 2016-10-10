// TEffectControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "TEffectControl.h"


// TEffectControl

IMPLEMENT_DYNAMIC(TEffectControl, CDockablePane)

TEffectControl::TEffectControl()
{

}

TEffectControl::~TEffectControl()
{
}


BEGIN_MESSAGE_MAP(TEffectControl, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// TEffectControl 메시지 처리기입니다.




int TEffectControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndForm = TEffectForm::CreateOne(this);
	return 0;
}


void TEffectControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(
			NULL,
			0, 0, cx, cy, SWP_NOZORDER);
	}
}


int TEffectControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	CFrameWnd*  pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


void TEffectControl::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CRect rectClient;
	GetClientRect(rectClient);
	dc.FillRect(rectClient, &afxGlobalData.brWindow);
}
