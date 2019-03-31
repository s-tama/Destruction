//
// BoxCollider.cpp
//



// ヘッダーファイルのインクルード -------------------------------------------------
#include "BoxCollider.h"

#include "..\Object\GameObject.h"



// usingディレクティブ ------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ---------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
BoxCollider::BoxCollider(GameObject* pGameObject):
	Collider(pGameObject),
	m_center(Vector3::Zero), 
	m_extents(Vector3::Zero)
{
}
