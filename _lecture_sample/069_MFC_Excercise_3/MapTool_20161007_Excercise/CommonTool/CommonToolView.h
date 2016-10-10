
// CommonToolView.h : CCommonToolView Ŭ������ �������̽�
//

#pragma once
#include <vector>

class CCommonToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCommonToolView();
	DECLARE_DYNCREATE(CCommonToolView)

// Ư���Դϴ�.
public:
	CCommonToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	std::vector<CString>  m_ObjList;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CCommonToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

#ifndef _DEBUG  // CommonToolView.cpp�� ����� ����
inline CCommonToolDoc* CCommonToolView::GetDocument() const
   { return reinterpret_cast<CCommonToolDoc*>(m_pDocument); }
#endif

