#include "Sample.h"
#include "TSys.h"
#include <math.h>

#define RadianToDegree(fAngle)  ( fAngle * (3.14192f / 180.0f))   
#define DegreeToRadian(fAngle)  ( fAngle * ( 180.0f / 3.14192f) )   


bool Sample::Frame()
{
	m_fAngle += g_fSecondPerFrame * 0.0f;
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
HBITMAP Sample::GetRotationBimap( HDC hdc, 
	float fAngle, int iWidth, int iHeight)
{
	HDC BitmapDC = CreateCompatibleDC(g_hScreenDC);
	HBITMAP bitmap = CreateCompatibleBitmap(g_hScreenDC, iWidth,
		iHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(BitmapDC, bitmap);

	COLORREF bkColor = RGB(255, 255, 255);
	HBRUSH back = CreateSolidBrush(bkColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(BitmapDC, back);
	PatBlt(BitmapDC, 0, 0, iWidth, iHeight, PATCOPY);	
	//DeleteObject(SelectObject(BitmapDC, oldBitmap));
	DeleteObject(SelectObject(BitmapDC, oldBrush));

	int iOldMode = SetGraphicsMode(BitmapDC, GM_ADVANCED);
	//  fAnlge( 180도 ) -> 3.141592
	// 육십분법,  호도법
	// Degree -> Radian
	float fRadian = RadianToDegree(fAngle);
	float fCosine = cos(fRadian);
	float fSine = sin(fRadian);

	XFORM xForm;
	xForm.eM11 = fCosine;
	xForm.eM12 = fSine;
	xForm.eM21 = -fSine;
	xForm.eM22 = fCosine;
	xForm.eDx = iWidth / 2;
	xForm.eDy = iHeight / 2;
	SetWorldTransform(BitmapDC, &xForm);

	RECT rt;
	rt.left = 91;
	rt.top = 1;
	rt.right = 41;
	rt.bottom = 60;

	BitBlt(BitmapDC, 
		   0,// -(rt.right / 2),
		    0,//-(rt.bottom / 2),
			rt.right, 
			rt.bottom,
		    hdc, rt.left, rt.top, SRCCOPY);

	SelectObject(BitmapDC, oldBitmap);
	DeleteObject(BitmapDC);

	xForm.eM11 = 1;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = 1;
	xForm.eDx = 0;
	xForm.eDy = 0;
	SetWorldTransform(BitmapDC, &xForm);
	SetGraphicsMode(BitmapDC, iOldMode);

	return bitmap;
}
void Sample::DrawRotate(float fAngle)
{
	RECT rt;
	rt.left = 91;
	rt.top = 1;
	rt.right = 41;
	rt.bottom= 60;
	int iOffWidth = rt.right;
	int iOffHeight = rt.bottom;
	if (iOffWidth > iOffHeight) iOffHeight = iOffWidth;
	else iOffWidth = iOffHeight;

	HBITMAP hMaskBitmap =GetRotationBimap(
		m_MaskBitmap.m_hMemDC, 
		fAngle, 
		iOffWidth, iOffHeight );
	HBITMAP hColorBitmap = GetRotationBimap(
		m_ColorBitmap.m_hMemDC,
		fAngle,
		iOffWidth, iOffHeight);

	HDC hMaskMemDC = CreateCompatibleDC(g_hScreenDC);
	HDC hColorMemDC = CreateCompatibleDC(g_hScreenDC);
	HBITMAP hOldMask = (HBITMAP)SelectObject(hMaskMemDC, hMaskBitmap);
	HBITMAP hOldColor = (HBITMAP)SelectObject(hColorMemDC, hColorBitmap);

	BitBlt(g_hOffScreenDC, 400, 300,
		60,
		60,
		hMaskMemDC,
		0, 0, SRCAND);
	BitBlt(g_hOffScreenDC, 400, 300,
		60,
		60,
		hColorMemDC,
		0, 0, SRCINVERT);

	//BitBlt(g_hOffScreenDC, 400, 300,
	//	60,
	//	60,
	//	hMaskMemDC,
	//	0, 0, SRCINVERT);

	SelectObject(hMaskMemDC, hOldMask);
	SelectObject(hColorMemDC, hOldColor);
	DeleteDC(hMaskMemDC);
	DeleteDC(hColorMemDC);
	DeleteObject(hMaskBitmap);
	DeleteObject(hColorBitmap);
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