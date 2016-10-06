#pragma once
#include "TModel.h"
#include "TAseParser.h"

class TAseObj : public TModel
{
public:	
	//typedef TMeshData<PNCT_VERTEX>			TMESH_VERTEX;
	//typedef vector<TMESH_VERTEX*>		TMESH_VECTOR;
	//TMESH_VECTOR			m_pMeshList;
	TAseParser				m_Parser;
	TScene					m_Scene;
	vector<TMtrl>			m_Material;
	float					m_fElapseTime;
	TCHAR_STRING			m_szDirName;
	TCHAR_STRING			m_szName;

public:
	bool					Init();
	bool					Frame();
	bool					Render();
	bool					Release();
	bool					ResetResource();
	bool					Convert();
	bool					Load( const TCHAR* strFileName );
	bool					SetRenderBuffer();
	bool					CreateVertexIndexBuffer(TMeshData<PNCT_VERTEX>* pMesh,
													D3D11_USAGE usage=D3D11_USAGE_DEFAULT);
	void					SetTriangleBuffer(		TMeshData<PNCT_VERTEX>* pMesh,  
													TAseMesh* pAseMesh, 
													DWORD dwMask = 0x00000000 );
	int						GetMapID( TMtrl* pMtrl, int iTexMapType=ID_TBASIS_DI ); // �� �ε��� �˻�
	void SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj )
	{
		if( pWorld != NULL )
		{
			m_matWorld	= *pWorld;
		}
		else
		{
			D3DXMatrixIdentity(&m_matWorld);
		}
		if( pView != NULL )
		{
			m_matView	= *pView;
		}
		if( pProj != NULL )
		{
			m_matProj	= *pProj;
		}	
	}
	//--------------------------------------------------------------------------------------
	// ���ϸ��̼� ���� �Լ� 
	//--------------------------------------------------------------------------------------
	TAnimTrack*				SetDoublyLinkedList( TAnimTrack* pCurrentTrack, TAnimTrack* pPrev );//���� ���� ����Ʈ ����
	bool					GetAnimationTrack(	float fFrame, 
												vector<TAnimTrack*> pTrackList, 
												TAnimTrack** ppStartTrack, 
												TAnimTrack** ppEndTrack );
	void					Interpolate(		TMeshData<PNCT_VERTEX>* pMesh, 
												D3DXMATRIX* matParent,
												float fFrameTick );
	bool					InheriteCollect();
	TMeshData<PNCT_VERTEX>*		SearchToCollects(	/*vector<TMeshData<PNCT_VERTEX>*>& pMeshList,*/ 
												TCHAR_STRING	m_strParentName );

public:
	TAseObj(void);
	~TAseObj(void);
};
