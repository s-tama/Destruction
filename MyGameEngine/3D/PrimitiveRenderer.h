﻿//
// PrimitiveRenderer.h
//
#pragma once


// ヘッダーファイルのインクルード ------------------------------------------------
#include <windows.h>
#include <wrl/client.h>
#include <memory>
#include <string>
#include <d3d11_1.h>
#include <vector>

#include <Effects.h>
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <SimpleMath.h>
#include <CommonStates.h>
#include <GeometricPrimitive.h>


// クラスの定義 ------------------------------------------------------------------
namespace MyLibrary
{
	/// <summary>
	/// プリミティブ描画クラス
	/// </summary>
	class PrimitiveRenderer
	{
	private:

		// using
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;
		using Color = DirectX::SimpleMath::Color;


	private:

		// コンストラクタ
		PrimitiveRenderer();


	public:

		// インスタンスを取得
		static PrimitiveRenderer* GetInstance();

		// 初期化処理
		void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

		// 描画関数
		void Draw(ID3D11ShaderResourceView* pTexture,
			std::vector<DirectX::VertexPositionColorTexture> vertices,
			DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view,
			DirectX::SimpleMath::Matrix projection);
		void DrawLine(Vector3 start, Vector3 end, Color color = Color(1, 1, 1, 1));
//		void DrawCube(Vector3 size, Vector4 color);

		// 描画開始
		void Begin();
		// 描画終了
		void End();


	private:

		// インスタンス
		static std::unique_ptr<PrimitiveRenderer> m_pInstance;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_pPrimitiveBatch;
		// コモンステート
		std::unique_ptr<DirectX::CommonStates> m_pCommonStates;
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
		// エフェクト
		std::unique_ptr<DirectX::AlphaTestEffect> m_pAlphaEffect;
		std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;

		// ジオメトリックプリミティブ
		std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;

		// デバイス
		ID3D11Device* m_pDevice;
		// デバイスコンテキスト
		ID3D11DeviceContext* m_pContext;
	};
}
