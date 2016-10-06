#pragma once
#include "afxwin.h"


// TCreateMapDlg ��ȭ �����Դϴ�.

class TCreateMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TCreateMapDlg)

public:
	TCreateMapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TCreateMapDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	int m_iTileWidth;
	int m_iTileHeight;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_CBCellCount;
	CString m_iCellCnt;
	CString m_strTextureName;
	afx_msg void OnBnClickedButton2();
};
