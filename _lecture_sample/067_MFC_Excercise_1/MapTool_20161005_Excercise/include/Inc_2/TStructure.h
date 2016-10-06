#pragma once

#include "TDefine.h"
#include "TMatrix.h"

namespace TBASIS_BASE {

struct TBASIS_INPUT_MAP
{
	bool bUpKey;
	bool bDownKey;
	bool bLeftKey;
	bool bRightKey;
	
	bool bWKey;
	bool bSKey;	
	bool bAKey;
	bool bDKey;	
	bool bQKey;
	bool bEKey;	
	
	bool bLeftClick;
	bool bRightClick;
	bool bMiddleClick;

	bool bExit;
	bool bSpace; // 카메라의 이동가속도를 증가시킨다.

	int  iMouseValue[3];

	bool bFullScreen;
	bool bChangeFillMode;
	bool bChangePrimitive;
	bool bChangeCullMode;
	bool bChangeCameraType;
};
extern TBASIS_INPUT_MAP g_InputData;
extern float			g_fSecPerFrame;
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct PCT_VERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	bool operator == (const PCT_VERTEX & Vertex )
	{
		if(		p == Vertex.p  && c == Vertex.c    && t == Vertex.t )					
		{				
			return true;
		}
		return  false;
	}		
};
struct PCT2_VERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR4 c;
	D3DXVECTOR2 t0;
	D3DXVECTOR2 t1;
	bool operator == (const PCT2_VERTEX & Vertex )
	{
		if(		p == Vertex.p  && c == Vertex.c    && t0 == Vertex.t0 && t1 == Vertex.t1)					
		{				
			return true;
		}
		return  false;
	}	
};
struct PC_VERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR4 c;
	bool operator == (const PC_VERTEX & Vertex )
	{
		if(		p == Vertex.p  && c == Vertex.c     )					
		{				
			return true;
		}
		return  false;
	}
};
struct PNC_VERTEX
{
    D3DXVECTOR3 p;
	D3DXVECTOR3 n;
    D3DXVECTOR4 c;
	bool operator == (const PNC_VERTEX & Vertex )
	{
		if(		p == Vertex.p  && n == Vertex.n && 	c == Vertex.c     )					
		{				
			return true;
		}
		return  false;
	}
};
struct PNCT_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR4		c;
    D3DXVECTOR2     t;
	bool operator == (const PNCT_VERTEX & Vertex )
	{
		if(		p == Vertex.p  && n == Vertex.n && 	c == Vertex.c  &&	t == Vertex.t   )					
		{				
			return true;
		}
		return  false;
	}	
};
}