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
	, m_iCellCnt(_T(""))
	, m_strTextureName(_T(""))
{

}

TCreateMapDlg::~TCreateMapDlg()
{
}

void TCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TILEWIDTHSIZE, m_iTileWidth);
	DDX_Text(pDX, IDC_TILEHEIGHTSIZE, m_iTileHeight);
	DDX_Control(pDX, IDC_COMBO1, m_CBCellCount);
	DDX_CBString(pDX, IDC_COMBO1, m_iCellCnt);
	DDX_Text(pDX, IDC_TILEHEIGHTSIZE3, m_strTextureName);
}


BEGIN_MESSAGE_MAP(TCreateMapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TCreateMapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &TCreateMapDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &TCreateMapDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &TCreateMapDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// TCreateMapDlg �޽��� ó�����Դϴ�.


void TCreateMapDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void TCreateMapDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	m_iTileHeight = 16;
	m_iTileWidth = 16;

	UpdateData(FALSE);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void TCreateMapDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void TCreateMapDlg::OnBnClickedButton2()
{
	// ���� ���� ��ȭ ����
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		m_strTextureName = dlg.GetFileName();
		UpdateData(FALSE);
	}
	//MessageBox(dlg.GetPathName());

}
