#pragma once
#include "TRender.h"
#include "TAnimation.h"

typedef TMeshData<PNCT_VERTEX>	TMESH_VERTEX;
typedef vector<TMESH_VERTEX>	TMESH_VECTOR;

class TModel : public TRender
{
public:
	T_STR					m_szName;	
	//TMesh*							m_pMesh;
	std::shared_ptr<TMesh>			m_pMesh;
	vector<TMesh*>					m_pMeshList;
	UINT							m_iFilelIndex; // ���ϰ����� ���� �ε���
	TScene							m_Scene;
	D3DXMATRIX						m_matWorld;
	D3DXMATRIX						m_matView;
	D3DXMATRIX						m_matProj;
	TTexture						m_Texture;
	float				m_fElapseTime;
	int					m_iStartFrame;
	int					m_iLastFrame;
	UINT				m_iVertexCnt;
	UINT				m_iIndexCnt;
	D3DXMATRIX			m_matControlWorld;
public:	
	virtual bool			Init() { return true; };
	virtual bool			Frame(){ return true; };
	virtual bool			Render(ID3D11DeviceContext*	pImmediateContext){ return true; };
	virtual bool			Release(){ return true; };
	virtual D3DXMATRIX		Update(float fElapseTime, int iMesh );
	bool			Create( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext,							
							const TCHAR* strObjectName = 0, 
							const TCHAR* strFileName = 0, 
							const TCHAR* strShaderName = L"../../data/shader/shape.fx",
							TModel* pFileModel =0,
							LPCSTR strVSEntryPoint=0, 
							LPCSTR strPSEntryPoint=0, 
							LPCSTR strShaderModel=0);		
	virtual bool	Convert();
	virtual bool	Load(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pd3dImmediateContext, const TCHAR* szTexName, TModel* pFileModel=0);
public:
	TModel(void);
	virtual ~TModel(void);
};
