// TCreateMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "TCreateMapDlg.h"
#include "afxdialogex.h"


// TCreateMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TCreateMapDlg, CDialogEx)

TCreateMapDlg::TCreateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEMAP, pParent)
{

}

TCreateMapDlg::~TCreateMapDlg()
{
}

void TCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TCreateMapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TCreateMapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// TCreateMapDlg �޽��� ó�����Դϴ�.


void TCreateMapDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
