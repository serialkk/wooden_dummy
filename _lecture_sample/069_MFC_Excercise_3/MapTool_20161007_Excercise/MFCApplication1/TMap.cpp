// TMap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "TMap.h"


// TMap

IMPLEMENT_DYNAMIC(TMap, CDockablePane)

TMap::TMap()
{

}

TMap::~TMap()
{
}


BEGIN_MESSAGE_MAP(TMap, CDockablePane)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// TMap �޽��� ó�����Դϴ�.




void TMap::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	CRect rectClient;
	GetClientRect(rectClient);

	dc.FillRect(rectClient, &afxGlobalData.brWindow);
}


int TMap::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
