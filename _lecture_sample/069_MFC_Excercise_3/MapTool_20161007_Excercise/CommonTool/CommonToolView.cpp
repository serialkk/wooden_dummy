
// CommonToolView.cpp : CCommonToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCommonToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

// CCommonToolView ����/�Ҹ�

CCommonToolView::CCommonToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCommonToolView::~CCommonToolView()
{
}

BOOL CCommonToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCommonToolView �׸���

void CCommonToolView::OnDraw(CDC* /*pDC*/)
{
	CCommonToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CCommonToolView �μ�


void CCommonToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCommonToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCommonToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCommonToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CCommonToolView ����

#ifdef _DEBUG
void CCommonToolView::AssertValid() const
{
	CView::AssertValid();
}

void CCommonToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommonToolDoc* CCommonToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommonToolDoc)));
	return (CCommonToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommonToolView �޽��� ó����


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
