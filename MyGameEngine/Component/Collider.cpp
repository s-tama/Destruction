//
// Collider.cpp
//

#include "Collider.h"

#include "..\Object\GameObject.h"
#include "..\Collision\CollisionManager.h"

using namespace MyLibrary;

/// <summary>
/// コンストラクタ
/// </summary>
Collider::Collider(GameObject* pGameObject):
	Component(pGameObject)
{
}

/// <summary>
/// 仮想デストラクタ
/// </summary>
Collider::~Collider()
{
}
