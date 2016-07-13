Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);
cbuffer cb0
{
	float4x4	g_matWorld		: packoffset(c0);
	float4x4	g_matView		: packoffset(c4);
	float4x4	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
// float4  정점을 반환해야 한다.
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output;
	output.p = mul(vIn.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.t = vIn.t;
	output.c = vIn.c;// *g_MeshColor;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(samLinear, vIn.t) *vIn.c;
}