// TCharView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AITool.h"
#include "TCharView.h"
#include "afxdialogex.h"


// TCharView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TCharView, CDialogEx)

TCharView::TCharView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHARACTERVIEW, pParent)
	, m_strChracterName(_T(""))
	, m_bSolidRender(FALSE)
	, m_iState0(FALSE)
{

}

TCharView::~TCharView()
{
}

void TCharView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARACTERNAME, m_strChracterName);
	DDX_Control(pDX, IDC_TREE1, m_treeCharCtl);
	DDX_Control(pDX, IDC_LIST1, m_CharListCtl);
	DDX_Check(pDX, IDC_CHECK2, m_bSolidRender);
	DDX_Radio(pDX, IDC_RADIO4, m_iState0);
}


BEGIN_MESSAGE_MAP(TCharView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TCharView::OnBnClickedButton1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &TCharView::OnTvnSelchangedTree1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &TCharView::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// TCharView �޽��� ó�����Դϴ�.


void TCharView::OnBnClickedButton1()
{
	// ���� ���� ��ȭ ����
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		m_strChracterName = dlg.GetFileName();
		UpdateData(FALSE);
	}

	HTREEITEM hItem;
	hItem = m_treeCharCtl.InsertItem(L"bip01",0,0,TVI_ROOT);
			m_treeCharCtl.InsertItem(L"bip02", 0, 0, hItem);
			hItem = m_treeCharCtl.InsertItem(L"bip03", 0, 0, hItem);
			m_treeCharCtl.InsertItem(L"bip04", 0, 0, hItem);
			m_treeCharCtl.InsertItem(L"bip05", 0, 0, hItem);

			m_treeCharCtl.EnsureVisible(hItem);

	hItem = m_treeCharCtl.InsertItem(L"bip_01", 0, 0, TVI_ROOT);
			m_treeCharCtl.InsertItem(L"bip_02", 0, 0, hItem);
			hItem = m_treeCharCtl.InsertItem(L"bip_03", 0, 0, hItem);
			m_treeCharCtl.InsertItem(L"bip_04", 0, 0, hItem);
			m_treeCharCtl.InsertItem(L"bip_05", 0, 0, hItem);

			m_treeCharCtl.EnsureVisible(hItem);

			m_CharListCtl.InsertItem(0, L"aaaaa",0);
			m_CharListCtl.InsertItem(1, L"bbbbb", 0);
			m_CharListCtl.InsertItem(2, L"ccccc", 0);
			m_CharListCtl.InsertItem(3, L"ddddd", 0);
			m_CharListCtl.InsertItem(4, L"eeeee", 0);

}


void TCharView::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString item = m_treeCharCtl.GetItemText(pNMTreeView->itemNew.hItem);

	
	//������Ʈ ���1
	/*
	m_strChracterName = item;
	UpdateData(FALSE);
	*/

	//������Ʈ ���2
	GetDlgItem(IDC_CHARACTERNAME)->SetWindowText(item);


	*pResult = 0;
}


void TCharView::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
