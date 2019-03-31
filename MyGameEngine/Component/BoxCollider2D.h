//
// BoxCollider2D.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード -------------------------------------------------------------------
#include "Collider2D.h"


namespace MyLibrary
{
	/// <summary>
	/// 2D用当たり判定ボックス
	/// </summary>
	class BoxCollider2D : public Collider2D
	{
	private:

		using Vector2 = DirectX::SimpleMath::Vector2;


	public:

		BoxCollider2D(GameObject* pGameObject);
		~BoxCollider2D();

		void Set(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3);

		void OnCollisionToBox(BoxCollider2D* pOther) override;
		void OnCollisionToCircle(CircleCollider* pOther) override;


	private:

		Vector2 m_point[4];
	};
}
