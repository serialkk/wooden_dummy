#pragma once
#include "TUtils.h"

#pragma comment		(lib, "dinput8.lib")
//#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )

#if defined(DEBUG) || defined(_DEBUG)
	#pragma comment( lib, "d3dx10d.lib" )
	#pragma comment( lib, "d3dx11d.lib" )
	#pragma comment( lib, "dxgi.lib" )
#else
	#pragma comment( lib, "d3dX10.lib" )
	#pragma comment( lib, "d3dx11.lib" )
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "TBasisLib32d.lib" )
#else
#pragma comment( lib, "TBasisLib32R.lib" )
#endif

