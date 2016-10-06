#pragma once
#include "afxcmn.h"


// TCharView ��ȭ �����Դϴ�.

class TCharView : public CDialogEx
{
	DECLARE_DYNAMIC(TCharView)

public:
	TCharView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TCharView();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
