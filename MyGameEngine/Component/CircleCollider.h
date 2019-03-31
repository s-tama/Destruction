//
// CircleCollider.h
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
	class CircleCollider : public Collider2D
	{
	private:

		using Vector2 = DirectX::SimpleMath::Vector2;


	public:

		CircleCollider(GameObject* pGameObject);
		~CircleCollider();

		void Set(float radius);
		float GetRadius() const { return m_radius; }
		Vector2 GetCenter() const { return m_center; }

		void OnCollisionToBox(BoxCollider2D* pOther) override;
		void OnCollisionToCircle(CircleCollider* pOther) override;


	private:

		Vector2 m_center;
		float m_radius;
	};
}
