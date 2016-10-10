
// CommonToolView.cpp : CCommonToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CommonTool.h"
#endif

#include "CommonToolDoc.h"
#include "CommonToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommonToolView

IMPLEMENT_DYNCREATE(CCommonToolView, CView)

BEGIN_MESSAGE_MAP(CCommonToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCommonToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CCommonToolView 생성/소멸

CCommonToolView::CCommonToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCommonToolView::~CCommonToolView()
{
}

BOOL CCommonToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCommonToolView 그리기

void CCommonToolView::OnDraw(CDC* /*pDC*/)
{
	CCommonToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCommonToolView 인쇄


void CCommonToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCommonToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCommonToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCommonToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCommonToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCommonToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCommonToolView 진단

#ifdef _DEBUG
void CCommonToolView::AssertValid() const
{
	CView::AssertValid();
}

void CCommonToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommonToolDoc* CCommonToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommonToolDoc)));
	return (CCommonToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommonToolView 메시지 처리기


void CCommonToolView::OnDropFiles(HDROP hDropInfo)
{
	CString  filename;
	DWORD  dwSize = 0;
	int nfileCnt = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i = 0; i < nfileCnt;  i++)
	{
		dwSize = DragQueryFile(hDropInfo, i, NULL, 0);
		DragQueryFile(hDropInfo, i, filename.GetBuffer(dwSize + 1),
			dwSize+1);
		filename.ReleaseBuffer();

		CString name = PathFindFileName(filename);
		m_ObjList.push_back(name);
	}
	
	CView::OnDropFiles(hDropInfo);
}
