//
// Game.h
//
#pragma once


// ヘッダーファイルのインクルード ---------------------------------------------
#include "MyLibrary.h"


// クラスの定義 ---------------------------------------------------------------
/// <summary>
/// ゲームクラス
/// </summary>
class Game : public MyLibrary::Framework
{
public:

	// コンストラクタ
	Game(HINSTANCE hInstance, int nCmdShow);

	
private:

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(MyLibrary::StepTimer const& timer);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	// リソースの作成
	void CreateResources();


private:

	MyLibrary::SceneManager* m_pSceneManager;	// シーンマネージャー
	MyLibrary::ObjectManager* m_pObjectManager;	// オブジェクトマネージャー
	MyLibrary::CollisionManager* m_pCollisionManager; // 当たり判定マネージャー
};