﻿//
// Sprite.h
//
#pragma once



// ヘッダーファイルのインクルード ------------------------------------------------------------------
#include <SpriteBatch.h>

#include "..\Component\Component.h"
#include "Texture.h"
#include "SpriteRenderer.h"



// クラスの定義 ------------------------------------------------------------------------------------
namespace MyLibrary
{
	/// <summary>
	/// スプライトクラス
	/// </summary>
	class Sprite : public Component
	{
	public:

		// コンストラクタ
		Sprite(GameObject* pGameObject);

		// 描画処理
		void Draw(DirectX::SpriteBatch* pSpriteBatch);

		// テクスチャ情報
		void SetTexture(Texture* pTexture);
		Texture* GetTexture();

		// 切り取り情報
		RECT& Rect();

		// 色情報
		DirectX::SimpleMath::Vector4& Color();

		// アンカーポイント
		DirectX::SimpleMath::Vector2& AnchorPoint();

		// 回転情報
		float& Rotation();

		// スケール
		float& Scale();

		
	private:

		// テクスチャハンドル
		Texture* m_pTexture;

		// 色
		DirectX::SimpleMath::Vector4 m_color;

		// 切り取り
		RECT m_rect;

		// アンカーポイント
		DirectX::SimpleMath::Vector2 m_anchorPoint;

		// 回転
		float m_rotation;

		// スケール
		float m_scale;
	};
}
