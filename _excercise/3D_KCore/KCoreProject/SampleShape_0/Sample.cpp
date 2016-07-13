#include "Sample.h"

bool	Sample::Init()
{
	for (int iObj = 0; iObj < MAX_CNT; iObj++)
	{
		D3DXMatrixIdentity(&m_matWorld[iObj]);
		SAFE_NEW(m_pPlane[iObj], TPlaneShape);
		if (!m_pPlane[iObj]->Create(g_pd3dDevice,
			L"Plane.hlsl",
			L"../../data/Back.bmp"))
		{
			return false;
		}
	}
		/*D3DXMatrixIdentity(&m_matWorld[1]);
		SAFE_NEW(m_pPlane[1], TPlaneShape);
		if (!m_pPlane[1]->Create(g_pd3dDevice,
			L"Plane.hlsl",
			L"../../data/Front.bmp"))
		{
			return false;
		}*/
	//}

	
	D3DXVECTOR3 m_vEye = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	D3DXVECTOR3 m_vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_matView, 
		&m_vEye, 
		&m_vAt, 
		&m_vUp);

	float m_fAspet = 800.0f / 600.0f;
	float m_fFov = D3DX_PI * 0.25f;
	float fNear = 1.0f;
	float fFar = 100.0f;
	D3DXMatrixPerspectiveFovLH(&m_matProj,
		m_fFov, m_fAspet, fNear, fFar);

	return true;
}
bool	Sample::Frame() {

	for (int iObj = 0; iObj < MAX_CNT; iObj++)
	{
		if (iObj % 2 == 0)
		{
			D3DXMatrixRotationX(&m_matWorld[iObj], m_Timer.m_fAccumulation);
			m_matWorld[iObj]._41 = iObj*0.1f;// +cosf(m_Timer.m_fAccumulation);
			m_matWorld[iObj]._42 = iObj*0.1f;
		}
		else
		{
			D3DXMatrixRotationY(&m_matWorld[iObj], m_Timer.m_fAccumulation);
			m_matWorld[iObj]._41 = -iObj*0.1f;// +cosf(m_Timer.m_fAccumulation);
			m_matWorld[iObj]._42 = -iObj*0.1f;
		}
		m_matWorld[iObj]._43 = 0;// cosf(m_Timer.m_fAccumulation);

		// m_pPlane[iObj]->m_Object.Frame();
	}
	return true;
}
bool	Sample::Render() {
	for (int iObj = 0; iObj < MAX_CNT; iObj++)
	{
		m_pPlane[iObj]->SetMatrix(
			&m_matWorld[iObj],
			&m_matView,
			&m_matProj);
		m_pPlane[iObj]->Render(g_pImmediateContext);
	}
	return true;
}
bool	Sample::Release() {
	//m_pPlane->Release();
	SAFE_DEL(m_pPlane[0]);
	SAFE_DEL(m_pPlane[1]);
	return true;
}

Sample::Sample()
{
	SAFE_ZERO(m_pPlane[0]);
	SAFE_ZERO(m_pPlane[1]);
	
}


Sample::~Sample()
{
}
KCORE_RUN(_T("Sample Lib"), 800, 600)