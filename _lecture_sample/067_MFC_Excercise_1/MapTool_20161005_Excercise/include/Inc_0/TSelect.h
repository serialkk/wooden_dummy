#pragma once
#include "TShape.h"

struct T_RAY
{
	float			fExtent;
	D3DXVECTOR3		vOrigin;
	D3DXVECTOR3		vDirection;
};

class TSelect
{
public:
	T_RAY		m_Ray;
	D3DXVECTOR3 m_vIntersection;
	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_matView;
	D3DXMATRIX  m_matProj;
	D3DXVECTOR3 m_vDxR;
	D3DXVECTOR3 m_vCenter;
public:
	D3DXVECTOR3		m_vSrcVex[3];
	float			m_fPickDistance;
	D3DXMATRIX		m_matWorldPick;
	D3DXVECTOR3 qvec;
	D3DXVECTOR3 tvec;
	D3DXVECTOR3 pvec;
public:
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	void Update();
	bool IntersectRayToSphere(T_SPHERE* pSphere, T_RAY* pRay = NULL);

	bool ChkOBBToRay(T_BOX* pBox, T_RAY* pRay = NULL);
	bool IntersectBox(T_BOX* pBox, T_RAY* pRay = NULL);

	bool AABBtoRay(T_BOX* a, T_RAY* pRay = NULL);
	bool OBBtoRay(T_BOX* a, T_RAY* pRay = NULL);
	D3DXVECTOR3 GetIntersection();

	// 교점을 찾는다.
	bool    GetIntersection(
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd,
		D3DXVECTOR3 vNormal,
		D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);
	// 폴리곤안에 위치하는지 판단한다.
	bool    PointInPolygon(
		D3DXVECTOR3 vert,
		D3DXVECTOR3 faceNormal,
		D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);
	bool	ChkPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2);
	bool	IntersectTriangle(const D3DXVECTOR3& orig, const D3DXVECTOR3& dir,
		D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2,
		FLOAT* t, FLOAT* u, FLOAT* v);

public:
	TSelect(void);
	virtual ~TSelect(void);
};

