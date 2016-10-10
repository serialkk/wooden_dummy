// TCreateMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AITool.h"
#include "TCreateMapDlg.h"
#include "afxdialogex.h"


// TCreateMapDlg 대화 상자입니다.

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


// TCreateMapDlg 메시지 처리기입니다.


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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TCreateMapDlg::OnBnClickedButton1()
{
	// 파일 선택 대화상자
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strBaseTexName = dlg.GetFileName();
		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}
		
}
