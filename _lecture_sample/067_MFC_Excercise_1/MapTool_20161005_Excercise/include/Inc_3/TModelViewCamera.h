#pragma once
#include "TCamera.h"

class TModelViewCamera : public TCamera
{
public:		
	//--------------------------------------------------------------------------------------
	// 카메라 위치 정보 
	//--------------------------------------------------------------------------------------
	void				MoveLook( float fValue );
	void				MoveSide( float fValue );	
	void				MoveUp( float fValue );	
	//--------------------------------------------------------------------------------------
	// 오일러 각에 따른 뷰 행렬 계산 
	//--------------------------------------------------------------------------------------
	D3DXMATRIX			Update( float fElapseTime );

	// 모델의 월드 변환 행렬의 방향벡터
	D3DXVECTOR3			m_vObjectVector[3];

public:

	//--------------------------------------------------------------------------------------
	// 뷰 행렬 계산  
	//--------------------------------------------------------------------------------------
	D3DXMATRIX			SetViewMatrix( D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));	

public:
	TModelViewCamera(void);
	virtual ~TModelViewCamera(void);
};
