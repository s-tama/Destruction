//
// Collider2D.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------------------
#include "Component.h"


namespace MyLibrary
{
	class BoxCollider2D;
	class CircleCollider;

	/// <summary>
	/// 2Dオブジェクト用コライダ
	/// </summary>
	class Collider2D : public Component
	{
	public:

		Collider2D(GameObject* pGameObject);
		virtual ~Collider2D();

		//virtual void OnCollisionToBox(const std::vector<Collider2D*>& pOthers) = 0;
		//virtual void OnCollisionToCircle(const std::vector<Collider2D*>& pOthers) = 0;

		virtual void OnCollisionToBox(BoxCollider2D* pOther) = 0;
		virtual void OnCollisionToCircle(CircleCollider* pOther) = 0;
	};
}
