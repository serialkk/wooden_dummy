#pragma once
#include "afxcmn.h"



// TMapForm �� ���Դϴ�.

class TMapForm : public CFormView
{
	DECLARE_DYNCREATE(TMapForm)

protected:
	TMapForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~TMapForm();

	// �߰���_S
public:
	CImageList m_imageList;
	CImageList m_imageSmallList;


		static TMapForm* CreateOne(CWnd* pParent);
		//�߰���_E

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TMAPFORM };
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
public:
	CTreeCtrl m_ctrlTree;
	CListCtrl m_ctrlList;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};


