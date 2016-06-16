//Vertex Shader
// ��ȯ��, �������̴� �Լ���, �ø�ƽ(�ṉ̀���)
// �������̴�-> �������ۿ� ����ִ� ��� ������ 1ȸ ȣ��ȴ�.
// �ݵ�� ó���ؾ��ϴ� ��Ȱ�� 
// float4�� ������ ��ġ(SV_POSITION)�� ��ȯ�ؾ� �Ѵ�.
// �ø�ƽ
// ��� �������� c0 ~ 65553
// c0 = x,y,z,w
//      r,g,b,a
cbuffer cb0
{
	float4 Color : packoffset(c0);	// c0
	float  time  : packoffset(c1.x);    // c1
};

struct VS_INPUT
{
	float3 p : POSITION;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION; // ���� ��ġ �������� ���
	float4 c : COLOR0;      // ���� �÷� �������� ���
	float1 t : TEXCOORD0;   // ���� �ؽ��� ��ǥ �������� ���
};
float4 VS( in float3 p : POSITION ) : SV_POSITION
{
	return float4( p.x, p.y, p.z, 1.0f);
}
VS_OUTPUT VS2(in float3 p : POSITION) 
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	//output.p = float4(p.x, p.y, p.z, 1.0f);
	output.p = float4(p, 1.0f);
	return output;
}
VS_OUTPUT VS3( VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 pos = float4(input.p, 1.0f);
	output.p.x = pos.x;
	output.p.y = pos.y;
	output.p.z = pos.z;
	output.p.w = 1.0f;
	output.t = time*0.5f + 0.5f;
	output.c = float4(Color.x, Color.y, Color.z, Color.w);
	return output;
}