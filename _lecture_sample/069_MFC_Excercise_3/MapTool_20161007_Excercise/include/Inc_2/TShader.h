#pragma once
#include "TBasisStd.h"
#include "TInputLayout.h"

enum STAGE_TYPE { t_VS, t_HS, t_DS, t_GS, t_PS, t_CS };

class TShader
{
public:
	T_STR		m_szName;
	T_STR		m_szPath;
	int					m_iIndex;
	ID3DBlob*			m_pBuffer;
	ID3DBlob*			m_pBlobVS;
	ID3DX11EffectTechnique*		m_pTechnique;
	TInputLayout		m_InputLayout;
public:
	//--------------------------------------------------------------------------------------
	// Effect Variables
	//--------------------------------------------------------------------------------------
	ID3DX11Effect*           m_pEffect;
	ID3DX11Effect*			GetEffect();
	//--------------------------------------------------------------------------------------
	// VS & PS Variables
	//--------------------------------------------------------------------------------------
	ID3D11VertexShader*         m_pVertexShader;//정점쉐이더	
	ID3D11HullShader*			m_pHullShader;//헐 쉐이더
	ID3D11DomainShader*			m_pDomainShader;//도메인쉐이더
	ID3D11GeometryShader*       m_pGeometryShader;//기하쉐이더
	ID3D11PixelShader*          m_pPixelShader;//픽쉘쉐이더
	ID3D11ComputeShader*		m_pComputeShader;//컴퓨터쉐이더


	void			Apply(ID3D11DeviceContext*	pd3dContext);
	HRESULT			Load(ID3D11Device* pd3dDevice,
		TCHAR* pLoadShaderFile,
		CHAR* pEntryPoint,
		CHAR* pCompiler,
		STAGE_TYPE type = t_VS,
		ID3DBlob* pLoadBlob = 0);
	void			ApplyVS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	void			ApplyHS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	void			ApplyDS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	void			ApplyGS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	void			ApplyPS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	void			ApplyCS(ID3D11DeviceContext*	pd3dContext, bool bUse = true);
	//--------------------------------------------------------------------------------------
	// ID3DX11EffectTechnique map
	//--------------------------------------------------------------------------------------
	HRESULT			Load(ID3D11Device* pDevice,
		const TCHAR* strShaderPath,
		LPCSTR strVSEntryPoint = 0,
		LPCSTR strPSEntryPoint = 0,
		LPCSTR strShaderModel = 0,
		UINT Flags = D3DCOMPILE_ENABLE_STRICTNESS);

	HRESULT			SetInputLayout(ID3D11Device* pd3dDevice, D3D11_INPUT_ELEMENT_DESC* pLayout, UINT numElements, ID3DBlob* pBuffer);
public:
	typedef map < CHAR_STRING, ID3DX11EffectTechnique*>		TechniqueMap;
	typedef TechniqueMap::iterator							TechniqueMapItor;
	TechniqueMap											m_TechMap;
	ID3DX11EffectTechnique*				AddTechnique(CHAR_STRING Word);
	ID3DX11EffectTechnique*				GetTechniquePtr(CHAR_STRING String);

	//--------------------------------------------------------------------------------------
	// ID3DX11EffectVariable map
	//--------------------------------------------------------------------------------------
public:
	typedef map < CHAR_STRING, ID3DX11EffectVariable*>		VariableMap;
	typedef VariableMap::iterator							VariableMapItor;
	VariableMap												m_VariMap;
	ID3DX11EffectVariable*				AddVariable(CHAR_STRING Word);
	ID3DX11EffectVariable*				GetVariablePtr(CHAR_STRING String);
	HRESULT								SetResource(CHAR_STRING string,
		ID3D11ShaderResourceView*	pSRV);
	//--------------------------------------------------------------------------------------
	// 유니코드 변환 유틸
	//--------------------------------------------------------------------------------------
public:
	wchar_t*				CharToWChar(const char* pString);
	char*					WCharToChar(const wchar_t* pwstrSrc);

	//--------------------------------------------------------------------------------------
	// 멤버 함수
	//--------------------------------------------------------------------------------------
public:


	void					ClearShaderResources(ID3D11DeviceContext*  pImmediateContext);
	bool					Release();
	HRESULT					CompileShaderFromFile(const WCHAR* szFileName, DWORD flags, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT					CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

public:
	TShader(void);
	virtual ~TShader(void);
};

class TShaderMgr : public TSingleton < TShaderMgr >
{
private:
	friend class TSingleton<TShaderMgr>;
	ID3D11Device*			m_pd3dDevice;
public:
	typedef map <INT, TShader*>					TemplateMap;
	typedef TemplateMap::iterator				TemplateMapItor;
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	INT											m_iCurIndex;


public:
	void			SetDevice(ID3D11Device*	 pDevice);
	INT				Add(const TCHAR *pFileName, LPCSTR strVSEntryPoint = 0,
		LPCSTR strPSEntryPoint = 0,
		LPCSTR strShaderModel = 0);
	INT				Add(TCHAR* pLoadShaderFile,
		CHAR* pEntryPoint,
		CHAR* pCompiler,
		STAGE_TYPE type = t_VS);
	TShader*		GetPtr(INT iIndex);
	bool			Release();
	bool			Delete(INT iDelete);
public:
	TShaderMgr();
	virtual ~TShaderMgr();
};
#define I_Shader TShaderMgr::GetInstance()