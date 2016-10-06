#include "TObject.h"
#include "TObjMgr.h"
bool TObject::Set(ID3D11Device* pd3dDevice, int iIndex)
{
	Init();
	TModel* const pModel = I_ObjMgr.GetPtr(iIndex);
	if (pModel == NULL) return false;
	m_cbData.Color = D3DXVECTOR4(1, 1, 1, 1);
	m_dxobj.g_pConstantBuffer.Attach(DX::CreateConstantBuffer(pd3dDevice, &m_cbData, 1, sizeof(VS_CONSTANT_BUFFER)));

	// 멀티 스레드로 처리되기 때문에 오브젝트 단위로 에미메이션 및 최종 행렬(인덱스)을 별도로 저장해 둔다. 
	shared_ptr<TObjWM> pWM = make_shared<TObjWM>(pModel->m_pMesh.size());
	for (DWORD dwObject = 0; dwObject < pModel->m_pMesh.size(); dwObject++)
	{
		pWM->m_iParent[dwObject] = -1;
		if (pModel->m_pMesh[dwObject]->m_pParent)
		{
			pWM->m_iParent[dwObject] = pModel->m_pMesh[dwObject]->m_pParent->m_iIndex;
		}
	}
	pWM->m_pModel = pModel;
	pWM->m_Scene = pModel->m_Scene;
	m_pModelList.push_back(pWM);
	return true;
}
void TObject::Add(ID3D11Device* pDevice, shared_ptr<TObject> pObj)
{
	m_pSubObjList.push_back(pObj);
}
void TObject::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	TModel::SetMatrix(pWorld, pView, pProj);
	for (int iModel = 0; iModel < m_pModelList.size(); iModel++)
	{
		m_pModelList[iModel]->m_pModel->SetMatrix(pWorld, pView, pProj);
	}
	//for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	//{
	//	m_pSubObjList[iObj]->SetMatrix(pWorld, pView, pProj);		
	//}
}

