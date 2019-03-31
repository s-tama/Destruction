//
// MainCamera.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------
#include "MainCamera.h"



// usingディレクティブ -------------------------------------------------------------
using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ----------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
MainCamera::MainCamera()
{
	SetTag("MainCamera");

	m_pCamera = AddComponent<Camera>();

	m_pTransform->SetPosition(0, 3, -5);
}
