//
// SimpleGS.hlsl
// 作成日: 2019/03/31(日)
//

#include "MyShader.hlsli"
#include "Simple.hlsli"


[maxvertexcount(3)]
void main(triangle PS_INPUT input[3], inout TriangleStream<PS_INPUT> output)
{
	// ポリゴンの中心を計算
	float3 center = (input[0].pos + input[1].pos + input[2].pos) / 3;

	// ポリゴンの法線を計算
	float3 v0 = input[1].pos.xyz - input[0].pos.xyz;
	float3 v1 = input[2].pos.xyz - input[1].pos.xyz;
	float3 normal = normalize(cross(v0, v1));

	for (uint i = 0; i < 3; i++)
	{
		PS_INPUT v = input[i];
		PS_INPUT o;

		// 単位を変化
		float destruction = max(0, sin(Time * 50));
		destruction *= 3;
		// 中心位置を起点にスケールを変化させます。
		//v.pos.xyz = (v.pos.xyz - center) * (1.0 - destruction) + center;
		// 法線方向に位置を変化
		v.pos.xyz += normal * destruction;

		// 変換
		o.pos = mul(v.pos, World);
		o.pos = mul(o.pos, View);
		o.pos = mul(o.pos, Proj);

		// 法線
		o.normal = mul(v.normal, (float3x3)World);
		o.normal = normalize(o.normal);

		// ライト方向
		o.lightDir = WorldSpaceLightDir(v.pos);
		o.lightDir = normalize(o.lightDir);

		// カメラ方向
		o.viewDir = WorldSpaceViewDir(v.pos);
		o.viewDir = normalize(o.viewDir);

		output.Append(o);
	}

	output.RestartStrip();
}