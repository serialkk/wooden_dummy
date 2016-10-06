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
	int iVersion;		// ����
	int	iFirstFrame;    // ���� ������
	int	iLastFrame;     // ������ ������
	int	iFrameSpeed;    // 1�ʴ� ������ ����(30)
	int	iTickPerFrame;  // 1�������� ƽ ��(160)
	int iNumMesh;		// �޽�������Ʈ ����
	int iMaxWeight;		// ���� �� ����ġ
	int iBindPose;		// ���ε� ���� ���ϸ��̼� ����
};

struct TTextexMap
{
	// ������Ʈ �ؽ��� �����ڿ��� ���͸����� �ؽ������ϸ��� ���� DX�ؽ��� ���� �� �����ε����� �����Ѵ�.
	DWORD					m_dwIndex;
	// �ؽ��� �� Ÿ���ε���
	DWORD					m_dwType;
	// �� �ؽ��� �̸�.
	TCHAR_STRING		m_strTextureName;
	TTextexMap() : m_dwType(1),m_dwIndex(0)	{}	
};
struct TMtrl
{	
	// ������Ʈ �ؽ��� �����ڿ��� ���͸����� �ؽ������ϸ��� ���� DX�ؽ��� ���� �� �����ε����� �����Ѵ�.
	DWORD					m_dwIndex;
	// ������͸��� ����
	DWORD					m_dwSubCount;
	// �ؽ��� �� ����
	DWORD					m_dwTexMapCount;
	// ��Ŭ���� �̸�
	TCHAR_STRING		m_strName;
	// ��Ŭ���� �̸�
	TCHAR_STRING		m_strClassName;
	// ��ǻ�� �� �ؽ��� �̸�.
	TCHAR_STRING		m_strTextureName;
	// ��Ÿ�Ե�
	vector<TTextexMap>	m_TexMaps;	
	// ������͸��� ���庤��
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
	
	D3DXMATRIX				m_matWorldTrans;	// ���� �̵� ���
	D3DXMATRIX				m_matWorldRotate;	// ���� ȸ�� ���
	D3DXMATRIX				m_matWorldScale;	// ���� ���� ���

	vector<TAnimTrack>		m_PosTrack;		// �̵� Ʈ�� 
	vector<TAnimTrack>		m_RotTrack;		// ȸ�� Ʈ��
	vector<TAnimTrack>		m_SclTrack;		// ���� Ʈ��	
	// �߰�
	vector<TAnimTrack>		m_VisTrack;		// ���� Ʈ��
	OBJECTCLASSTYPE			m_ClassType;		// �� : ���� : ������Ʈ�� ����	
	TCHAR_STRING			m_strParentName;	// �θ��̸�
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