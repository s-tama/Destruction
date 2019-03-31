//
// Text.cpp
// 作成日: 2019/03/31(日)
//

#include "Text.h"

#include "..\Object\GameObject.h"
#include "..\Component\Transform.h"

using namespace MyLibrary;


Text::Text(GameObject* pGameObject):
	UI(pGameObject)
{
}

void MyLibrary::Text::SetFont(const wchar_t * pFileName)
{
}

void MyLibrary::Text::SetText(LPCWSTR text)
{
}

void MyLibrary::Text::Draw()
{
}
