#pragma once
#include "TTemplate.h"
#include "TDxHelperEx.h"
// Sub texture types
#define ID_TBASIS_AM 0   // ambient
#define ID_TBASIS_DI 1   // diffuse
#define ID_TBASIS_SP 2   // specular
#define ID_TBASIS_SH 3   // shininesNs
#define ID_TBASIS_SS 4   // shininess strength
#define ID_TBASIS_SI 5   // self-illumination
#define ID_TBASIS_OP 6   // opacity
#define ID_TBASIS_FI 7   // filter color
#define ID_TBASIS_BU 8   // bump 
#define ID_TBASIS_RL 9   // reflection
#define ID_TBASIS_RR 10  // refraction 
#define ID_TBASIS_DP 11  // displacement
#define ID_TBASIS_GN 12  // Generic
#define ID_TBASIS_EV 13  // EnvMap

using namespace TBASIS;

const enum OBJECTCLASSTYPE {
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};

const enum FILETYPE {
	NULLFILE = 0,
	ASEFILE,
	TBSFILE,
	SKMFILE,
	MATFILE,
};


struct TScene
{
	int iVersion;		// 버전
	int	iFirstFrame;    // 시작 프레임
	int	iLastFrame;     // 마지막 프레임
	int	iFrameSpeed;    // 1초당 프레임 개수(30)
	int	iTickPerFrame;  // 1프레임의 틱 값(160)
	int iNumMesh;		// 메쉬오브젝트 개수
	int iMaxWeight;		// 정점 당 가중치
	int iBindPose;		// 바인딩 포즈 에니메이션 여부
};
struct VersionMark
{
	int		iVersion;
	TCHAR	description[128];
};

struct TTextexMap
{
	// 오브젝트 텍스쳐 관리자에서 매터리얼의 텍스쳐파일명을 보고 DX텍스쳐 생성 후 참조인덱스를 저장한다.
	DWORD		m_dwIndex;
	// 텍스쳐 맵 타입인덱스
	DWORD		m_dwType;
	// 맵 이름
	T_STR		m_strName;
	// 맵 클래스 이름
	T_STR		m_strClassName;
	// 맵 텍스쳐 이름.
	T_STR		m_strTextureName;
	TTextexMap() : m_dwType(1), m_dwIndex(0) {}
};
struct TMtrl
{
	// 메터리얼 이름
	T_STR		m_strName;
	// 메터리얼 클래스 이름
	T_STR		m_strClassName;
	// 맵타입들
	vector<TTextexMap>	m_TexMaps;
	// 서브 매터리얼 저장벡터
	vector<TMtrl>		m_SubMaterial;
	//TBS
	DWORD m_dwSubCount;
	DWORD m_dwTexMapCount;
	DWORD m_dwIndex;

	TMtrl() {}
	~TMtrl()
	{
		stl_wipe_vector(m_SubMaterial);
		stl_wipe_vector(m_TexMaps);
	}
};


struct TFaceList
{
	union
	{
		struct { DWORD	_0, _1, _2; };
		DWORD v[3];
	};
	DWORD   dwMtrl;
	TFaceList() : dwMtrl(0), _0(0), _1(0), _2(0)
	{}
};

struct TVertexList
{
	DWORD					dwNumVertex;
	DWORD					dwNumFace;
	vector<D3DXVECTOR3>		pVertexList;
	vector<TFaceList>		pFaceList;
	vector<DWORD>			pSubListMtl;
	TVertexList() : dwNumVertex(0), dwNumFace(0)
	{
	}
	~TVertexList() { stl_wipe_vector(pVertexList); stl_wipe_vector(pVertexList); }
};

