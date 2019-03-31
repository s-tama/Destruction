//
// Collider.h
//
#pragma once

#include "Component.h"

namespace MyLibrary
{
	/// <summary>
	/// コライダークラス
	/// </summary>
	class Collider : public Component
	{
	public:

		Collider(GameObject* pGameObject);
		virtual ~Collider();
	};
}
