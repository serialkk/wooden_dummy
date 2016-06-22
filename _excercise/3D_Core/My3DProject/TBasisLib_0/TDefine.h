#pragma once
#define DIRECTINPUT_VERSION 0x0800
#ifndef UNICODE
		#error "TBASIS는 유니코드로 컴파일 해야 합니다."
#endif

#include <Windows.h>
#include <tchar.H>
#include <time.h>
#include <crtdbg.h>
#include <cassert>

#include <assert.h>
#include <d3d10_1.h>
#include <d3dx10math.h>
#include <d3dx11.h> 
//#include <dxerr.h> 
#include <D3Dcompiler.h>

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


#define BASIS_APP_KEY	TEXT("Software\\TBASIS11_SAMPLES")


//#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#if defined(DEBUG) || defined(_DEBUG)
	#pragma comment( lib, "d3dx10d.lib" )
	#pragma comment( lib, "d3dx11d.lib" )	
#else
	#pragma comment( lib, "d3dx10.lib" )
	#pragma comment( lib, "d3dx11.lib" )
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "TBasisLib32d_0.lib" )
#else
#pragma comment( lib, "TBasisLib32R_0.lib" )
#endif
#if defined(__d3d11_h__)
	typedef ID3D11Device			ID3DDevice;
	typedef ID3D11Buffer			ID3DBuffer;
	typedef ID3D11Texture3D 		ID3DVolumeTexture;
	typedef ID3D11VertexShader 		ID3DVertexShader;
	typedef ID3D11PixelShader 		ID3DPixelShader;
	typedef ID3D11RenderTargetView	ID3DRTView;		
	typedef D3D11_CULL_MODE			D3D_CULL_MODE;
	typedef D3D11_USAGE				D3D_USAGE;
	typedef D3D11_FILL_MODE			D3D_FILE_MODE;
#endif

typedef basic_string<TCHAR>				TCHAR_STRING;
typedef basic_string<TCHAR>::iterator	TCHAR_STRING_ITOR;

typedef vector<basic_string<TCHAR>>	TCHAR_STRING_VECTOR;
typedef vector<string>				CHAR_STRING_VECTOR;

typedef list<basic_string<TCHAR>>	TCHAR_STRING_LIST;
typedef string						CHAR_STRING;

typedef vector<DWORD>				DWORD_VECTOR;
typedef	vector< DWORD >::iterator	DWORD_VECTOR_ITOR;

typedef list<DWORD>					DWORD_LIST;
typedef list<DWORD>::iterator		DWORD_LIST_ITOR;

typedef list< HANDLE >				HANDLE_LIST;
typedef	list< HANDLE >::iterator	HANDLE_LIST_ITOR;

//////////////////////////////////////////////
// WinMain 매크로
//////////////////////////////////////////////
#define TBASIS_START int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ Sample gSample;
#define TBASIS_WIN(x) if( !gSample.InitWindow( hInstance, nCmdShow,  L#x ) )	{	return 0;	}	ShowCursor ( TRUE );gSample.Run();	return 1; }
#define TBASIS_RUN(x) TBASIS_START; TBASIS_WIN(x);

//////////////////////////////////////////////
// 템플릿 객체 릴리즈 함수
//////////////////////////////////////////////
template<class Interface> inline void SAFE_RELEASE(   Interface **ppInterfaceToRelease    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}
//////////////////////////////////////////////
// Assert
//////////////////////////////////////////////
#ifndef Assert
	#if defined( _DEBUG ) || defined( _DEBUG )
		#define Assert(b) do {if (!(b)) {OutputDebugStringW(L"Assert: " #b L"\n");}} while(0)
	#else
		#define Assert(b)
	#endif //_DEBUG || _DEBUG
#endif


//////////////////////////////////////////////
// DX 매소드 호출에 대한 반환값 처리 매크로
//////////////////////////////////////////////
#ifndef V
		#define V(x)       { hr = (x); }
#endif
#ifndef V_RETURN
		#define V_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
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
	#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif
