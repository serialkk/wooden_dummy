#pragma once
#include "TObjStd.h"

template< class T > struct TTri
{
	T						vVertex[3];
	D3DXVECTOR3  vNormal;
	int						iSubIndex;
	TTri( int Index )  : iSubIndex(Index) {}
	TTri()	: iSubIndex(-1) {}
};
template< class T > struct DescendingTriSort
{
	bool operator()(TTri<T>& rpStart, TTri<T>& rpEnd)
	{		
		return rpStart.iSubIndex < rpEnd.iSubIndex;
	}
};
template< class T > struct IsTriangleSame    
{   
	TTri<T>			m_Tri;  
	IsTriangleSame( TTri<T> data ) : m_Tri(data) {}
	bool operator()(TTri<T>& value)
    {   
        return value.iSubIndex == m_Tri.iSubIndex;   
    }   
}; 
struct TMESH_HEADER
{
	OBJECTCLASSTYPE		m_ClassType;
	T_BOX				m_BBox;
	D3DXMATRIX			m_matWorld;
	int					m_iNumFace;
	int					m_iMtrlRef;
	int					m_iNumTrack[4];	
};

template <class T >  class TMeshData : public TMESH_HEADER
{
public:
	int						m_iIndex;
	TCHAR_STRING			m_strNodeName;
	TCHAR_STRING			m_strParentName;
	D3DXMATRIX				m_matInverse;	
	T*						m_pDrawVertex;

	typedef vector<T>		TVERTEX_ARRAY;	
	TVERTEX_ARRAY 			m_VertexArray;
	vector<DWORD>			m_IndexArray;
	UINT					m_iVertexCnt;
	UINT					m_iIndexCnt;
	UINT					m_iVertexStart;
	UINT					m_iIndexStart;
	UINT					m_iNumMtrl;
	UINT					m_iNumTex;
	vector<TMeshData<T>*>	m_pSubMesh;
	vector<TMeshData<T>*>	m_pChildMesh;
	vector<TTri<T>>			m_TriList;	
	TDxBuffer				m_BufferVB;		
	TDxBuffer				m_BufferIB;	
	ID3D11CommandList*      m_pd3dCommandList;
	TMeshData<T>*			m_pParent;
	D3DXMATRIX				m_matWorldTrans;
	// m_matCalculation�� ��Ƽ������ ���ô� ����� �ϸ� �ȵȴ�. 
	// �̴� TMeshData�� ��������� �����ϴ� �������̱� �����̴�.
	// �ٸ� ������� �ʱ� ����� �� ���� ����ϱ� ������ ������ ������ �� ������ �����ӿ��� ���ŵǱ� �����̴�.
	D3DXMATRIX				m_matCalculation;

	D3DXMATRIX				m_matWorldRotate;
	D3DXMATRIX				m_matWorldScale;
	vector<TAnimTrack*>		m_pPosTrack;
	vector<TAnimTrack*>		m_pRotTrack;
	vector<TAnimTrack*>		m_pSclTrack;
	vector<TAnimTrack*>		m_pVisTrack;
	float					m_fVisibility;
	bool					m_bUsed;
	int						m_iTexIndex;
	int						m_iVertexSize;
	int						m_iIndexSize;
	// �ؽ��� ����( �ؽ��� �� ���� )
	int						m_iDiffuseTex;	
	int						m_iTexType[13];
	TCHAR					m_szTexName[13][30];

	static TMeshData<T>*		NewMesh();
	int  IsEqulVertexList( TVERTEX_ARRAY&  VertexArray, T& Vertex );	
	int  SetUniqueBuffer( vector <TTri<T>>& TriList, int iMtrl, int iStartTri );
public:
	TMeshData(void)
	{
		m_iNumFace		= 0;
		m_iIndex		= -1; // ������ ����
		m_iTexIndex		= -1;	
		m_iMtrlRef		= -1;
		m_pParent		= 0;   //�߰�
		m_iVertexCnt	= 0;
		m_iIndexCnt		= 0;
		m_iVertexStart	= 0;
		m_iIndexStart	= 0;
		m_iNumMtrl		= 0;
		m_iDiffuseTex = -1;
		m_iNumTex		= 0;
		m_pd3dCommandList = 0;
		m_iVertexSize	= sizeof(T);
		m_iIndexSize	= sizeof(DWORD);
		D3DXMatrixIdentity(&m_matWorldTrans);
		D3DXMatrixIdentity(&m_matWorldRotate);
		D3DXMatrixIdentity(&m_matWorldScale);
		D3DXMatrixIdentity(&m_matCalculation);
	};
	virtual ~TMeshData(void)
	{
		SAFE_RELEASE( m_pd3dCommandList );
	};
};
template <class T > TMeshData<T>* TMeshData<T>::NewMesh()
{
	TMeshData<T>* pMesh = NULL;
	SAFE_NEW( pMesh, TMeshData<T> );	
	return pMesh;
}

template <class T > 
int TMeshData<T>::IsEqulVertexList( TVERTEX_ARRAY&  VertexArray, T& Vertex )
{
	for( int iVertex=0; iVertex < VertexArray.size(); iVertex++ ) 
	{
		if( VertexArray[iVertex] == Vertex  )					
		{				
			return iVertex;
		}
	}
	return -1;
}

template <class T > 
int TMeshData<T>::SetUniqueBuffer( vector <TTri<T>>& TriList, int iMtrl, int iStartTri )
{
	int iNumFaces = TriList.size();
	m_VertexArray.reserve(iNumFaces*3);
	m_IndexArray.reserve(iNumFaces*3);

	TTri<T>  triSame( iMtrl );
	if( iMtrl >= 0 )
	{
		iNumFaces = count_if( TriList.begin(), TriList.end(), IsTriangleSame<T>(triSame) );
	}

	for( int iFace = 0; iFace < iNumFaces; iFace++ )
	{			
		for( int iCnt = 0; iCnt < 3; iCnt++ )
		{
			int iPosReturn = IsEqulVertexList( m_VertexArray, TriList[iStartTri+iFace].vVertex[iCnt] );
			if( iPosReturn < 0 )
			{				
				m_VertexArray.push_back(TriList[iStartTri+iFace].vVertex[iCnt]);
				iPosReturn = m_VertexArray.size()-1;
			}
			m_IndexArray.push_back( iPosReturn );			
		}				
	}

	m_iNumFace = iNumFaces;
	return iNumFaces;
}

class TMesh : public TMeshData< PNCT_VERTEX >
{
};
