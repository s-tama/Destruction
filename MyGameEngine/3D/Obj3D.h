//
// Obj3D
//
#pragma once


// ヘッダーファイルのインクルード -------------------------------------------------
#include <Effects.h>

#include "..\Component\Component.h"
#include "Model3D.h"
#include "../Utility/Flag.h"


// クラスの定義 -------------------------------------------------------------------
namespace MyLibrary
{
	/// <summary>
	/// 3Dオブジェクトクラス
	/// </summary>
	class Obj3D : public Component
	{
	private:

		// フラグ定数
		const UCHAR LIGHT = 1 << 7;


	public:

		// コンストラクタ
		Obj3D(GameObject* pGameObject);

		// モデル情報の設定
		void SetModel(Model3D* pModel);

		// 初期化処理
		void Start()				override;
		// 更新処理
		void Update()	override;
		// 描画処理
		void Draw();


	private:

		// モデル3Dへのポインタ
		Model3D* m_pModel;

		// フラグ
		Utility::Flag m_flag;
	};
}
