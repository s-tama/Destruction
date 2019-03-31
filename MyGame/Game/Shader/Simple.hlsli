//
// Simple.hlsli
//


// 頂点シェーダに渡すデータ
struct VS_INPUT
{
	float4 pos		: POSITION;
	float4 normal	: NORMAL;
};

// ピクセルシェーダに渡すデータ
struct PS_INPUT
{
	float4 pos		: SV_POSITION;
	float3 normal	: NORMAL;
	float3 lightDir	: TEXCOORD0;
	float3 viewDir	: TEXCOORD1;
};
