#pragma once
#include "TModel.h"

struct TObjWM
{
	vector<D3DXMATRIX>	m_matCalculation;
	vector<D3DXMATRIX>	m_matAnim;
	vector<int>			m_iParent;
};
class TObject : public TRender
{
public:
	T_STR		m_szName;
	vector<TModel*>		m_pModelList;	
	vector<TObjWM*>		m_matWorldList;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matView;
	D3DXMATRIX			m_matProj;
	TAnimation			m_Animation;	
public:
	UINT				m_iFilelIndex; // ���ϰ����� ���� �ε���
	TModel*				m_pModelObj;
	float				m_fElapseTime;
	int					m_iStartFrame;
	int					m_iLastFrame;
	UINT				m_iVertexCnt;
	UINT				m_iIndexCnt;

	TScene				m_Scene;
	D3DXMATRIX			m_matControlWorld;
    //--------------------------------------------------------------------------------------
	// Collision Data
	//--------------------------------------------------------------------------------------
	T_BOX                       m_Box;
    T_SPHERE                    m_Sphere;
    T_PLANE                     m_Plane;
	bool	Render(ID3D11DeviceContext* pContext, bool bUpdateCB = true);
public:
	bool		Init();
	bool		Create( ID3D11Device* pd3dDevice,
						ID3D11DeviceContext* pd3dImmediateContext,
							const TCHAR* strObjectName = 0, 
							const TCHAR* strFileName = 0, 
							const TCHAR* strShaderName = L"../../data/shader/shape3.fx",
							TModel* pFileModel =0,
							LPCSTR strVSEntryPoint=0, 
							LPCSTR strPSEntryPoint=0, 
							LPCSTR strShaderModel=0);	
	// ����Ϸ��� ��Ų�޽� ���ϸ�, ���ϸ��̼Ǹ�Ʈ���� �ε���, ���̴� �ε���
	bool		Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, const TCHAR* strFileName, TModel* pFileModel );
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		ResetResource();
	bool		Draw(ID3D11DeviceContext* pContext, TModel* pObj, vector<D3DXMATRIX>& matWorld, bool bCommand = false, bool bUpdate=true);
	bool		Draw(ID3D11DeviceContext* pContext, TModel* pObj, bool bCommand = false );
	void		SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj );
	TModel*		SetActionFrame( TCHAR* pStrModel, DWORD dwStrat, DWORD dEnd );
	TModel*		SetActionFrame( DWORD dwIndex, DWORD dwStrat, DWORD dEnd );
	HRESULT		SetConstantBuffer(ID3D11Buffer*	pConstantBuffer );
	
	bool		DrawGroup(ID3D11DeviceContext* pContext, TModel* pObj,  int iObject, bool bCommand = false );
	bool		DrawMesh(ID3D11DeviceContext* pContext, TModel* pObj, TMesh* pMesh );

	bool		Setup(ID3D11DeviceContext* pd3dDeferredContext );
	void		SetCB( ID3D11DeviceContext* pContext, TMesh* pMesh, D3DXMATRIX matWorld, bool bUpdate = true );
	
	bool		SetCommandRender(ID3D11DeviceContext* pContext, bool bUpdateCB = true);
	bool		CommandRender(ID3D11DeviceContext* pContext, bool bUpdateCB =true);
	bool		CommandDraw(ID3D11DeviceContext* pContext, TModel* pObj, vector<D3DXMATRIX>& matWorld);
	bool		CommandDraw(ID3D11DeviceContext* pContext, TModel* pObj );
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateResource();
	virtual HRESULT						DeleteResource();
public:
	TObject(void);
	~TObject(void);
};
