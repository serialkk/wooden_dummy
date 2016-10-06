// TMapControl.cpp : ���� �����Դϴ�.
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
END_MESSAGE_MAP()



// TMapControl �޽��� ó�����Դϴ�.




//BOOL TMapControl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	return CDockablePane::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


void TMapControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// �߰���_S
	if (m_wndForm) {

		//�������ø� ����..
		m_wndForm->SetWindowPos(
			NULL,
			0,0,cx,cy,SWP_NOZORDER);
	}
	// �߰���_E

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int TMapControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �߰���_S
	m_wndForm = TMapForm::CreateOne(this);
	// �߰���_E


	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


int TMapControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
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
