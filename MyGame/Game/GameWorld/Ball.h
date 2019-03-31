//
// Ball.h
//
#pragma once

#include "MyLibrary.h"


namespace MyGame
{
	/// <summary>
	/// ボール(プレイヤー)クラス
	/// </summary>
	class Ball : public MyLibrary::GameObject
	{
	public:

		Ball();

		void Start() override;
		void Update(float elapsedTime) override;


	private:

		DirectX::SimpleMath::Vector3 m_velocity;
	};
}
