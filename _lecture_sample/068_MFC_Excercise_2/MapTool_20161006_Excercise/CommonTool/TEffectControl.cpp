// TEffectControl.cpp : ���� �����Դϴ�.
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
END_MESSAGE_MAP()



// TEffectControl �޽��� ó�����Դϴ�.




int TEffectControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	// �߰���_S
	m_wndForm = TEffectForm::CreateOne(this);
	// �߰���_E
	return 0;
}


void TEffectControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	// �߰���_S
	if (m_wndForm) {

		//�������ø� ����..
		m_wndForm->SetWindowPos(
			NULL,
			0, 0, cx, cy, SWP_NOZORDER);
	}
	// �߰���_E


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int TEffectControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//�߰���_S
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
	//�߰���_E
}
