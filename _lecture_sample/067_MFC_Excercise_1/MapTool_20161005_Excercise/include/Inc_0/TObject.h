#pragma once
#include "TObjMgr.h"
#include "TAnimation.h"

class TObject : public TModel
{
public:	
	vector<shared_ptr<TObjWM>>			m_pModelList;
	vector<shared_ptr<TObject>>			m_pSubObjList;	
	bool			m_bDefferedMultiThread;
	TAnimation		m_Animation;
public:
	void		Add(ID3D11Device* pDevice, shared_ptr<TObject> pObj);
	bool		Init();
	bool		Load(ID3D11Device* pd3dDevice,	const TCHAR* strFileName,	const TCHAR* strShaderName,	bool bThread = false);
	bool		Frame();
	bool		Render(ID3D11DeviceContext*    pContext);
	bool		Draw(ID3D11DeviceContext* pContext, TObjWM* pUint, bool bCommand);
	virtual bool		PreDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand);
	virtual bool		PostDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand);
	bool		Release();
	bool		ResetResource();	
	void		SetActionFrame(TCHAR* pStrModel, DWORD dwStrat, DWORD dwEnd);
	void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	// 1개의 메쉬를 다수의 오브젝트가 사용할 경우에 사용된다.
	bool		ObjectFrame();
	bool		ObjectRender(ID3D11DeviceContext*    pContext, bool bCommand=false);
	bool		Set(ID3D11Device* pd3dDevice, int iIndex);
	void		SetConstantBuffers(ID3D11DeviceContext* pContext, TObjWM* pUint, int iMesh);
	bool		SetCommandRender(ID3D11DeviceContext* pContext);
	bool		CommandRender(ID3D11DeviceContext* pContext);
	bool		CommandDraw(ID3D11DeviceContext* pContext, TObjWM* pUnit);
	virtual HRESULT	SetCommmandList(ID3D11DeviceContext* pContext, TMesh* pSubMesh, bool bSave = false);
	virtual void	ExecuteCommandList(ID3D11DeviceContext* pContext, TMesh* pSubMesh, bool bClear = true);
public:
	TObject(void);
	TObject(int iIndex);
	explicit TObject(std::shared_ptr<TObject> myStuff)
	{
		m_pSubObjList.push_back(move(myStuff));
	}
	explicit TObject(TObject* const myStuff)
	{
		shared_ptr<TObject> pObj(myStuff);
		m_pSubObjList.push_back(move(pObj));
	}
	TObject(TObject &obj);
	virtual ~TObject(void);
};
