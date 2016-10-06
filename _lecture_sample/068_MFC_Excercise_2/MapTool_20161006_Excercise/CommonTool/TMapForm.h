#pragma once
#include "afxcmn.h"



// TMapForm 폼 뷰입니다.

class TMapForm : public CFormView
{
	DECLARE_DYNCREATE(TMapForm)

protected:
	TMapForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~TMapForm();

	// 추가함_S
public:
	CImageList m_imageList;
	CImageList m_imageSmallList;


		static TMapForm* CreateOne(CWnd* pParent);
		//추가함_E

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


