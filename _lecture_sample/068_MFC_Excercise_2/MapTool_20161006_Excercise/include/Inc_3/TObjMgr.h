#pragma once
#include "TTemplate.h"
#include "TObject.h"

class TObjMgr: public TTemplateMap< TObject >, public TSingleton<TObjMgr> 
{
private:
	friend class TSingleton<TObjMgr>;
	TModel*		m_pModelObj;
public:			
	
	int			Load(	ID3D11Device* pd3dDevice, 
						ID3D11DeviceContext*    pImmediateContext,	
						const TCHAR* strObjectName,
						const TCHAR* strFileName, 
						const TCHAR* strShaderName,
						TModel* pOwnerModel,
						TModel* pFileModel,
						LPCSTR strVSEntryPoint = NULL, 
										LPCSTR strPSEntryPoint= NULL, 
										LPCSTR strShaderModel= NULL);
	TObject*	LoadFile( ID3D11Device* pd3dDevice, const TCHAR* pszFileName , TModel* pModel = 0);		
	//void		SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj );
private:
	TObjMgr(void);
	virtual ~TObjMgr(void);
};
#define I_ObjMgr TObjMgr::GetInstance()