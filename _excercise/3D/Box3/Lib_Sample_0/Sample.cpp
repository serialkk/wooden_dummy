#include "Sample.h"


D3DXVECTOR3            g_Eye;






bool	Sample::Init()
{
	g_Eye.x = 0.0f;
	g_Eye.y = 0.0f;
	g_Eye.z = -5.0f;

	

	return true;
}
bool	Sample::Render()
{
	HRESULT hr;


	
	//
	// Update variables
	//
	//ConstantBuffer cb;
	//D3DXMatrixTranspose(&cb.mWorld,&g_World);
	//D3DXMatrixTranspose(&cb.mView,&g_View);
	//D3DXMatrixTranspose(&cb.mProjection,&g_Projection);
	//g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	//
	// Renders a triangle
	//
	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);

	//
	g_pImmediateContext->DrawIndexed(36, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list

													   //
													   // Present our back buffer to our front buffer
													   //
	

	return true;
}
bool    Sample::Frame()
{
	HRESULT hr;

	//Clear constant buffer
	//단위행렬로 월드 행렬을 만듦.
	D3DXMatrixIdentity(&cb_game.mWorld);

	TCHAR buf[80];

	if (m_Input.KeyCheck('W') == KEY_HOLD){
		g_Eye.z += 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD){
		g_Eye.z -= 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('A') == KEY_HOLD) {
		g_Eye.x -= 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD) {
		g_Eye.x += 10.0f *m_Timer.m_fSecondPerFrame;

		_stprintf_s(buf, L"g_Eye.x: %5f, g_Eye.y:%5f, g_Eye.z:%5f\n", g_Eye.x, g_Eye.y, g_Eye.z);
		OutputDebugStringW(buf);
	}





	//D3DXVECTOR3 Eye = D3DXVECTOR3(0.0f, 0.0f, -5.0f); // 카메라의 위치
	//g_Eye.z = 10.00f;
	D3DXVECTOR3 Eye = g_Eye;
	D3DXVECTOR3 At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 카메라가 보는 
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&cb_game.mView, &Eye, &At, &Up);// 뷰 행렬 계산





													   // 투영 행렬 계산
													   // (D3DXMATRIX *pOut,  계산된 투영 행렬 반환
	FLOAT fovy = D3DX_PI * 0.5f;  // 시야각
	FLOAT Aspect = 800.0f / 600.0f;// 화면 비율( 1.33f )
	FLOAT zn = 0.1f; // 근단면 거리
	FLOAT zf = 1000.0f;   // 원단면 거리

	D3DXMatrixPerspectiveFovLH(&cb_game.mProjection, fovy, Aspect, zn, zf); // ==>> 투영 좌표


																	  // 전치 행렬 변환
																	  // Update variables
	D3DXMatrixTranspose(&cb.mWorld, &cb_game.mWorld);
	D3DXMatrixTranspose(&cb.mView, &cb_game.mView);
	D3DXMatrixTranspose(&cb.mProjection, &cb_game.mProjection);

	// Update constant buffer in every frame
	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	return true;
}
bool	Sample::Release()
{



	return true;
}

Sample::Sample()
{

}

Sample::~Sample()
{

}
TCORE_RUN(DxSample_1, 800, 600)
//TCORE_START;
//if (sample.SetWindow(hInstance,
//	L"SampleScene_0", 800, 600, WS_POPUPWINDOW))
//{
//	sample.Run();
//}
//TCORE_END;