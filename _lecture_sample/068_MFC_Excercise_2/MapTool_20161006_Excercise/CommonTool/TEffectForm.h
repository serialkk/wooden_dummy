#pragma once



// TEffectForm �� ���Դϴ�.

class TEffectForm : public CFormView
{
	DECLARE_DYNCREATE(TEffectForm)

protected:
	TEffectForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~TEffectForm();
	// �߰���_S
public:
	static TEffectForm* CreateOne(CWnd* pParent);
	//�߰���_E
public:
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


