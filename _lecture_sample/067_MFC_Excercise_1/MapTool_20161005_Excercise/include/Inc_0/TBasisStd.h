#ifndef TBASIS_H
#define TBASIS_H
#include "TUtils.h"
#include "TDxHelper.h"

#pragma comment( lib, "winmm.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "TBasisLib32d_0.lib" )
#else
#pragma comment( lib, "TBasisLib32R_0.lib" )
#endif
namespace TBASIS
{
	extern float		g_fSecPerFrame;
	extern float		g_fDurationTime;
	extern HWND			g_hWnd;
	extern HINSTANCE	g_hInstance;
	extern UINT			g_iClientWidth;
	extern UINT			g_iClientHeight;
}
using namespace TBASIS;
//////////////////////////////////////////////
// WinMain ∏≈≈©∑Œ
//////////////////////////////////////////////
#define TBASIS_START int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ Sample gSample;
#define TBASIS_WIN(x) if( !gSample.InitWindow( hInstance, nCmdShow,  L#x ) )	{	return 0;	}	ShowCursor ( TRUE );gSample.Run();	return 1; }
#define TBASIS_RUN(x) TBASIS_START; TBASIS_WIN(x);

#endif //TBASIS_H