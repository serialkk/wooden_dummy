#pragma once
#include "TModel.h"
#include "TAseParser.h"

class TAseObj : public TModel
{
private:	
	TAseParser				m_Parser;
	vector<TMtrl>			m_Material;
	T_STR			m_szDirName;
	T_STR			m_szName;
public:
	bool					Init();
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
	//--------------------------------------------------------------------------------------
	// ���ϸ��̼� ���� �Լ� 
	//--------------------------------------------------------------------------------------
	TAnimTrack*				SetDoublyLinkedList( TAnimTrack* pCurrentTrack, TAnimTrack* pPrev );//���� ���� ����Ʈ ����
	bool					InheriteCollect();
	TMeshData<PNCT_VERTEX>*		SearchToCollects(	/*vector<TMeshData<PNCT_VERTEX>*>& pMeshList,*/ 
												T_STR	m_strParentName );

public:
	TAseObj(void);
	~TAseObj(void);
};
