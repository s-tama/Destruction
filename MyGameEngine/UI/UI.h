//
// UI.h
// 作成日: 2019/03/31(日)
//
#pragma once

#include "..\Component\Component.h"


namespace MyLibrary
{
	class UI : public Component
	{
	public:

		UI(GameObject* pGameObject):
			Component(pGameObject){}
		virtual ~UI(){}
	};
}
