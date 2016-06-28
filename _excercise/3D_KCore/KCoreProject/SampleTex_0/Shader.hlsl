cbuffer cb0
{
	// ��� ���� ��������(0��)
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
// float4  ������ ��ȯ�ؾ� �Ѵ�.
V_OUT VS(V_in vIn)
{
	V_OUT vOut;
	vOut.p = vIn.p;
	vOut.c = vIn.c;
	vOut.t = vIn.t;
	return vOut;
}


// �ؽ�ó ���� ��������(0��)
Texture2D g_txDiffuse : register(t0);
// ���÷� ���� ��������(0��)
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