//
// Text.h
// 作成日: 2019/03/31(日)
//
#pragma once

#include "UI.h"


namespace MyLibrary
{
	class Text : public UI
	{
	public:

		Text(GameObject* pGameObject);
		~Text(){}

		// 使用するフォントファイルを設定
		// .spritefontを設定
		void SetFont(const wchar_t* pFileName);

		// 描画テキストを設定
		void SetText(LPCWSTR text);

		void Draw();


	private:
	};
}
