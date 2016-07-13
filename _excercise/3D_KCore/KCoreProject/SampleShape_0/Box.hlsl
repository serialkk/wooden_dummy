cbuffer cb0
{
	float4 Color : packoffset(c0);
};
struct V_in
{
	float4 p : POSITION;
	float4 c0 : COLOR;
};
struct V_OUT
{
	float4 p : SV_POSITION;
	float4 c0 : COLOR0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
// float4  정점을 반환해야 한다.
V_OUT VS(V_in vIn)
{
	V_OUT vOut;
	vOut.p = vIn.p;
	vOut.c0 = vIn.c0;
	return vOut;
}

struct P_IN
{
	float4 p : SV_POSITION;
	float4 c0 : COLOR0;
};
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(P_IN vIn) : SV_Target
{
	return vIn.c0*Color;
}