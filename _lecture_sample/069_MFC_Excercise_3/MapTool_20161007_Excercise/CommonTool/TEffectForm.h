#pragma once



// TEffectForm 폼 뷰입니다.

class TEffectForm : public CFormView
{
	DECLARE_DYNCREATE(TEffectForm)

protected:
	TEffectForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~TEffectForm();

public:
	static TEffectForm*   CreateOne(CWnd* pParent);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEFFECTFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


