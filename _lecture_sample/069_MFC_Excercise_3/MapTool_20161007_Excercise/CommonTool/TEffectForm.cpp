// TEffectForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "TEffectForm.h"


// TEffectForm

IMPLEMENT_DYNCREATE(TEffectForm, CFormView)
TEffectForm*   TEffectForm::CreateOne(CWnd* pParent)
{
	TEffectForm* pane = new TEffectForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 205, 157), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
};
TEffectForm::TEffectForm()
	: CFormView(IDD_TEFFECTFORM)
{

}

TEffectForm::~TEffectForm()
{
}

void TEffectForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(TEffectForm, CFormView)
END_MESSAGE_MAP()


// TEffectForm 진단입니다.

#ifdef _DEBUG
void TEffectForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void TEffectForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// TEffectForm 메시지 처리기입니다.
