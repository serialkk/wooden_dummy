#pragma once



// TEffectForm �� ���Դϴ�.

class TEffectForm : public CFormView
{
	DECLARE_DYNCREATE(TEffectForm)

protected:
	TEffectForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


