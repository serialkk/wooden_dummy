#pragma once
#pragma warning( disable:4005)
#include <assert.h>
#include <d3d11.h>
#include <d3dx11.h> 

class TViewDS
{
public:
    ID3D11Texture2D*				m_pTexture;
    ID3D11DepthStencilView*			m_pDSV;
    ID3D11ShaderResourceView*		m_pSRV;

    TViewDS( ID3D11Device* pd3dDevice, D3D11_TEXTURE2D_DESC* pTexDesc );
    ~TViewDS();
};

////--------------------------------------------------------------------------------------
//void CreateShadowMap( ID3D11Device* pd3dDevice )
//{
//    D3D11_TEXTURE2D_DESC texDesc;
//    texDesc.ArraySize          = 1;
//    texDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
//    texDesc.CPUAccessFlags     = NULL;
//    texDesc.Format             = DXGI_FORMAT_R32_TYPELESS;
//    texDesc.Width              = LIGHT_RES;
//    texDesc.Height             = LIGHT_RES;
//    texDesc.MipLevels          = 1;
//    texDesc.MiscFlags          = NULL;
//    texDesc.SampleDesc.Count   = 1;
//    texDesc.SampleDesc.Quality = 0;
//    texDesc.Usage              = D3D11_USAGE_DEFAULT;
//
//    SAFE_DEL(g_pShadowMapSimpleDS);
//    g_pShadowMapSimpleDS = new SimpleDS( pd3dDevice, &texDesc );
//
//    texDesc.Width              = SCREEN_WIDTH;
//    texDesc.Height             = SCREEN_HEIGHT;
//
//    SAFE_DEL(g_SSShMapSimpleDS);
//    g_SSShMapSimpleDS = new SimpleDS( pd3dDevice, &texDesc );
//}
//
////--------------------------------------------------------------------------------------
//void DeleteShadowMap()
//{
//    SAFE_DEL(g_pShadowMapSimpleDS);
//    SAFE_DEL(g_pShadowMapResolvedDS);
//    SAFE_DEL(g_SSShMapSimpleDS);
//}
//
////--------------------------------------------------------------------------------------
//void CreateSSShadowMap( ID3D11Device* pd3dDevice )
//{
//    D3D11_TEXTURE2D_DESC texDesc;
//    texDesc.ArraySize          = 1;
//    texDesc.BindFlags          = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
//    texDesc.CPUAccessFlags     = NULL;
//    texDesc.Format             = DXGI_FORMAT_R32_FLOAT;
//    texDesc.Width              = SCREEN_WIDTH;
//    texDesc.Height             = SCREEN_HEIGHT;
//    texDesc.MipLevels          = 1;
//    texDesc.MiscFlags          = NULL;
//    texDesc.SampleDesc.Count   = 1;
//    texDesc.SampleDesc.Quality = 0;
//    texDesc.Usage              = D3D11_USAGE_DEFAULT;
//
//    SAFE_DEL(g_SSShadowRT);
//    g_SSShadowRT = new SimpleRT( pd3dDevice, &texDesc );
//
//    SAFE_DEL(g_SSShResolveRT);
//    g_SSShResolveRT = new SimpleRT( pd3dDevice, &texDesc );	
//}
//
////--------------------------------------------------------------------------------------
//void DeleteSSShadowMap()
//{
//    SAFE_DEL(g_SSShadowRT);
//    SAFE_DEL(g_SSShResolveRT);
//}

