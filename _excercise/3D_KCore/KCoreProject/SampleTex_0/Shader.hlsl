cbuffer cb0
{
	// 상수 저장 레지스터(0번)
	float4 Color : packoffset(c0);
};
struct V_in
{
	float4 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct V_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
// float4  정점을 반환해야 한다.
V_OUT VS(V_in vIn)
{
	V_OUT vOut;
	vOut.p = vIn.p;
	vOut.c = vIn.c;
	vOut.t = vIn.t;
	return vOut;
}


// 텍스처 저장 레지스터(0번)
Texture2D g_txDiffuse : register(t0);
// 샘플러 저장 레지스터(0번)
SamplerState samLinear : register(s0);

struct P_IN
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(P_IN vIn) : SV_Target
{
	float4 texColor = g_txDiffuse.Sample(samLinear,vIn.t);
	float4 FinalColor = texColor;// *vIn.c + Color;
	return FinalColor;
}