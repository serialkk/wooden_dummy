#pragma once
#include "TTemplate.h"
#include "TModel.h"

///////////////////////////////////////////////////////////////////////////////
// TBAsisModel�� �Ļ��� ���ϵ��� �ε�Ǿ� TModel�� ��ȯ�Ǿ� ���� �� ��ȯ�ȴ�.
///////////////////////////////////////////////////////////////////////////////
class TModelMgr: public TTemplateMap< TModel >, public TSingleton<TModelMgr> 
{
private:
	friend class TSingleton<TModelMgr>;
	TModel*		m_pModelObj;
public:			
	int			Load( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, const TCHAR* strFileName, TModel* pModel );
	FILETYPE	GetFileTypeID( ID3D11Device* pd3dDevice, const TCHAR* pszFileName , TModel* pModel = 0);		
private:
	TModelMgr(void);
	virtual ~TModelMgr(void);
};
#define I_ModelMgr TModelMgr::GetInstance()