// TMap.cpp : 구현 파일입니다.
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



// TMap 메시지 처리기입니다.




void TMap::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
