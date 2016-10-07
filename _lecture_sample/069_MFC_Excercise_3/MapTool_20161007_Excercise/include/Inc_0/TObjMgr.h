#pragma once
#include "TTemplate.h"
#include "TAseObj.h"
#include "TTbsObj.h"
#include "TSkinObj.h"
#include "TBoneObj.h"

class TObjMgr : public TTemplateMap< TModel >, public TSingleton<TObjMgr>
{
private:
	friend class TSingleton<TObjMgr>;
	TModel*		m_pModelObj;
public:
	int			Load(ID3D11Device* pd3dDevice,
		const TCHAR* strFileName,
		const TCHAR* strShaderName, bool bThread = false);
	
	FILETYPE	GetFileTypeID(const TCHAR* pszFileName);
	void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
private:
	TObjMgr(void);
	virtual ~TObjMgr(void);
};

static TAseObj* IsAseObjType(TModel* pModel)
{
	const std::type_info& r1 = typeid(*pModel);
	const std::type_info& r2 = typeid(TAseObj);
	TAseObj* pObj = nullptr;
	if (&r1 == &r2)
	{
		pObj = dynamic_cast<TAseObj*>(pModel);
	}	
	return pObj;
}
static TTbsObj* IsTbsObjType(TModel* pModel)
{
	const std::type_info& r1 = typeid(*pModel);
	const std::type_info& r2 = typeid(TTbsObj);
	TTbsObj* pObj = nullptr;
	if (&r1 == &r2)
	{
		pObj = dynamic_cast<TTbsObj*>(pModel);
	}
	return pObj;
}
template<typename T, typename F>
auto TObjMgr::execute(T* value, F func) -> decltype(func(value)) 
{
	return func(value);
}
#define I_ObjMgr TObjMgr::GetInstance()