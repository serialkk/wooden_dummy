#pragma once
#include "TMesh.h"

typedef TData<PNCT5_VERTEX>				tSkmMesh;
typedef vector<shared_ptr<tSkmMesh>>	tSkmMeshList;

class TSkinObj : public TModel
{
public:
	VersionMark						m_VersionMark;
	int								m_iMaxWeight;	
	tSkmMeshList					m_pData;
	vector<D3DXMATRIX>				m_matBipedList;
	vector<D3DXMATRIX>* GetMatrix() { return &m_matBipedList; };
public:
	bool		Render(ID3D11DeviceContext*    pContext);
	bool		Release();
	bool		Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread = false);
	bool		Convert(const TCHAR* strPathName=0 );
	bool		LoadMesh( FILE	*fp, TMesh* pMesh, tSkmMesh* pData, const TCHAR* szFileName);

	void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);	
	HRESULT		SetInputLayout();
	bool		UpdateBuffer();
	bool		CombineBuffer(ID3D11Buffer* pVB, ID3D11Buffer* pIB);
	bool		Draw(ID3D11DeviceContext*    pContext, TModel* pParent);

public:
	TSkinObj(void);
	virtual ~TSkinObj(void);
};
