//
// SampleScene.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------------
#include "SampleScene.h"

#include "..\GameWorld\MainCamera.h"
#include "..\GameWorld\SampleObj.h"



// usingディレクティブ -------------------------------------------------------------------
using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ----------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SampleScene::SampleScene()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void SampleScene::Initialize()
{
	MainCamera* pCamera = new MainCamera();
	m_pObj1 = new SampleObj();
}

/// <summary>
/// 更新処理
/// </summary>
void SampleScene::Update()
{	
	m_pObj1->GetTransform()->Rotate(0, 1, 0);
}

/// <summary>
/// 描画処理
/// </summary>
void SampleScene::Render()
{
	// シーン名を描画
	GameText::GetInstance()->AddText(Vector2(0, 0), Colors::White, 2, L"さんぷるシーン");
}

/// <summary>
/// 終了処理
/// </summary>
void SampleScene::Finalize()
{
	SpriteRenderer::GetInstance()->Reset();
	MeshRenderer::GetInstance()->Reset();
}
