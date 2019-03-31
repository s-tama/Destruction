//
// SphereCollider.cpp
//



// ヘッダーファイルのインクルード -------------------------------------------------
#include "SphereCollider.h"

#include "..\Object\GameObject.h"



// usingディレクティブ ------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ---------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SphereCollider::SphereCollider(GameObject* pGameObject): 
	Collider(pGameObject),
	m_radius(0.f), 
	m_center(Vector3::Zero)
{
}
