//
// MyShader.hlsli
// 作成者: 玉村柊希
// 作成日: 2019/03/18(月)
// 


// 定数バッファ ----------------------------------------------------------------

// 定数バッファ0
// 各種変換行列用
cbuffer ConstBuffer0 : register(b0)
{
	matrix World;	// ワールド行列
	matrix View;	// ビュー行列
	matrix Proj;	// 射影行列
	matrix WVP;		// ワールドから射影までの変換行列
}

// 定数バッファ1
cbuffer ConstBuffer : register(b1)
{
	float4 Diffuse;		// 拡散反射(色)
	float4 Ambient;		// アンビエント光
	float4 Specular;	// 鏡面反射
	float4 LightPos;	// 光源座標
	float4 CameraPos;	// 視点
}

// 定数バッファ2
cbuffer ConstBuffer : register(b2)
{
	float4 Time;
	float4 SinTime;
	float4 CosTime;
}


// 定数を定義 -----------------------------------------------------
#define COLOR_RED float4(1, 0, 0, 1);
#define COLOR_GREEN float4(0, 1, 0, 1);
#define COLOR_BLUE float4(0, 0, 1, 1);
#define COLOR_LIGHT_BLUE float4(0.6f, 0.8f, 0.9f, 1);




// いろいろ使えそうな関数たち ----------------------------------------

// ライト方向を計算する(オブジェクト座標)
// 正規化なし
float3 ObjSpaceLightDir(float4 v)
{
	return mul(LightPos, World);
}

// ライト方向を計算する(ワールド座標)
// 正規化なし
float3 WorldSpaceLightDir(float4 v)
{
	float3 worldPos = mul(v, World);
	return LightPos - worldPos;
}

// カメラ方向を計算する(オブジェクト座標)
// 正規化なし
float3 ObjSpaceViewDir(float4 v)
{
	return mul(CameraPos, World);
}

// カメラ方向を計算する(ワールド座標)
// 正規化なし
float3 WorldSpaceViewDir(float4 v)
{
	float3 worldPos = mul(v, World);
	return CameraPos - worldPos;
}

// ランバート拡散
float4 Lambert(float4 col, float3 normal)
{
	float c = saturate(dot(normal, (float3)LightPos));
	col = float4(c, c, c, 1);
	return col;
}