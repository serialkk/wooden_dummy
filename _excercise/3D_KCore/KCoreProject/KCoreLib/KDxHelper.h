#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
//#include <xnamath.h>
#include <d3dx10math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>	
using namespace std;

#pragma comment	(lib, "dxgi.lib")
#pragma comment	(lib, "dxguid.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dcompiler.lib")

#if defined(DEBUG) || defined(_DEBUG)
	#pragma comment( lib, "d3dx10d.lib")
	#pragma comment( lib, "d3dx11d.lib")
#else
	#pragma comment( lib, "d3dx10.lib")
	#pragma comment( lib, "d3dx11.lib")
#endif

#pragma comment( lib, "dwrite.lib")
#pragma comment	(lib, "d2d1.lib")

extern ID3D11Device*	g_pd3dDevice;
// # 스트링화 연산자
// ## 연결연산자
#define str(x)  L#x  // L"aa", _T("aa"), "aa"
#define xstr(x)  str(x)

#if defined(DEBUG) | defined(_DEBUG) 
#ifndef H_RETURN
#define H_RETURN(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK); return x;}\
	}
#endif
#ifndef H
#define H(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK);}\
	}
#endif
#else
#ifndef H_RETURN
#define H_RETURN(x) { hr=(x); if( FAILED(hr) { return hr; }}
#endif
#ifndef H
#define H(x) { hr = (x); }
#endif
#endif

//////////////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
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
#define SAFE_NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif
// 추가
#define COUNTOF(a) ( sizeof( a ) / sizeof( ( a )[0] ) )
