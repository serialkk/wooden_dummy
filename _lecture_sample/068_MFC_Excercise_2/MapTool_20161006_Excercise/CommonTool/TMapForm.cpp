// TMapForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "TMapForm.h"


// TMapForm

IMPLEMENT_DYNCREATE(TMapForm, CFormView)


//추가함_S
TMapForm* TMapForm::CreateOne(CWnd* pParent) {

	TMapForm* pane = new TMapForm;
	if (pane->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,
		CRect(0,0,2000,2000), pParent,0,NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E



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
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}

BEGIN_MESSAGE_MAP(TMapForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &TMapForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TMapForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &TMapForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &TMapForm::OnBnClickedButton5)
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


	// 비트맵을 가지고 이미지 추가_S
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	m_imageList.Create(48, 48, ILC_COLOR32, 6, 0);
	m_imageSmallList.Create(16, 16, ILC_COLOR32, 6, 0);

	m_imageList.Add(&bitmap, RGB(0,0,0));
	m_imageSmallList.Add(&bitmap, RGB(0, 0, 0));

	m_ctrlList.SetImageList(&m_imageSmallList, LVSIL_NORMAL);
	m_ctrlList.SetImageList(&m_imageSmallList, LVSIL_SMALL);
	// 비트맵을 가지고 이미지 추가_E

	// 아이콘으로 이미지 추가_S
	/*
	m_imageList.Create(48,48,ILC_COLOR32, 5,0);
	m_imageSmallList.Create(16,16,ILC_COLOR32,5,0);

	for (int i = 0; i < 5; i++) {
		m_imageList.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
		m_imageSmallList.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
	}
	m_ctrlList.SetImageList(&m_imageList, LVSIL_NORMAL);
	m_ctrlList.SetImageList(&m_imageSmallList, LVSIL_SMALL);
	*/
	// 아이콘으로 이미지 추가_E



	//리스트 컨트롤에서 탐색기 처럼 보일 수 있게 처리 
	//Report 스타일.스타일 전환..

	m_ctrlList.InsertColumn(0, L"파일명", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, L"크기", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(2, L"설명", LVCFMT_CENTER, 50);

	m_ctrlList.InsertItem(0,L"aaa",0);
	m_ctrlList.InsertItem(0, L"bbb", 1);
	m_ctrlList.InsertItem(0, L"ccc", 2);
	m_ctrlList.InsertItem(0, L"ddd", 3);
	m_ctrlList.InsertItem(0, L"eee", 4);
	m_ctrlList.InsertItem(0, L"fff", 5);


	m_ctrlList.SetItemText(0, 1, L"1000");
	m_ctrlList.SetItemText(0, 2, L"ase파일");
	m_ctrlList.SetItemText(1, 1, L"2000");
	m_ctrlList.SetItemText(1, 2, L"tbs파일");

	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);



	//확장 스타일 추가 작업.
	DWORD dwStyle = m_ctrlList.GetExtendedStyle();
	m_ctrlList.SetExtendedStyle(dwStyle | LVS_EX_CHECKBOXES
		| LVS_EX_BORDERSELECT |LVS_EX_GRIDLINES 
		| LVS_EX_FULLROWSELECT |LVS_EX_AUTOCHECKSELECT
		);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void TMapForm::OnBnClickedButton2()
{
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}


void TMapForm::OnBnClickedButton3()
{
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}


void TMapForm::OnBnClickedButton4()
{
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}


void TMapForm::OnBnClickedButton5()
{
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}
