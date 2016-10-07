#pragma once
#include "TObjStd.h"
#include <tchar.h>
class TMesh;
class TModel;

struct TVertexLayout
{
	vector<D3D11_INPUT_ELEMENT_DESC> Element;
};
struct TObjWM
{
	TModel*				m_pModel;
	float				m_fElapseTime;
	TScene				m_Scene;
	vector<D3DXMATRIX>	m_matCalculation;
	vector<D3DXMATRIX>	m_matAnim;
	vector<int>			m_iParent;
	TObjWM(int iNumMesh)
	{
		m_pModel = NULL;
		m_fElapseTime = 0.0f;
		m_matCalculation.resize(iNumMesh);
		m_matAnim.resize(iNumMesh);
		m_iParent.resize(iNumMesh);
		for (int iMesh = 0; iMesh < iNumMesh; iMesh++)
		{
			D3DXMatrixIdentity(&m_matCalculation[iMesh]);
			D3DXMatrixIdentity(&m_matAnim[iMesh]);
			m_iParent[iMesh] = -1;
		}
	}
};
class TModel
{
public:
	vector<shared_ptr<TMesh>>	m_pMesh;
	ID3D11Device*				m_pd3dDevice;
	ID3D11DeviceContext*		m_pContext;
	DX::TDxObject				m_dxobj;

	VS_CONSTANT_BUFFER			m_cbData;
	D3DXVECTOR3					m_vCenter;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	vector<DWORD>				m_IndexList;
	vector<PNCT_VERTEX>			m_VertexList;
	TScene				m_Scene;
	FILETYPE			m_ObjType;
	float				m_fElapseTime;
	int					m_iStartFrame;
	int					m_iLastFrame;
	T_STR				m_szDirName;
	T_STR				m_szName;
	///  Buffer Comine 
	UINT				m_iMaxVertex;
	UINT				m_iMaxIndex;
	UINT				m_iBeginPosVB;
	UINT				m_iBeginPosIB;
	bool				m_bOptimization;
	int					m_iMatrixIndex;	
public:
	ID3D11Buffer*				GetVB();
	ID3D11Buffer*				GetIB();
	virtual int					GetMeshCounter() { return 0; }
	virtual void				SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual void				SetAmbientColor(float fR, float fG, float fB, float fA);
	virtual bool				Convert(ID3D11Device* pDevice);
	virtual bool				Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread = false);
	virtual HRESULT				LoadShaderFile(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile);
	virtual HRESULT				SetInputLayout();
	virtual bool				CreateVertexData();
	virtual bool				CreateIndexData();
	virtual HRESULT				CreateVertexBuffer();
	virtual HRESULT				CreateIndexBuffer();
	virtual HRESULT				CreateConstantBuffer();
	virtual HRESULT				LoadTextures(ID3D11Device* pDevice, const TCHAR* pLoadTextureString);
	virtual HRESULT				CreateResource();
	virtual HRESULT				DeleteResource();
	virtual bool				UpdateBuffer();
	virtual void				ObjectFrame(TObjFrame* pObjFrame, float fTickFrame) {};
	virtual void				ObjectRender(ID3D11DeviceContext*    pContext, TObjFrame* pObjFrame) {};
	virtual bool				Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString = 0);
	virtual bool				Init();
	virtual bool				Frame();
	virtual bool				PreRender(ID3D11DeviceContext* pContext);
	virtual bool				Render(ID3D11DeviceContext*		pContext);
	// 지연 컨텍스트의 사용시에 즉시 컨텍스트로 변경하기 위해서 로직에서 가상 함수화 하였다.
	virtual void				UpdateConstantBuffer(ID3D11DeviceContext* pContext, TModel* pParent= NULL);
	virtual bool				PostRender(ID3D11DeviceContext* pContext);
	virtual bool				Draw(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor);
	virtual bool				Release();
	virtual void				SetMatrixIndex(int iMatrixIndex) { m_iMatrixIndex = iMatrixIndex; }
public:
	TModel(void);
	virtual ~TModel(void);
};