struct TAnimTrack
{
	int					iTick;
	D3DXQUATERNION		qRotate;
	D3DXVECTOR3			vVector;
	TAnimTrack*			pNext;
	TAnimTrack*			pPrev;
};

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct T_PLANE
{
	float	fA, fB, fC, fD;
	bool	CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	bool	CreatePlane(D3DXVECTOR3 vNormal, D3DXVECTOR3 v0);
	void	Normalize()
	{
		float fMag = sqrt(fA*fA + fB*fB + fC*fC);
		fA = fA / fMag;
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
	float			fRadius[3];
	// OBB
	D3DXVECTOR3		vAxis[3];
	float			fExtent[3];	
};
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	bool operator == (const PCT_VERTEX & Vertex)
	{
		if (p == Vertex.p  && c == Vertex.c    && t == Vertex.t)
		{
			return true;
		}
		return  false;
	}
	PCT_VERTEX() {}
	PCT_VERTEX(D3DXVECTOR3		vp,
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
	bool operator == (const PCT2_VERTEX & Vertex)
	{
		if (p == Vertex.p  && c == Vertex.c    && t0 == Vertex.t0 && t1 == Vertex.t1)
		{
			return true;
		}
		return  false;
	}
	PCT2_VERTEX() {}
	PCT2_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt0,
		D3DXVECTOR2     vt1)
	{
		p = vp, c = vc, t0 = vt0, t1 = vt1;
	}
};
struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	bool operator == (const PC_VERTEX & Vertex)
	{
		if (p == Vertex.p  && c == Vertex.c)
		{
			return true;
		}
		return  false;
	}
	PC_VERTEX() {}
	PC_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR4		vc)
	{
		p = vp, c = vc;
	}
};
struct PNC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	bool operator == (const PNC_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c)
		{
			return true;
		}
		return  false;
	}
	PNC_VERTEX() {}
	PNC_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc)
	{
		p = vp, n = vn, c = vc;
	}
};
struct PNCT_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR4		c;
	D3DXVECTOR2     t;
	bool operator == (const PNCT_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c  &&	t == Vertex.t)
		{
			return true;
		}
		return  false;
	}
	PNCT_VERTEX() {}
	PNCT_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt)
	{
		p = vp, n = vn, c = vc, t = vt;
	}
};
struct PNCT2_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR4		c;
	D3DXVECTOR2     t;
	D3DXVECTOR3		vTangent;
	bool operator == (const PNCT2_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c   &&	vTangent == Vertex.vTangent)
		{
			return true;
		}
		return  false;
	}
	PNCT2_VERTEX() {}
	PNCT2_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt,
		D3DXVECTOR3		tangent )
	{
		p = vp, n = vn, c = vc, t = vt, vTangent = tangent;
	}
};
// ─────────────────────────────────
//  쉐이더 사용시( 가중치 4개 제한 사용 )
// ─────────────────────────────────
struct PNCT3_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR4		c;
	D3DXVECTOR2		t;
	D3DXVECTOR4		w;// W0, fW1, fW2, fNumWeight;
	D3DXVECTOR4		i;	// I0, I1, I2, I3
	bool operator == (const PNCT3_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c  &&	t == Vertex.t)
		{
			return true;
		}
		return  false;
	}
	PNCT3_VERTEX() {}
	PNCT3_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt,
		D3DXVECTOR4		vw,
		D3DXVECTOR4		vi)
	{
		p = vp, n = vn, c = vc, t = vt;
		w = vw, i = vi;
	}
};
// ─────────────────────────────────
//  쉐이더 사용시( 가중치 8개 제한 사용 )
// ─────────────────────────────────
struct PNCT5_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR4		c;
	D3DXVECTOR2		t;
	D3DXVECTOR4		w0;// W0, fW1, fW2, fW3;
	D3DXVECTOR4		i0;	// I0, I1, I2, I3
	D3DXVECTOR4		w1;// W4, fW5, fW6, fNumWeight;	
	D3DXVECTOR4		i1;	// I4, I5, I6, I7
	bool operator == (const PNCT5_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c  &&	t == Vertex.t)
		{
			return true;
		}
		return  false;
	}
	PNCT5_VERTEX() {}
	PNCT5_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt,
		D3DXVECTOR4		vw0,
		D3DXVECTOR4		vi0,
		D3DXVECTOR4		vw1,
		D3DXVECTOR4		vi1)
	{
		p = vp, n = vn, c = vc, t = vt;
		w0 = vw0, i0 = vi0, w1 = vw1, i1 = vi1;
	}
};

struct TBipedMesh
{
	T_STR		m_strName;
	int					m_iNumFace;
	D3DXMATRIX			m_matWorld;
	vector<PNC_VERTEX>	m_VertexList;
	PNC_VERTEX*		m_pDrawVertex;
};

struct VS_CONSTANT_BUFFER
{
	D3DXMATRIX matWorld;// c0						
	D3DXMATRIX matView;	// c4						
	D3DXMATRIX matProj;	// c8						
	D3DXVECTOR4 Color; // 12
};

struct TObjFrame
{
	vector<D3DXMATRIX>  m_matWorldList;
	int  				m_iIndex;
	TObjFrame(int iNumMesh, int iIndex)
	{
		m_matWorldList.resize(iNumMesh);
		m_iIndex = iIndex;
	}
};

typedef struct
{
	double x, y, z;
} Point3;



typedef struct
{
	/* sample time */
	double t;

	/* sample position */
	Point3 P;

	/* sample parameters for affecting tangential behavior at control point */
	double tension, continuity, bias;
}
PositionKey;

/* private structures to hide details of polynomials */
typedef struct
{
	/* P(u) = C0 + u*C1 + u^2*C2 + u^3*C3,  0 <= u <= 1 */
	Point3 C0, C1, C2, C3;

	/* sample time interval on which polynomial is valid, tmin <= t <= tmax */
	double tmin, tmax, trange;
}
CubicPolynomial;

typedef struct
{
	int numPolys;
	CubicPolynomial* poly;

	/* partial sums of arc length */
	double* length;
	double totalLength;
}
SplineInfo;