bool TObject::Init()
{
	return true;
}
bool TObject::Load(ID3D11Device* pd3dDevice,
	const TCHAR* strFileName,
	const TCHAR* strShaderName, bool bThread)
{
	int iIndex = I_ObjMgr.Load(pd3dDevice, strFileName, strShaderName, bThread);
	if (iIndex < 0)
	{
		I_ObjMgr.Delete(iIndex);
		return -1;
	}
	return Set(pd3dDevice, iIndex);
}
bool TObject::ObjectFrame()
{
	for (int iModel = 0; iModel < m_pModelList.size(); iModel++)
	{
		TObjWM* pUnit = m_pModelList[iModel].get();
		pUnit->m_fElapseTime += g_fSecPerFrame * pUnit->m_Scene.iFrameSpeed * pUnit->m_Scene.iTickPerFrame;
		if (pUnit->m_fElapseTime >= pUnit->m_Scene.iLastFrame* pUnit->m_Scene.iTickPerFrame)
		{
			pUnit->m_fElapseTime = pUnit->m_Scene.iFirstFrame * pUnit->m_Scene.iTickPerFrame;
		}

		for (int iMesh = 0; iMesh < pUnit->m_Scene.iNumMesh; iMesh++)
		{
			D3DXMatrixIdentity(&pUnit->m_matAnim[iMesh]);
			D3DXMatrixIdentity(&pUnit->m_matCalculation[iMesh]);
			int iParent = pUnit->m_iParent[iMesh];
			D3DXMATRIX mat;
			if (iParent >= 0)
			{
				pUnit->m_matAnim[iMesh] = m_Animation.Update(pUnit->m_fElapseTime,
					pUnit->m_pModel->m_pMesh[iMesh].get(),
					pUnit->m_matAnim[iParent],
					pUnit->m_Scene);
			}
			else
			{
				pUnit->m_matAnim[iMesh] = m_Animation.Update(pUnit->m_fElapseTime,
					pUnit->m_pModel->m_pMesh[iMesh].get(),
					mat,
					pUnit->m_Scene);
			}
			D3DXMatrixMultiply(&pUnit->m_matCalculation[iMesh], &pUnit->m_matAnim[iMesh], &m_matWorld);
		}
	}	
	return true;
}
bool TObject::ObjectRender(ID3D11DeviceContext*    pContext, bool bCommand)
{	
	for (int iModel = 0; iModel < m_pModelList.size(); iModel++)
	{
		TObjWM* pUnit = m_pModelList[iModel].get();
		PreDraw(pContext, pUnit, bCommand);
		PostDraw(pContext, pUnit, bCommand);
	}
	return true;
}
bool TObject::PreDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand)
{
	pUnit->m_pModel->PreRender(pContext);
	return true;
}
bool TObject::PostDraw(ID3D11DeviceContext*    pContext, TObjWM* pUnit, bool bCommand)
{
	Draw(pContext, pUnit, bCommand);
	return true;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void TObject::SetConstantBuffers(ID3D11DeviceContext* pContext, TObjWM* pUint, int iMesh)
{
	//D3DXMatrixMultiply(&m_pObjWM->m_matCalculation[iMesh], &m_pObjWM->m_matAnim[iMesh], &m_matWorld);
	if (m_bDefferedMultiThread)
	{
		//D3DXMatrixMultiply(&m_pObjWM->m_matCalculation[iMesh], &m_pObjWM->m_matAnim[iMesh], &m_matWorld);
		// m_pModel은 공용 메쉬의 상수버퍼이기 때문에 동일한 오브젝트를 사용할 경우 멀티쓰래드에서 문제가 생긴다.
		// 그렇기 때문에 오브젝트 단위의 상수버퍼를 사용한다.		
		SetMatrix(&pUint->m_matCalculation[iMesh], &m_matView, &m_matProj);
		pContext->UpdateSubresource(m_dxobj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		pContext->VSSetConstantBuffers(0, 1, m_dxobj.g_pConstantBuffer.GetAddressOf());
	}
	else
	{
		D3DXMatrixMultiply(&pUint->m_matCalculation[iMesh], &pUint->m_matAnim[iMesh], &m_matWorld);
		pUint->m_pModel->SetMatrix(&pUint->m_matCalculation[iMesh], &m_matView, &m_matProj);
		UpdateConstantBuffer(pContext, pUint->m_pModel);
	}
}
bool TObject::Draw(ID3D11DeviceContext* pContext, TObjWM* pUint, bool bCommand)
{
	//CStopwatch stopwatch;	
	TModel* pModel = pUint->m_pModel;
	for (DWORD iMesh = 0; iMesh < pModel->m_pMesh.size(); iMesh++)
	{
		auto pMesh = pModel->m_pMesh[iMesh].get();	
		if (bCommand == false)
		{
			SetConstantBuffers(pContext, pUint, iMesh);
		}
		//D3DXMatrixMultiply(&m_pObjWM->m_matCalculation[iMesh], &m_pObjWM->m_matAnim[iMesh], &m_matWorld);
	/*	SetMatrix(&m_pObjWM->m_matCalculation[iMesh], &m_matView, &m_matProj);
		pContext->UpdateSubresource(m_dxobj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		pContext->VSSetConstantBuffers(0, 1, m_dxobj.g_pConstantBuffer.GetAddressOf());	*/	

		if (pMesh->m_pSubMesh.size() > 0)
		{
			for (DWORD dwSub = 0; dwSub < pMesh->m_pSubMesh.size(); dwSub++)
			{
				auto pSubMesh = pMesh->m_pSubMesh[dwSub].get();
				if (pSubMesh->m_iNumFace < 1) continue;
				pContext->PSSetShaderResources(0, 1, pSubMesh->m_dxobj.g_pTextureSRV.GetAddressOf());
				pContext->DrawIndexed(pSubMesh->m_dxobj.m_iNumIndex,
					pSubMesh->m_dxobj.m_iBeginIB,
					pSubMesh->m_dxobj.m_iBeginVB);
				if (bCommand) 	SetCommmandList(pContext, pSubMesh, true);
			}
		}
		else
		{
			if (pMesh->m_iNumFace < 1) continue;
			pContext->PSSetShaderResources(0, 1, pMesh->m_dxobj.g_pTextureSRV.GetAddressOf());
			pContext->DrawIndexed(pMesh->m_dxobj.m_iNumIndex,
				pMesh->m_dxobj.m_iBeginIB,
				pMesh->m_dxobj.m_iBeginVB);
			if (bCommand) 	SetCommmandList(pContext, pMesh, true);
		}
	}
	//stopwatch.Output(L"\nTTbsObj::Draw");
	return true;
}
//
//bool TObject::DrawGroup(ID3D11DeviceContext* pContext, TModel* pObj, int iObject,  bool bCommand)
//{
//	/*if (pObj->m_pMesh[iObject]->m_pSubMesh.size() > 0)
//	{
//		for (DWORD dwSubCount = 0; dwSubCount < pObj->m_pMesh[iObject]->m_pSubMesh.size(); dwSubCount++)
//		{
//			TMesh* pSubMesh = (TMesh*)pObj->m_pMesh[iObject]->m_pSubMesh[dwSubCount];
//			if (DrawMesh(pContext, pObj, pSubMesh, pApply))
//			{
//				if (bCommand) 	SetCommmandList(pContext, pSubMesh, true);
//			}
//		}
//	}
//	else
//	{
//		if (DrawMesh(pContext, pObj, pObj->m_pMesh[iObject], pApply))
//		{
//			if (bCommand) 	SetCommmandList(pContext, pObj->m_pMesh[iObject], true);
//		}
//	}*/
//	return true;
//}
bool TObject::Frame()
{
	ObjectFrame();
	//for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	//{
	//	m_pSubObjList[iObj]->ObjectFrame();
	//}	
	return true;
}
bool TObject::Render(ID3D11DeviceContext*    pContext)
{
	ObjectRender(pContext);
	/*for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	{
		m_pSubObjList[iObj]->ObjectRender( pContext);
	}*/
	return true;
}
bool TObject::Release()
{
	m_pSubObjList.clear();
	return true;
}
bool TObject::ResetResource()
{
	return true;
}
void TObject::SetActionFrame(TCHAR* pStrModel, DWORD dwStrat, DWORD dwEnd)
{	
	m_iStartFrame = dwStrat;
	m_iLastFrame = dwEnd;
	m_fElapseTime = (float)dwStrat;
	for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	{
		m_pSubObjList[iObj]->m_iStartFrame = dwStrat;
		m_pSubObjList[iObj]->m_iLastFrame = dwEnd;
		m_pSubObjList[iObj]->m_fElapseTime = (float)dwStrat;		
	}	
}
//////////////////////////////////////////////////////////////////////////
// 명령목록 생성
//////////////////////////////////////////////////////////////////////////
bool TObject::SetCommandRender(ID3D11DeviceContext* pContext)
{
	ObjectRender(pContext, true);
	/*for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	{
		m_pSubObjList[iObj]->ObjectRender(pContext, true);
	}*/
	return true;
}
//////////////////////////////////////////////////////////////////////////
// 명령목록 실행
//////////////////////////////////////////////////////////////////////////
bool TObject::CommandRender(ID3D11DeviceContext* pContext)
{
	for (int iModel = 0; iModel < m_pModelList.size(); iModel++)
	{
		TObjWM* pUnit = m_pModelList[iModel].get();
		CommandDraw(pContext, pUnit);
	}
	
	/*for (int iObj = 0; iObj < m_pSubObjList.size(); iObj++)
	{
		TObject* pObj = m_pSubObjList[iObj].get();
		_ASSERT(pObj);
		pObj->CommandRender(pContext);
	}*/
	return true;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
bool TObject::CommandDraw(ID3D11DeviceContext* pContext, TObjWM* pUnit)
{
	HRESULT hr;
	TModel* pModel = pUnit->m_pModel;
	for (DWORD iMesh = 0; iMesh < pModel->m_pMesh.size(); iMesh++)
	{
		SetConstantBuffers(pContext, pUnit, iMesh);

		if (pModel->m_pMesh[iMesh]->m_pSubMesh.size() > 0)
		{
			for (DWORD dwSubCount = 0; dwSubCount < pModel->m_pMesh[iMesh]->m_pSubMesh.size(); dwSubCount++)
			{
				TMesh* pSubMesh = (TMesh*)pModel->m_pMesh[iMesh]->m_pSubMesh[dwSubCount].get();
				if (pSubMesh->m_iNumFace <= 0) continue;
				ExecuteCommandList(pContext, pSubMesh, false);
			}
		}
		else
		{
			if (pModel->m_pMesh[iMesh]->m_iNumFace <= 0) continue;
			ExecuteCommandList(pContext, pModel->m_pMesh[iMesh].get(), false);
		}
	}

	return true;
}
HRESULT TObject::SetCommmandList(ID3D11DeviceContext* pContext, TMesh* pSubMesh, bool bSave)
{
	HRESULT hr = S_OK;
	if (pContext)
	{
		return pContext->FinishCommandList(bSave, &pSubMesh->m_pd3dCommandList);
	}
	return E_FAIL;
}
void TObject::ExecuteCommandList(ID3D11DeviceContext* pContext, TMesh* pMesh, bool bClear)
{
	assert(pMesh && pMesh->m_pd3dCommandList!=nullptr);
	pContext->ExecuteCommandList(pMesh->m_pd3dCommandList.Get(), !bClear);

	if (bClear)
	{
		pMesh->m_pd3dCommandList.ReleaseAndGetAddressOf();
	}
}
TObject::TObject(void)
{
	m_fElapseTime = 0.0f;
	m_bDefferedMultiThread = false;
}
TObject::TObject(int iIndex)
{
	m_fElapseTime = 0.0f;
	m_bDefferedMultiThread = false;
}
TObject::TObject(TObject &obj)
{
	m_fElapseTime = 0.0f;
	m_bDefferedMultiThread = obj.m_bDefferedMultiThread;
}
TObject::~TObject(void)
{
}