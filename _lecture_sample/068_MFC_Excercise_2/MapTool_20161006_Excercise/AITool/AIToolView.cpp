
// AIToolView.cpp : CAIToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AITool.h"
#endif

#include "AIToolDoc.h"
#include "AIToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAIToolView

IMPLEMENT_DYNCREATE(CAIToolView, CView)

BEGIN_MESSAGE_MAP(CAIToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAIToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CAIToolView 생성/소멸

CAIToolView::CAIToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAIToolView::~CAIToolView()
{
}

BOOL CAIToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAIToolView 그리기

void CAIToolView::OnDraw(CDC* /*pDC*/)
{
	CAIToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAIToolView 인쇄


void CAIToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAIToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAIToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAIToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CAIToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAIToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAIToolView 진단

#ifdef _DEBUG
void CAIToolView::AssertValid() const
{
	CView::AssertValid();
}

void CAIToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAIToolDoc* CAIToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAIToolDoc)));
	return (CAIToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CAIToolView 메시지 처리기


void CAIToolView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAIToolApp* pApp = (CAIToolApp*)AfxGetApp();
	if (cx != 0 && cy != 0)
	{
		pApp->ResizeDevice(cx, cy);
	}
}
