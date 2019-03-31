//
// Component.cpp
//



// ヘッダーファイルのインクルード ----------------------------------------------------------
#include "Component.h"
#include "..\Object\GameObject.h"
#include "Transform.h"



// usingディレクティブ ---------------------------------------------------------------------
using namespace MyLibrary;



// メンバ関数の定義 ------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
Component::Component(GameObject* pGameObject, int updateOrder):
	m_pGameObject(pGameObject), 
	m_pTransform(pGameObject->GetTransform())
{
}

/// <summary>
/// 仮想デストラクタ
/// </summary>
Component::~Component()
{
}
