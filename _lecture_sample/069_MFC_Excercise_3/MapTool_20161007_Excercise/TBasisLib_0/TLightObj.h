#pragma once
#include "TBasisStd.h"

struct TLightInfo
{
	D3DXVECTOR3				m_vPosition;	// 라이트의 위치
	D3DXVECTOR3				m_vDirection;	// 라이트의 방향
	float					m_fRange;		// 광원의 유효 거리
	float					m_fFalloff;		// 내부 콘과 외부 콘의 휘도( Luminance )
	float					m_fTheta;		// 내부 콘의 각도 범위		
	float					m_fPhi;			// 외부 콘의 각도 범위
	D3DXVECTOR4				m_DiffuseColor;
};

class TLightObj : public TLightInfo
{
public:
	D3DXMATRIX				m_matInitWorld;
	D3DXMATRIX				m_matWorld;
	D3DXVECTOR3				m_vInitPosition;// 초기 라이트의 위치값
	D3DXVECTOR3				m_vScale;		// 라이트 오브젝트의 크기변환 값
	D3DXVECTOR3				m_vRotation;    // 라이트 오브젝트의 회전(xyz)
	D3DXVECTOR3				m_vOffset;		// 지형 높이에서 추가된 위치(x,y,z)
public:
	T_STR		m_szName;
	T_STR		m_szPath;
public:
	HRESULT				Load(ID3D11Device* pDevice, const TCHAR* strFilePath);
	void				SetPath(TCHAR* pPath);
	void					SetValue(D3DXVECTOR3* pvPos = NULL,
		D3DXVECTOR3* pvDir = NULL,
		float* pfRange = NULL,
		D3DXVECTOR4* pvColor = NULL,
		D3DXVECTOR3* pvScale = NULL,
		D3DXVECTOR3* pvRotation = NULL,
		float fTheta = D3DX_PI / 4.0f,
		float fPhi = 5.0f);
public:
	bool					Init();
	bool					Frame(float fElapaseTime = 0.0f, float fSecondPerFrame = 0.0f);
	bool					Update(D3DXMATRIX* pmatLightWorld);
	bool					Render();
	bool					Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	TLightObj(void);
	~TLightObj(void);
};
class TLightMgr : public TSingleton < TLightMgr >
{
private:
	friend class TSingleton<TLightMgr>;
	ID3D11Device*			m_pd3dDevice;
public:
	typedef map <INT, TLightObj*>					TemplateMap;
	typedef TemplateMap::iterator				TemplateMapItor;
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	INT											m_iCurIndex;


public:
	void			SetDevice(ID3D11Device*	 pDevice);

	//D3DXVECTOR3 vPosition( 0.0f, 10.0f, 0.0f );
	//D3DXVECTOR3 vDir( 0.0f, -1.0f, 0.0f );
	INT				Add(D3DXVECTOR3,
		D3DXVECTOR3,
		const TCHAR *pFileName = _T("NULL"));

	TLightObj* const		GetPtr(INT iIndex);
	TLightObj* const		GetPtr(T_STR strFindName);
	bool			Init();
	bool			Frame();
	bool			Render();
	bool			Release();
	bool			Update(D3DXMATRIX* pmatLightWorld);
public:
	TLightMgr();
	~TLightMgr();
};
#define I_Light	 TLightMgr::GetInstance()