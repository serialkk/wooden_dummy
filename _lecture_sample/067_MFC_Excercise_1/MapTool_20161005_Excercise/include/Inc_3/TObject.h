#pragma once
#include "TModel.h"
#include "TRender.h"

struct TObjWM
{
	vector<D3DXMATRIX>	m_matCalculation;
	vector<D3DXMATRIX>	m_matAnim;
	vector<int>			m_iParent;
};
class TObject : public TRender
{
public:
	TCHAR_STRING		m_szName;
	vector<TModel*>		m_pModelList;	
	vector<TObjWM*>		m_matWorldList;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matView;
	D3DXMATRIX			m_matProj;
	bool				m_bDynamicCB; // 로칼 상수버퍼 사용 유무
	TAnimation			m_Animation;
	TInputLayout		m_InputLayout;
	HRESULT				SetInputLayout(ID3D11Device* pd3dDevice,D3D11_INPUT_ELEMENT_DESC* pLayout= NULL, UINT numElements = 4);

	ID3DX11EffectTechnique*		m_pTechnique;
	ID3DX11EffectTechnique*		m_pTechniqueColor;
	ID3DX11EffectTechnique*		m_pTechniqueApply;	

	ID3DX11EffectMatrixVariable* m_pWorldVariable;
	ID3DX11EffectMatrixVariable* m_pViewVariable;
	ID3DX11EffectMatrixVariable* m_pProjVariable;
	ID3DX11EffectMatrixVariable* m_pNormalVariable;
	ID3DX11EffectShaderResourceVariable* m_pTextureVariable;

	cbChangesEveryFrame			m_cbEveryFrame;
	cbChangeOnResize			m_cbOnResize;
	ID3D11Buffer*				m_pEveryFrameCBuffer; // 상수버퍼
	ID3D11Buffer*				m_pOnResizeCBuffer; // 상수버퍼
	ID3D11Buffer*				m_pGlobalEveryFrameCBuffer; // 상수버퍼
	ID3D11Buffer*				m_pGlobalOnResizeCBuffer; // 상수버퍼

	HRESULT					CreateConstantBuffer(D3D11_USAGE type = D3D11_USAGE_DEFAULT);
	void					SetEveryFrameCBuffer( ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matWorld, D3DXMATRIX& matView );
	void					SetOnResizeCBuffer(ID3D11DeviceContext* pImmediateContext, D3DXMATRIX& matProj);
	bool					SetupRender(	ID3D11DeviceContext*	pImmediateContext, 
											ID3D11Buffer* pCB0=0, 
											ID3D11Buffer* pCB1=0 );
public:
	UINT				m_iFilelIndex; // 파일관리자 저장 인덱스
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
	void		GetEffectVariable();
	// 사용하려는 스킨메쉬 파일명, 에니메이션매트릭스 인덱스, 쉐이더 인덱스
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
	void		SetTechnique(ID3DX11EffectTechnique* pTechnique=0);
	HRESULT		SetConstantBuffer(ID3D11Buffer*	pConstantBuffer );
	
	bool		DrawGroup(ID3D11DeviceContext* pContext, TModel* pObj,  int iObject, ID3DX11EffectTechnique* pApply = NULL, bool bCommand = false );
	bool		DrawMesh(ID3D11DeviceContext* pContext, TModel* pObj, TMesh* pMesh, ID3DX11EffectTechnique* pApply = NULL );

	bool		Setup(ID3D11DeviceContext* pd3dDeferredContext );
	void		SetCB( ID3D11DeviceContext* pContext, TMesh* pMesh, D3DXMATRIX matWorld, bool bUpdate = true );
	void		ApplyCB( bool bUse = false ) { m_bDynamicCB = bUse; };
	bool		SetCommandRender(ID3D11DeviceContext* pContext, bool bUpdateCB = true);
	bool		CommandRender(ID3D11DeviceContext* pContext, bool bUpdateCB =true);
	bool		CommandDraw(ID3D11DeviceContext* pContext, TModel* pObj, vector<D3DXMATRIX>& matWorld);
	bool		CommandDraw(ID3D11DeviceContext* pContext, TModel* pObj );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT						CreateResource();
	virtual HRESULT						DeleteResource();
public:
	TObject(void);
	~TObject(void);
};
