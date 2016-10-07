// TMapForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "TMapForm.h"


// TMapForm

IMPLEMENT_DYNCREATE(TMapForm, CFormView)

TMapForm*   TMapForm::CreateOne(CWnd* pParent)
{
	RECT rect;
	pParent->GetClientRect(&rect);

	TMapForm* pane = new TMapForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0,0, 300, 300), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
};

TMapForm::TMapForm()
	: CFormView(IDD_TMAPFORM)
{

}

TMapForm::~TMapForm()
{
}

void TMapForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeMapCtl);
	DDX_Control(pDX, IDC_LIST1, m_listMapCtl);
}

BEGIN_MESSAGE_MAP(TMapForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &TMapForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TMapForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &TMapForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &TMapForm::OnBnClickedButton5)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &TMapForm::OnLvnItemchangedList1)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// TMapForm 진단입니다.

#ifdef _DEBUG
void TMapForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void TMapForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// TMapForm 메시지 처리기입니다.


void TMapForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	/*m_ImageList.Create(48, 48, ILC_COLOR32, 4, 0);
	m_ImageSmallList.Create(16,16, ILC_COLOR32, 4, 0);
	for (int i = 0; i < 4; i++ )
	{
		m_ImageList.Add(AfxGetApp()->LoadIconW(IDI_ICON1+i));
		m_ImageSmallList.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
	}*/

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP3);

	//m_ImageList.Create(48, 48, ILC_COLOR32, 6, 0);
	m_ImageSmallList.Create(16, 16, ILC_COLOR32, 6, 0);
	//m_ImageList.Add(&bitmap, RGB(0,0,0));
	m_ImageSmallList.Add(&bitmap, RGB(0, 0, 0));	

	m_listMapCtl.SetImageList(&m_ImageSmallList, LVSIL_NORMAL);
	m_listMapCtl.SetImageList(&m_ImageSmallList, LVSIL_SMALL);

	m_listMapCtl.InsertColumn(0, L"파일명", LVCFMT_CENTER, 50);
	m_listMapCtl.InsertColumn(1, L"크기", LVCFMT_CENTER, 50);
	m_listMapCtl.InsertColumn(2, L"설명", LVCFMT_CENTER, 50);
	m_listMapCtl.InsertItem(0, L"aaa", 0);
	m_listMapCtl.InsertItem(1, L"bbb", 1);
	m_listMapCtl.InsertItem(2, L"CCC", 2);
	m_listMapCtl.InsertItem(3, L"CCC", 3);
	m_listMapCtl.InsertItem(4, L"CCC", 4);
	m_listMapCtl.InsertItem(5, L"CCC", 5);
	m_listMapCtl.SetItemText(0, 1,  L"1000");
	m_listMapCtl.SetItemText(0, 2, L"ass파일");
	m_listMapCtl.SetItemText(1, 1, L"2000");
	m_listMapCtl.SetItemText(1, 2, L"tbs파일");

	m_listMapCtl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	DWORD dwStyle = m_listMapCtl.GetExtendedStyle();
	m_listMapCtl.SetExtendedStyle(dwStyle | LVS_EX_CHECKBOXES
		| LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT  | 
		LVS_EX_FULLROWSELECT | LVS_EX_AUTOCHECKSELECT );

	DragAcceptFiles();

	//GetParentFrame()->RecalcLayout();
	//SetScrollSizes(MM_TEXT, CSize(205, 157));
	//ResizeParentToFit(TRUE);
}


void TMapForm::OnBnClickedButton2()
{
	m_listMapCtl.ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}


void TMapForm::OnBnClickedButton3()
{
	m_listMapCtl.ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}


void TMapForm::OnBnClickedButton4()
{
	m_listMapCtl.ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}


void TMapForm::OnBnClickedButton5()
{
	m_listMapCtl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}


void TMapForm::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void TMapForm::OnDropFiles(HDROP hDropInfo)
{
	CString  filename;
	DWORD  dwSize = 0;
	int nfileCnt = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i = 0; i < nfileCnt; i++)
	{
		dwSize = DragQueryFile(hDropInfo, i, NULL, 0);
		DragQueryFile(hDropInfo, i, filename.GetBuffer(dwSize + 1),
			dwSize + 1);
		filename.ReleaseBuffer();

		CString name = PathFindFileName(filename);
		m_ObjList.push_back(name);
	}
	CFormView::OnDropFiles(hDropInfo);
}
