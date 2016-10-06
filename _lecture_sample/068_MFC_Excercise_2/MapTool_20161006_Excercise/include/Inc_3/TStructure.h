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
	bool bDebugRender;
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
	PCT_VERTEX() {}
	PCT_VERTEX(	D3DXVECTOR3		vp,					
					D3DXVECTOR4		vc,
					D3DXVECTOR2     vt)
	{
		p = vp, c = vc, t = vt;
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
	PCT2_VERTEX() {}
	PCT2_VERTEX(	D3DXVECTOR3		vp,					
					D3DXVECTOR4		vc,
					D3DXVECTOR2     vt0,
					D3DXVECTOR2		vt1)
	{
		p = vp, c = vc, t0 = vt0, t1 = vt1;
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
	PC_VERTEX() {}
	PC_VERTEX(	D3DXVECTOR3		vp,	D3DXVECTOR4		vc)
	{
		p = vp, c = vc;
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
	PNCT_VERTEX() {}
	PNCT_VERTEX(	D3DXVECTOR3		vp,
					D3DXVECTOR3		vn,
					D3DXVECTOR4		vc,
					D3DXVECTOR2     vt)
	{
		p = vp, n = vn, c = vc, t = vt;
	}
};
struct T_PLANE
{
	float	fA,fB,fC,fD;
	bool	CreatePlane( D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2 );
	bool	CreatePlane( D3DXVECTOR3 vNormal, D3DXVECTOR3 v0 );	
	void	Normalize()
	{
		float fMag =  sqrt( fA*fA + fB*fB + fC*fC);
		fA = fA  / fMag;
		fB = fB / fMag;
		fC = fC / fMag;		
		fD = fD / fMag;		
	}

};
struct T_SPHERE
{
	D3DXVECTOR3		vCenter;
	float			fRadius;
};
struct T_BOX
{	
	// Common
	D3DXVECTOR3		vCenter;
    D3DXVECTOR3		vPos[8];
	// AABB
	D3DXVECTOR3		vMax;
	D3DXVECTOR3		vMin;
	// OBB
	D3DXVECTOR3		vAxis[3];
	float			fExtent[3];
};

}