//
// BoxCollider2D.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード -------------------------------------------------------------------
#include "BoxCollider2D.h"

#include "../Object/GameObject.h"
#include "..\Collision\CollisionManager.h"


// usingディレクティブ ---------------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
BoxCollider2D::BoxCollider2D(GameObject* pGameObject):
	Collider2D(pGameObject)
{
	CollisionManager::AddCollider(this);
}

/// <summary>
/// デストラクタ
/// </summary>
BoxCollider2D::~BoxCollider2D()
{
}

/// <summary>
/// セット
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
void BoxCollider2D::Set(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
{
	m_point[0] = p0;
	m_point[1] = p1;
	m_point[2] = p2;
	m_point[3] = p3;
}

/// <summary>
/// ボックスとの当たり判定
/// </summary>
/// <param name="pOther"></param>
void BoxCollider2D::OnCollisionToBox(BoxCollider2D* pOther)
{
}

/// <summary>
/// 円との当たり判定
/// </summary>
/// <param name="pOther"></param>
void BoxCollider2D::OnCollisionToCircle(CircleCollider* pOther)
{
}
