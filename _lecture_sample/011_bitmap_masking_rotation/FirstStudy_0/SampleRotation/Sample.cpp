#include "Sample.h"
#include "TSys.h"
#include <math.h>

bool Sample::Frame()
{
	m_fAngle += g_fSecondPerFrame * 10.0f;
	return true;
}
bool Sample::Init()
{	
	if (!m_BackGround.Load(_T("../../data/Koala.bmp")))
	{
		return false;
	}
	if (!m_ColorBitmap.Load(_T("../../data/bitmap1.bmp")))
	{
		return false;
	}
	if (!m_MaskBitmap.Load(_T("../../data/bitmap2.bmp")))
	{
		return false;
	}
	return true;
}
///* Ternary raster operations */
//#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
//#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
//#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
//#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
//#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
//#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
//#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
//#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
//#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
//#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
//#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
//#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
//#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
//#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
//#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE */

void Sample::DrawBackGround()
{
	BitBlt(g_hOffScreenDC, 0, 0,
		m_BackGround.m_hBitInfo.bmWidth,
		m_BackGround.m_hBitInfo.bmHeight,
		m_BackGround.m_hMemDC,
		0, 0, SRCCOPY);

}

#define RadianToDegree(fAngle)  ( fAngle * (3.14192f / 180.0f))   
#define DegreeToRadian(fAngle)  ( fAngle * ( 180.0f / 3.14192f) )   
void Sample::DrawRotate(float fAngle)
{
	HDC hdc;
	// 회전되는 영역을 계산
	// 계산된 영역의 크기에 맞게 비트맵을 생성한다.
	hdc = CreateCompatibleDC(m_hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(m_hScreenDC, 100, 100);
	SelectObject(hdc, hBitmap);

	HBRUSH back = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, back);
	PatBlt(hdc, 0, 0, 100, 100, PATCOPY);

	// 메모리 DC에 비트맵을 적용

	
	int iOldMode = SetGraphicsMode(hdc, GM_ADVANCED);
	//  fAnlge( 180도 ) -> 3.141592
	// 육십분법,  호도법
	// Degree -> Radian
	float fRadian = RadianToDegree(fAngle);
	float fCosine = cos(fRadian);
	float fSine = sin(fRadian);
	XFORM xForm;
	xForm.eM11 = fCosine;
	xForm.eM12 = -fSine;
	xForm.eM21 = fSine;
	xForm.eM22 = fCosine;
	xForm.eDx = 0;
	xForm.eDy = 0;
	SetWorldTransform(hdc, &xForm);

	BitBlt(hdc, 0, 0, 100, 100, 
		   원본 DC, 0, 0, SRCCOPY);
	// Radian -> Degree
	float fDegree = DegreeToRadian(fRadian);
	
	SetGraphicsMode(hdc, iOldMode);
}
void Sample::DrawObject()
{
	BitBlt(g_hOffScreenDC, 400, 300,
		41,
		60,
		m_MaskBitmap.m_hMemDC,
		91, 1, SRCAND);
	BitBlt(g_hOffScreenDC, 400, 300,
		41,
		60,
		m_ColorBitmap.m_hMemDC,
		91, 1, SRCINVERT);

	BitBlt(g_hOffScreenDC, 400, 300,
		41,
		60,
		m_MaskBitmap.m_hMemDC,
		91, 1, SRCINVERT);
}
bool Sample::Render()
{
	DrawBackGround();
	//DrawObject();
	DrawRotate(m_fAngle);
	return true;
}
bool Sample::Release()
{
	m_ColorBitmap.Release();
	m_MaskBitmap.Release();
	return true;
}
Sample::Sample()
{
	m_fAngle = 0.0f;
}


Sample::~Sample()
{
}


int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}