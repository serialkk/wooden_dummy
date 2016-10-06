#pragma once
#define DIRECTINPUT_VERSION 0x0800

#ifndef UNICODE
#error "TBASIS�� �����ڵ�� ������ �ؾ� �մϴ�."
#endif

#pragma warning( disable:4005)
#include <Windows.h>
#include <tchar.H>
#include <time.h>
#include <crtdbg.h>
#include <cassert>

#include <assert.h>
#include <d3d10_1.h>
#include <d3dx10math.h>
#include <d3dx11.h> 
#include <D3Dcompiler.h>
#include <dxerr.h> //dxerr.lib

// �߰��κ�
#include <d3dx11effect.h>

#include <set>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>
using namespace std;

#pragma warning( disable:4005)
#pragma comment		(lib, "dinput8.lib")
//<stdio.h>, <conio.h>, and other CRT headers. �� 10���� ���� �� 
#pragma comment		(lib, "legacy_stdio_definitions.lib")

//#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dX10.lib" )
#if defined(DEBUG) || defined(_DEBUG)
	//#pragma comment( lib, "d3dx10d.lib" )
	#pragma comment( lib, "d3dx11d.lib" )
	#pragma comment( lib, "dxgi.lib" )
#else
	#pragma comment( lib, "d3dx11.lib" )
	#pragma comment( lib, "d3dx11.lib" )
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "TBasisLib32d_1.lib" )
#else
#pragma comment( lib, "TBasisLib32R_1.lib" )
#endif
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "Effects1132d.lib" )
#else
#pragma comment( lib, "Effects1132r.lib" )
#endif
typedef basic_string<TCHAR>				T_STR;
typedef basic_string<TCHAR>::iterator	T_ITOR;
typedef basic_string<CHAR>				CHAR_STRING;
typedef basic_string<CHAR>::iterator	CHAR_STRING_ITOR;
typedef vector<basic_string<TCHAR>>		T_STR_VECTOR;

#define BASIS_APP_KEY	TEXT("Software\\TBASIS3D11_SAMPLES")
#define TBASIS_EPSILON		((FLOAT)  0.001f)
#define TBASIS_PI			((FLOAT)  3.141592654f)
#define DegreeToRadian( degree ) ((degree) * (TBASIS_PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / TBASIS_PI))
#define MAKECOLOR_ARGB(a, r, g, b)			(((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)
#define IS_IN_RANGE(value,r0,r1) (( ((r0) <= (value)) && ((value) <= (r1)) ) ? 1 : 0)
//////////////////////////////////////////////
// WinMain ��ũ��
//////////////////////////////////////////////
#define TBASIS_START int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ Sample gSample;
#define TBASIS_WIN(x) if( !gSample.InitWindow( hInstance, nCmdShow,  L#x ) )	{	return 0;	}	ShowCursor ( TRUE );gSample.Run();	return 1; }
#define TBASIS_RUN(x) TBASIS_START; TBASIS_WIN(x);
//////////////////////////////////////////////
// DX �żҵ� ȣ�⿡ ���� ��ȯ�� ó�� ��ũ��
//////////////////////////////////////////////
#if defined(_DEBUG) || defined(_DEBUG)
		#ifndef V
#define V(x)       { hr = (x); }
		#endif
		#ifndef V_RETURN
#define V_RETURN(x){ hr = (x); if( FAILED(hr) )  return false;}
		#endif
#else
		#ifndef V
			#define V(x)       { hr = (x); }
		#endif
		#ifndef V_RETURN
			#define V_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
		#endif
#endif

//////////////////////////////////////////////
// ��ü �� �迭 �Ҵ�� ���� �� �Ҹ� ��ũ��
//////////////////////////////////////////////
	#ifndef SAFE_ZERO
		#define SAFE_ZERO(A)				{ A = 0; }
	#endif

	#ifndef SAFE_NEW
		#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
	#endif 

	#ifndef SAFE_DEL
		#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
	#endif 

	#ifndef SAFE_NEW_ARRAY
		#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
	#endif 

	#ifndef SAFE_DELETE_ARRAY
		#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
	#endif 

	#ifndef SAFE_RELEASE
		#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
	#endif 

	#ifndef SAFE_NEW_CLEAR
		#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
	#endif 

	#ifndef SAFE_NEW_ARRAY_CLEAR
		#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
	#endif
// �߰�
#define COUNTOF(a) ( sizeof( a ) / sizeof( ( a )[0] ) )
