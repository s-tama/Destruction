//
// SimplePS.hlsl
//

#include "MyShader.hlsli"
#include "Simple.hlsli"


// 氷シェーダー
float4 Ice(PS_INPUT i)
{
	float4 col = float4(1, 1, 1, 1);
	float alpha = 1 - abs(dot(i.viewDir, i.normal));
	col.a = alpha;
	return col;
}

// リムライティングシェーダ
float4 RimLighting(PS_INPUT i, float4 v)
{
	float4 baseColor = float4(0, 1, 0, 1);
	float4 rimColor = v;

	float rim = 1 - saturate(dot(i.viewDir, i.normal));
	float4 emission = float4(rimColor.rgb, 1) * pow(rim, 1.5f);
	return baseColor + emission;
}

float4 main(PS_INPUT i) : SV_TARGET
{
	return Ice(i) * COLOR_LIGHT_BLUE;
}