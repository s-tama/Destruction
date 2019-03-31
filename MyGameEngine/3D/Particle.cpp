//
// Particle.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード ---------------------------------------------------------------
#include "Particle.h"


// usingディレクティブ -----------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
Particle::Particle(GameObject* pGameObject):
	Component(pGameObject)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Particle::~Particle()
{
}
