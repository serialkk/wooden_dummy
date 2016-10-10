//--------------------------------------------------------------------------------------
// ���� ���� ����
//--------------------------------------------------------------------------------------
matrix			g_matWorld;
float4x4		g_matView;
float4x4		g_matProj;
//--------------------------------------------------------------------------------------
// ȯ��� (Cube Texture)
//--------------------------------------------------------------------------------------
TextureCube		g_txCubeMap; 

RasterizerState NoneCullSolid
{
    CullMode = NONE;
    FillMode = SOLID;
};
DepthStencilState AlwaysEnableDepth
{
    DepthEnable		= TRUE;
    DepthWriteMask	= ALL;
    DepthFunc		= Always;
};
SamplerState g_samCubeClamp
{
    Filter = ANISOTROPIC;
    AddressU = Clamp;
    AddressV = Clamp;
};
RasterizerState NoneCullWireFrame
{
    CullMode = NONE;
    FillMode = wireframe;
};


//-----------------------------------------------------------------------------
//���� �� �ȼ� ���̴� ����� ����
//-----------------------------------------------------------------------------
struct P3NCT_VERTEX
{
    float4 p			: POSITION; 
    float4 c			: COLOR0;
    float2 t			: TEXCOORD0;
};
struct P4T2_PS_INPUT
{
    float4 p			: SV_POSITION;  
    float3 v			: TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
P4T2_PS_INPUT OBJECT_VS( P3NCT_VERTEX input )
{
    P4T2_PS_INPUT output = (P4T2_PS_INPUT)0;
    float4 vWorldPos = mul( input.p,  g_matWorld );
    float4 vViewPos = mul( vWorldPos, g_matView );
    float4 vProjPos	= mul( vViewPos, g_matProj );
   
    // Set z = w so that z/w = 1 (i.e., skydome always on far plane). 
    output.p = vProjPos.xyww;
    output.v = input.p.xyz;
 
    return output;
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 OBJECT_PS( P4T2_PS_INPUT input) : SV_Target
{		
	return g_txCubeMap.Sample(g_samCubeClamp, input.v);
}

technique11 ObjectRender
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, OBJECT_VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, OBJECT_PS() ) );
        
        SetRasterizerState( NoneCullSolid );       
        // z���ۿ� 1���� �����Ѵ�.
        SetDepthStencilState( AlwaysEnableDepth, 0 );
    }
}
technique11 ObjectRenderWireFrame
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, OBJECT_VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, OBJECT_PS() ) );
        
        SetRasterizerState( NoneCullWireFrame );       
        // z���ۿ� 1���� �����Ѵ�.
        SetDepthStencilState( AlwaysEnableDepth, 0 );
    }
}
