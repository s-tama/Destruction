//
// CollisionManager.cpp
//


// ヘッダーファイルのインクルード -----------------------------------------------------------
#include "CollisionManager.h"

#include "..\Component\Collider.h"
#include "..\Component\Collider2D.h"
#include "..\Component\BoxCollider2D.h"
#include "..\Component\CircleCollider.h"


// usingディレクティブ -------------------------------------------------------------------
using namespace MyLibrary;


// 静的メンバ変数の定義 -----------------------------------------------------------------
std::vector<CircleCollider*> CollisionManager::m_pCircleColliders;
std::vector<BoxCollider2D*> CollisionManager::m_pBoxColliders2D;


// メンバ関数の定義 ----------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pNode"></param>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// 当たり判定用のコライダを追加する
/// </summary>
/// <param name="pCollider"></param>
void CollisionManager::AddCollider(CircleCollider* pCollider)
{
	m_pCircleColliders.push_back(pCollider);
}
void CollisionManager::AddCollider(BoxCollider2D* pCollider)
{
	m_pBoxColliders2D.push_back(pCollider);
}

/// <summary>
/// 指定したコライダを削除する
/// </summary>
/// <param name="pCollider"></param>
void CollisionManager::RemoveCollider(Collider2D* pCollider)
{
	for (auto& c : m_pCircleColliders)
	{
		if (c == pCollider)
		{
			delete c;
			c = nullptr;
		}
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CollisionManager::Update()
{
	for (auto& c1 : m_pCircleColliders)
	{
		for (auto& c2 : m_pCircleColliders)
		{
			if (c1 != c2)
			{
				c1->OnCollisionToCircle(c2);
				c2->OnCollisionToCircle(c1);
			}
		}
	}
}
