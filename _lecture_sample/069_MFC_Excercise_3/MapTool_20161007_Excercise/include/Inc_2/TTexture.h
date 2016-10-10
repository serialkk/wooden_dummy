#pragma once
#include "TBasisStd.h"

class TTexture
{
public:
	T_STR		m_szName;
	T_STR		m_szPath;
	//--------------------------------------------------------------------------------------
	// 텍스쳐 로딩 및 리소스버퍼 생성
	//--------------------------------------------------------------------------------------
	ID3D11ShaderResourceView*	m_pTextureRV;
public:
	HRESULT						Load(ID3D11Device* pDevice,
									ID3D11DeviceContext*    pImmediateContext,
									const TCHAR* strFilePath);
	bool						Apply(ID3D11DeviceContext*    pImmediateContext);
	HRESULT						Apply( ID3DX11EffectShaderResourceVariable* pTextureVariable);
	bool						Release();
	void						SetPath( const TCHAR* pPath );

public:
	TTexture(void);
	virtual ~TTexture(void);
};

class TTextureMgr : public TSingleton < TTextureMgr >
{
private:
	friend class TSingleton<TTextureMgr>;
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;
public:
	typedef map <INT, TTexture*>				TemplateMap;
	typedef TemplateMap::iterator				TemplateMapItor;	
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	INT											m_iCurIndex;
	

public:
	void			SetDevice(ID3D11Device*	 pDevice,ID3D11DeviceContext*    pImmediateContext ); 
	INT				Add( const TCHAR *pFileName );
	INT				Add( const TCHAR *pFileName, const TCHAR* szPath );
	const TTexture*		GetPtr( INT iIndex );
	const TTexture*		GetPtr( T_STR strFindName );
	bool			Release();
public:	
	TTextureMgr();
	virtual ~TTextureMgr();
};
#define I_Texture TTextureMgr::GetInstance()

