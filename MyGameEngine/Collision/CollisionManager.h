//
// CollisionManager.h
// 制作者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード --------------------------------------------------
#include <vector>


// クラスの定義 --------------------------------------------------------------------
namespace MyLibrary
{
	class Collider;
	class Collider2D;
	class BoxCollider2D;
	class CircleCollider;

	/// <summary>
	/// 当たり判定管理クラス
	/// </summary>
	class CollisionManager
	{
	public:

		// コンストラクタ
		CollisionManager();

		// 当たり判定を行うコライダを追加する
		static void AddCollider(CircleCollider* pCollider);
		static void AddCollider(BoxCollider2D* pCollider);
		static void RemoveCollider(Collider2D* pCollider);

		// 更新
		void Update();


	private:

		static std::vector<CircleCollider*> m_pCircleColliders;
		static std::vector<BoxCollider2D*> m_pBoxColliders2D;
	};
}
