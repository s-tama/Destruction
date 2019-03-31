//
// SampleScene.h
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------
#include "MyLibrary.h"

class SampleObj;

// クラスの定義 ----------------------------------------------------------------------
namespace MyGame
{
	/// <summary>
	/// サンプルシーン
	/// </summary>
	class SampleScene : public MyLibrary::SceneBase
	{
	public:

		// コンストラクタ
		SampleScene();

		// 初期化処理
		void Initialize()				override;
		// 更新処理
		void Update()					override;
		// 描画処理
		void Render()					override;
		// 終了処理
		void Finalize()					override;


	private:

		SampleObj* m_pObj1;
	};
}
