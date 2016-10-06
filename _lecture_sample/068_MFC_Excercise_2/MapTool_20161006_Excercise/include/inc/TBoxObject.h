#pragma once
#include "TShape.h"

typedef vector<INT>				INT_List;
typedef vector<INT>::iterator	INT_itor;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------

struct TVertex
{
	INT_List 		m_iFaceList;
	INT_List 		m_iEdgeList;
	PNCT_VERTEX	m_Format;
};
struct TEdge
{
	UINT			m_iIndex;
	UINT			m_iVertexID[2];
	float			m_fDistance;
	D3DXVECTOR3		m_vCenter;
	INT_List 		m_tFaceList;	
};
struct TFace
{
	UINT			m_iVertexID[3];
	UINT 			m_iEdge[3];
	UINT			m_NeightborFaceID[3];
	D3DXVECTOR3		m_vNormal;
};

typedef vector<TVertex>				TVertexArray;
typedef vector<TVertex>::iterator	TVertexitor;
typedef vector<TEdge>				TEdgeArray;
typedef vector<TEdge>::iterator		TEdgeitor;
typedef vector<TFace>				TFaceArray;
typedef vector<TFace>::iterator		TFaceitor;

class TBoxObject : public TBoxShape
{
public:
	TVertexArray				m_tVertexList;
	TEdgeArray					m_tEdgeList;
	TFaceArray					m_tFaceList;
	vector<PNCT_VERTEX>			m_VertexList;
	vector< UINT>				m_IndexList;
	UINT						m_iLODPhase;
	UINT						m_iPreLodCnt;
		
	D3DXMATRIX		m_matNormal;

public:
	//--------------------------------------------------------------------------------------
	// Create Vertex Buffer / Index Buffer
	//--------------------------------------------------------------------------------------
	HRESULT			CreateVertexBuffer();
	HRESULT			CreateIndexBuffer();
public:
	void			AddVertex(PNCT_VERTEX Format);
	void			AddEdge( UINT v0, UINT v1, UINT iFace );
	void			AddFace( UINT v0, UINT v1, UINT v2, UINT e0, UINT e1, UINT e2 );
	void			CreateNewVertex( TEdge Edge );
public:
	bool			SubDivide(bool bReLoadBuffer = true);
	HRESULT			ReLoadBuffer();
public:
	TBoxObject();
	virtual ~TBoxObject();
};

