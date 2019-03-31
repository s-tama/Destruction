//
// SimpleVS.hlsl
//

#include "MyShader.hlsli"
#include "Simple.hlsli"


PS_INPUT main(VS_INPUT i)
{
	//PS_INPUT o = (PS_INPUT)0;

	//o.pos = mul(i.pos, World);
	//o.pos = mul(o.pos, View);
	//o.pos = mul(o.pos, Proj);

	//// 法線
	//o.normal = mul(i.normal, (float3x3)World);
	//o.normal = normalize(o.normal);

	//// ライト方向
	//o.lightDir = WorldSpaceLightDir(i.pos);
	//o.lightDir = normalize(o.lightDir);

	//// カメラ方向
	//o.viewDir = WorldSpaceViewDir(i.pos);
	//o.viewDir = normalize(o.viewDir);

	PS_INPUT o = (PS_INPUT)0;
	o.pos = i.pos;
	o.normal = i.normal;

	return o;
}