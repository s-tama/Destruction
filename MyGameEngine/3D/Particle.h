//
// Particle.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード -----------------------------------------------------------------
#include "..\Component\Component.h"


namespace MyLibrary
{
	/// <summary>
	/// パーティクルコンポーネント
	/// </summary>
	class Particle : public Component
	{
	public:

		Particle(GameObject* pGameObject);
		~Particle();

		
	};
}
