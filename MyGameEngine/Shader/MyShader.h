//
// MyShader.hlsli
// 作成者: 玉村柊希
// 作成日: 2019/03/18(月)
// 
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

#pragma comment(lib, "DirectXTK.lib")


namespace MyLibrary
{
	// 定数バッファ0
	// 各種変換行列用
	struct ConstBuffer0
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix proj;
		DirectX::SimpleMath::Matrix wvp;
	};

	// 定数バッファ1
	// ライトとかカメラとか
	struct ConstBuffer1
	{
		DirectX::SimpleMath::Vector4 diffuse;
		DirectX::SimpleMath::Vector4 ambient;
		DirectX::SimpleMath::Vector4 specular;
		DirectX::SimpleMath::Vector4 lightPos;
		DirectX::SimpleMath::Vector4 cameraPos;
	};

	// 定数バッファ2
	// 時間関係
	struct ConstBuffer2
	{
		DirectX::SimpleMath::Vector4 time;
		DirectX::SimpleMath::Vector4 sinTime;
		DirectX::SimpleMath::Vector4 cosTime;
	};
}
