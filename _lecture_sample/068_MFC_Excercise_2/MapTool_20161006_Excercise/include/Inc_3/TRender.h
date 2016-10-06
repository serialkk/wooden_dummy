#pragma once

#include "TDxBuffer.h"
#include "TInputLayout.h"
#include "TTimer.h"
#include "TAnimation.h"

class TRender
{
public:
	ID3D11Device*				m_pd3dDevice;	
	ID3D11DeviceContext*		m_pd3dImmediateContext;
	ID3D11CommandList*          m_pd3dCommandList;
	TShader*					m_pShader;
	int							m_iPrimitiveType;
	int							m_iVertexSize;
	int							m_iIndexSize;
public:
	virtual void	SetContext(ID3D11DeviceContext* pd3dImmediateContext){m_pd3dImmediateContext = pd3dImmediateContext;};
	virtual TShader*  LoadEffectFile(	const TCHAR* strShaderFile, 	
										D3D10_SHADER_MACRO* pShaderMacros	= 0);		
	virtual TShader*  LoadShaderFile(	const TCHAR* strShaderFile, 	
										LPCSTR strVSEntryPoint=0, 
										LPCSTR strPSEntryPoint=0, 
										LPCSTR strShaderModel=0,
										D3D10_SHADER_MACRO* pShaderMacros	= 0);		
	virtual TShader* 	LoadShader(	ID3D11Device* pd3dDevice,
										TCHAR* pLoadShaderFile,
										CHAR* pEntryPoint, 
										CHAR* pCompiler,
										STAGE_TYPE type = t_VS);
	virtual void	BindVertexBuffer( ID3D11DeviceContext* pContext,
										ID3D11Buffer* pVertexBuffer=0, 
												UINT iStrides=0,							
												UINT iStartSlot = 0,
												UINT iNumBuffers = 1,																	
												UINT iOffsets = 0  );
	virtual void	BindIndexBuffer(	ID3D11DeviceContext* pContext,		
										ID3D11Buffer *pIndexBuffer=0,
										DXGI_FORMAT Format=DXGI_FORMAT_R32_UINT,
										UINT Offset=0 );

	virtual void	Draw(	ID3D11DeviceContext* pContext,ID3DX11EffectTechnique* pTechnique, TShader* pShader,
							UINT VertexCount,
							UINT StartVertexLocation=0);
	virtual void	DrawIndex(	ID3D11DeviceContext* pContext,ID3DX11EffectTechnique* pTechnique, TShader* pShader,
								UINT IndexCount, 
								UINT StartIndexLocation=0, 
								INT BaseVertexLocation=0);
	virtual HRESULT	SetCommmandList(ID3D11DeviceContext* pContext, TMesh* pSubMesh, bool bSave=false );
	virtual void	ExecuteCommandList(ID3D11DeviceContext* pContext,TMesh* pSubMesh, bool bClear=true );
public:
	TRender(void);
	virtual ~TRender(void);
};
