#pragma once
#include "TBasis.h"

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


const enum OBJECTCLASSTYPE {
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY, 
	CLASS_BIPED,
};

const enum FILETYPE {
	NULLFILE = 0,
	MODELFILE,
	ASEFILE,
	TBSFILE,
	SKMFILE,
	MATFILE,
};

struct VersionMark
{
	int		iVersion;
	TCHAR	description[32];
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

struct TTextexMap
{
	// 오브젝트 텍스쳐 관리자에서 매터리얼의 텍스쳐파일명을 보고 DX텍스쳐 생성 후 참조인덱스를 저장한다.
	DWORD					m_dwIndex;
	// 텍스쳐 맵 타입인덱스
	DWORD					m_dwType;
	// 맵 텍스쳐 이름.
	TCHAR_STRING		m_strTextureName;
	TTextexMap() : m_dwType(1),m_dwIndex(0)	{}	
};
struct TMtrl
{	
	// 오브젝트 텍스쳐 관리자에서 매터리얼의 텍스쳐파일명을 보고 DX텍스쳐 생성 후 참조인덱스를 저장한다.
	DWORD					m_dwIndex;
	// 서브매터리얼 갯수
	DWORD					m_dwSubCount;
	// 텍스쳐 맵 갯수
	DWORD					m_dwTexMapCount;
	// 맵클래스 이름
	TCHAR_STRING		m_strName;
	// 맵클래스 이름
	TCHAR_STRING		m_strClassName;
	// 디퓨즈 맵 텍스쳐 이름.
	TCHAR_STRING		m_strTextureName;
	// 맵타입들
	vector<TTextexMap>	m_TexMaps;	
	// 서브매터리얼 저장벡터
	vector<TMtrl>			m_SubMaterial;
	TMtrl() : m_dwSubCount(0), m_dwIndex(0), m_dwTexMapCount(0)
	{
	}
	~TMtrl() { stl_wipe_vector( m_SubMaterial );}
};


struct TFaceList
{
	union
	{
		struct {DWORD	_0, _1,_2;};
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
	TVertexList() : dwNumVertex(0),dwNumFace(0)
	{
	}
	~TVertexList() { stl_wipe_vector( pVertexList ); stl_wipe_vector( pVertexList ); }
};

struct TAnimTrack	
{
	int					iTick;
	D3DXQUATERNION		qRotate;
	D3DXVECTOR3			vVector;
	TAnimTrack*			pNext;
	TAnimTrack*			pPrev;	
};

struct TAseMesh
{	
	D3DXMATRIX				m_matWorld;
	TCHAR_STRING			m_strNodeName;
	DWORD					m_iNumFace;
	INT						m_iMtrlRef;
	TVertexList				m_PosVertexList;
	TVertexList				m_TexVertexList;
	TVertexList				m_ColVertexList;
	TVertexList				m_NorVertexList;	
	
	D3DXMATRIX				m_matWorldTrans;	// 월드 이동 행렬
	D3DXMATRIX				m_matWorldRotate;	// 월드 회전 행렬
	D3DXMATRIX				m_matWorldScale;	// 월드 신축 행렬

	vector<TAnimTrack>		m_PosTrack;		// 이동 트랙 
	vector<TAnimTrack>		m_RotTrack;		// 회전 트랙
	vector<TAnimTrack>		m_SclTrack;		// 신축 트랙	
	// 추가
	vector<TAnimTrack>		m_VisTrack;		// 신축 트랙
	OBJECTCLASSTYPE			m_ClassType;		// 본 : 더미 : 지오메트리 지정	
	TCHAR_STRING			m_strParentName;	// 부모이름
	T_BOX					m_BBox;
	TAseMesh()
	{
		m_iNumFace = 0;
		m_iMtrlRef = -1;
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