//void CALLBACK OnD3D10FrameRender( ID3D11Device* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
//{
//    if (g_Reload)
//    {
//        g_Reload = false;
//        LoadEffect( pd3dDevice );
//    }
//
//    // If the settings dialog is being shown, then render it instead of rendering the app's scene
//    if( g_SettingsDlg.IsActive() )
//    {
//        g_SettingsDlg.OnRender( fElapsedTime );
//        return;
//    }
//
//    //
//    // STEP 1: render shadow map from the light's point of view
//    //
//
//    pd3dDevice->ClearDepthStencilView( g_pShadowMapSimpleDS->pDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );
//    m_pImmediateContext->RSSetViewports(1, &g_LViewport);
//
//    // Set SRV to NULL to avoid runtime warning in OMSetRenderTargets
//    g_pDepthMapVariable->SetResource( NULL );
//    g_pSSShMapVariable->SetResource( NULL );
//    //g_pTech->GetPassByName( "ZEqualPCF" )->Apply( 0,m_pImmediateContext);
//
//    g_pTech->GetPassByName( "ShadowMapPass" )->Apply( 0,m_pImmediateContext);
//    m_pImmediateContext->OMSetRenderTargets( 0, NULL, g_pShadowMapSimpleDS->pDSV );
//
//    DrawMesh(pd3dDevice, g_Mesh1, g_pVertexLayout);
//    DrawMesh(pd3dDevice, g_Mesh2, g_pVertexLayout);
//
//    g_pDepthMapVariable->SetResource( g_pShadowMapSimpleDS->pSRV );
//
//    //
//    // STEP 2: render scene from the eye's point of view
//    //
//
//    ID3D11RenderTargetView* pBB_RT = DXUTGetD3D10RenderTargetView();
//    ID3D11DepthStencilView* pBB_DS = DXUTGetD3D10DepthStencilView();
//
//    m_pImmediateContext->ClearRenderTargetView( pBB_RT, g_BackgroundColor_Black );
//    pd3dDevice->ClearDepthStencilView( pBB_DS, D3D11_CLEAR_DEPTH, 1.0, 0 );
//
//    m_pImmediateContext->OMSetRenderTargets( 1, &pBB_RT, pBB_DS );
//    m_pImmediateContext->RSSetViewports(1, &g_Viewport); 
//
//    if (g_DisplayTex)
//    {
//        g_pTech->GetPassByName( "VisTex" )->Apply( 0,m_pImmediateContext);
//        pd3dDevice->Draw( 3, 0 );
//    }
//	else if (g_UseSSPCSS)
//	{
//		ID3D11RenderTargetView* aRTViews[ 1 ] = { g_SSShadowRT->pRTV };
//
//		float g_BackgroundColor_Red[4] = { 0.9f, 0.9f, 0.1f, 0.0f };
//		m_pImmediateContext->ClearRenderTargetView( g_SSShadowRT->pRTV, g_BackgroundColor_Red);
//		pd3dDevice->ClearDepthStencilView( g_SSShMapSimpleDS->pDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );
//
//		// To reduce overdraw, do a depth prepass to layout z, followed by a shading pass
//        DrawSceneGeometry( pd3dDevice, g_pVertexLayout, g_pTech->GetPassByName( "ZPrepass" ) );
//		DrawSceneGeometry( pd3dDevice, g_pVertexLayout, g_pTech->GetPassByName( "SSHSPass" ) );
//
//		m_pImmediateContext->OMSetRenderTargets( 1, aRTViews, g_SSShMapSimpleDS->pDSV );
//		
//		//pd3dDevice->ResolveSubresource((ID3D11Resource*)g_SSShResolveRT->pTexture, D3D10CalcSubresource( 0, 0, 1 ), (ID3D11Resource*)g_SSShadowRT->pTexture, D3D10CalcSubresource( 0, 0, 1 ), DXGI_FORMAT_R8_UNORM);
//		
//		g_pSSShMapVariable->SetResource( g_SSShadowRT->pSRV );
//
//		m_pImmediateContext->OMSetRenderTargets( 1, &pBB_RT, pBB_DS );
//
//		if (g_DisplaySSSHMap)
//		{
//			g_pTech->GetPassByName( "VisSSHS" )->Apply( 0,m_pImmediateContext);
//			pd3dDevice->Draw( 3, 0 );
//		}
//	}
//    else if (!g_UseSSPCSS)
//    {
//        // To reduce overdraw, do a depth prepass to layout z, followed by a shading pass
//        DrawSceneGeometry( pd3dDevice, g_pVertexLayout, g_pTech->GetPassByName( "ZPrepass" ) );
//        DrawSceneGeometry( pd3dDevice, g_pVertexLayout, g_pTech->GetPassByName( g_UsePCSS ? "ZEqualPCSS" : "ZEqualPCF") );
//    }
//
//    if (g_DrawUI)
//    {
//        DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
//        RenderText();
//        g_HUD.OnRender( fElapsedTime ); 
//        DXUT_EndPerfEvent();
//    }
//}

