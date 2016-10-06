// TCreateMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AITool.h"
#include "TCreateMapDlg.h"
#include "afxdialogex.h"


// TCreateMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TCreateMapDlg, CDialogEx)

TCreateMapDlg::TCreateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEMAP, pParent)
	, m_iTileWidth(0)
	, m_iTileHeight(0)
	, m_iCellSize(0)
	, m_iCellCnt(_T(""))
	, m_strBaseTexName(_T(""))
{

}

TCreateMapDlg::~TCreateMapDlg()
{
}

void TCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TILEWIDTHSIZE, m_iTileWidth);
	DDX_Text(pDX, IDC_IDC_TILEHEIGHTSIZE, m_iTileHeight);
	DDX_Text(pDX, IDC_IDC_TILEHEIGHTSIZE2, m_iCellSize);
	DDX_Control(pDX, IDC_COMBO1, m_CBCellCount);
	DDX_CBString(pDX, IDC_COMBO1, m_iCellCnt);
	DDX_Text(pDX, IDC_IDC_TILEHEIGHTSIZE3, m_strBaseTexName);
}


BEGIN_MESSAGE_MAP(TCreateMapDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &TCreateMapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &TCreateMapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// TCreateMapDlg �޽��� ó�����Դϴ�.


void TCreateMapDlg::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}


BOOL TCreateMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_CBCellCount.InsertString(0, L"1");
	m_CBCellCount.InsertString(1, L"2");
	m_CBCellCount.InsertString(2, L"4");
	m_CBCellCount.InsertString(3, L"8");
	m_CBCellCount.InsertString(4, L"16");
	m_CBCellCount.InsertString(5, L"32");
	
	m_iTileWidth = 16;
	m_iTileHeight = 16;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void TCreateMapDlg::OnBnClickedButton1()
{
	// ���� ���� ��ȭ����
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strBaseTexName = dlg.GetFileName();
		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}
		
}
