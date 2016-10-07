#pragma once
#include "afxcmn.h"
#include <vector>
#include "resource.h"


// TMapForm �� ���Դϴ�.

class TMapForm : public CFormView
{
	DECLARE_DYNCREATE(TMapForm)

protected:
	TMapForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~TMapForm();

public:
	std::vector<CString>  m_ObjList;
	static TMapForm*   CreateOne(CWnd* pParent);
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
	CTreeCtrl m_treeMapCtl;
	CListCtrl m_listMapCtl;
	CImageList   m_ImageList;
	CImageList   m_ImageSmallList;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


