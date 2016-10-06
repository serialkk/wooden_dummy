#pragma once
#include "afxcmn.h"


// TCharView 대화 상자입니다.

class TCharView : public CDialogEx
{
	DECLARE_DYNAMIC(TCharView)

public:
	TCharView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TCharView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strChracterName;
	afx_msg void OnBnClickedButton1();
	CTreeCtrl m_treeCharCtl;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_CharListCtl;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL m_bSolidRender;
	BOOL m_iState0;
};
