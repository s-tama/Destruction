//
// Collider2D.cpp
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード ---------------------------------------------------------------
#include "Collider2D.h"

#include "BoxCollider2D.h"
#include "CircleCollider.h"


// usingディレクティブ -----------------------------------------------------------------------
using namespace DirectX;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject">子のコライダを所持するオブジェクト</param>
Collider2D::Collider2D(GameObject* pGameObject):
	Component(pGameObject)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Collider2D::~Collider2D()
{
}
