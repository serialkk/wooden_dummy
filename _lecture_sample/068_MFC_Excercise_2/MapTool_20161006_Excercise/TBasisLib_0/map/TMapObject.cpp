#include "TMapObject.h"

void TMapObject::SetPosition( D3DXVECTOR3 vPos )
{
	m_vPosition = vPos;
}
void TMapObject::Update()
{
	// g_matWorld Matrix = S * R * T
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;	

	m_tBox.vCenter = m_vPosition;

	m_tBox.vMax	= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	m_tBox.vMin	= D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
	// AABB
	D3DXVECTOR3 vVertex[8];
	vVertex[0] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMin.z );
	vVertex[1] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMin.z );
	vVertex[2] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMin.z );
	vVertex[3] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMin.z );

	vVertex[4] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMax.z );
	vVertex[5] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMax.z );
	vVertex[6] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMax.z );
	vVertex[7] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMax.z );

	D3DXVECTOR3 vMax, vMin;
	vMin = D3DXVECTOR3( 100000.0f, 100000.0f, 100000.0f );
	vMax = D3DXVECTOR3( -100000.0f, -100000.0f, -100000.0f );
	for( int iVer=0; iVer < 8; iVer++ )
	{
		D3DXVec3TransformCoord( &vVertex[iVer], &vVertex[iVer], &m_matWorld );	
		if( vVertex[iVer].x > vMax.x ) vMax.x = vVertex[iVer].x;
		if( vVertex[iVer].y > vMax.y ) vMax.y = vVertex[iVer].y;
		if( vVertex[iVer].z > vMax.z ) vMax.z = vVertex[iVer].z;

		if( vVertex[iVer].x < vMin.x ) vMin.x = vVertex[iVer].x;
		if( vVertex[iVer].y < vMin.y ) vMin.y = vVertex[iVer].y;
		if( vVertex[iVer].z < vMin.z ) vMin.z = vVertex[iVer].z;
	}

	m_tBox.vMin = vMin;
	m_tBox.vMax = vMax;
	m_tBox.fRadius[0] = m_tBox.vMax.x - m_tBox.vCenter.x;
	m_tBox.fRadius[1] = m_tBox.vMax.y - m_tBox.vCenter.y;
	m_tBox.fRadius[2] = m_tBox.vMax.z - m_tBox.vCenter.z;
}

TMapObject::TMapObject()
{
	m_tBox.vCenter	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_tBox.vMax		= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	m_tBox.vMin		= D3DXVECTOR3( -1.0f, -1.0f, -1.0f );

	DWORD dwAreaLange = ( pow(2.0f,7.0f)+1) * 2.0f * 10.0f ;
	m_vPosition		= D3DXVECTOR3( dwAreaLange*0.5f - (rand()%dwAreaLange), dwAreaLange*0.5f - (rand()%dwAreaLange),  (dwAreaLange*0.5f - rand()%dwAreaLange));
	m_vColor		= D3DXVECTOR4(	( rand()%256 ) / 255.0f, ( rand()%256 ) / 255.0f, ( rand()%256 ) / 255.0f, 1.0f );

	// g_matWorld Matrix = S * R
	D3DXMATRIX matScale, matRotation, matWorld;
	D3DXMatrixScaling( &matScale, 	( rand()%256 ) / 255.0f * 10.0f, ( rand()%256 ) / 255.0f * 5.0f, ( rand()%256 ) / 255.0f * 10.0f  );  
	D3DXMatrixRotationYawPitchRoll( &matRotation, ( rand()%256 ) / 255.0f, ( rand()%256 ) / 255.0f, ( rand()%256 ) / 255.0f  );  
	D3DXMatrixMultiply( &m_matWorld, &matScale, &matRotation );
			
	// OBB 기저벡터 변환( 회전 변환 이후 정규화 )
	m_tBox.vCenter = m_vPosition;
	D3DXVECTOR3 vMax, vMin, vHalf ;
	D3DXVec3TransformCoord( &m_tBox.vAxis[0], &D3DXVECTOR3( 1.0f,0.0f, 0.0f ), &m_matWorld );
	D3DXVec3TransformCoord( &m_tBox.vAxis[1], &D3DXVECTOR3( 0.0f,1.0f, 0.0f ), &m_matWorld );
	D3DXVec3TransformCoord( &m_tBox.vAxis[2], &D3DXVECTOR3( 0.0f,0.0f, 1.0f ), &m_matWorld );
	D3DXVec3Normalize( &m_tBox.vAxis[0], &m_tBox.vAxis[0] );
	D3DXVec3Normalize( &m_tBox.vAxis[1], &m_tBox.vAxis[1] );
	D3DXVec3Normalize( &m_tBox.vAxis[2], &m_tBox.vAxis[2] );

	// g_matWorld Matrix = S * R * T
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;		

	// OBB 기저벡터의 크기 계산
	D3DXVec3TransformCoord( &vMax, &m_tBox.vMax, &m_matWorld );
	D3DXVec3TransformCoord( &vMin, &m_tBox.vMin, &m_matWorld );
	vHalf  = vMax-m_tBox.vCenter;
	m_tBox.fExtent[0] = D3DXVec3Dot( &m_tBox.vAxis[0], &vHalf );
	m_tBox.fExtent[1] = D3DXVec3Dot( &m_tBox.vAxis[1], &vHalf );
	m_tBox.fExtent[2] = D3DXVec3Dot( &m_tBox.vAxis[2], &vHalf );

	// AABB
	D3DXVECTOR3 vVertex[8];
	vVertex[0] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMin.z );
	vVertex[1] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMin.z );
	vVertex[2] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMin.z );
	vVertex[3] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMin.z );

	vVertex[4] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMax.z );
	vVertex[5] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMax.z );
	vVertex[6] = D3DXVECTOR3( m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMax.z );
	vVertex[7] = D3DXVECTOR3( m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMax.z );

	vMin = D3DXVECTOR3( 100000.0f, 100000.0f, 100000.0f );
	vMax = D3DXVECTOR3( -100000.0f, -100000.0f, -100000.0f );
	for( int iVer=0; iVer < 8; iVer++ )
	{
		D3DXVec3TransformCoord( &vVertex[iVer], &vVertex[iVer], &m_matWorld );	
		if( vVertex[iVer].x > vMax.x ) vMax.x = vVertex[iVer].x;
		if( vVertex[iVer].y > vMax.y ) vMax.y = vVertex[iVer].y;
		if( vVertex[iVer].z > vMax.z ) vMax.z = vVertex[iVer].z;

		if( vVertex[iVer].x < vMin.x ) vMin.x = vVertex[iVer].x;
		if( vVertex[iVer].y < vMin.y ) vMin.y = vVertex[iVer].y;
		if( vVertex[iVer].z < vMin.z ) vMin.z = vVertex[iVer].z;
	}

	m_tBox.vMin = vMin;
	m_tBox.vMax = vMax;
}
TMapObject::~TMapObject()
{
}

