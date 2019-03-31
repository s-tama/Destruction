//
// Game.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------
#include "Game.h"

#include "Scenes\SampleScene.h"



// usingディレクティブ -------------------------------------------------------------
using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;



// メンバ関数の定義 ----------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hInstance">インスタンス</param>
/// <param name="nCmdShow">表示状態</param>
Game::Game(HINSTANCE hInstance, int nCmdShow): 
	Framework(hInstance, nCmdShow, 640, 480, L"だんご大家族"),
	m_pSceneManager(nullptr),
	m_pObjectManager(nullptr)
{
	SetWindowColor(0, 0, 0);
}

/// <summary>
/// 初期化処理
/// </summary>
void Game::Initialize()
{
	// リソースの作成処理
	CreateResources();

	// シーンマネージャーの作成
	m_pSceneManager = new SceneManager();
	m_pSceneManager->StartScene(new SampleScene());

	// オブジェクトマネージャーの作成
	m_pObjectManager = new ObjectManager();
	m_pObjectManager->Initialize();

	// コリジョンマネージャーの作成
	m_pCollisionManager = new CollisionManager();
}

#pragma region ゲームループ
/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Game::Update(StepTimer const& timer)
{
	Time::GetInstance()->Update(timer);

	System::InputDevice::GetInstance()->Update();

	// エスケープキーでゲームの終了
	if (System::InputDevice::GetInstance()->GetKeyState().Escape)
	{
		PostQuitMessage(0);
	}

	m_pSceneManager->Update();
	m_pObjectManager->Update();
	m_pCollisionManager->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Render()
{
	// シーンマネージャーの描画
	m_pSceneManager->Render();
	// スプライトの描画
	SpriteRenderer* pSpriteRenderer = SpriteRenderer::GetInstance();
	pSpriteRenderer->Begin();
	pSpriteRenderer->Draw();
	pSpriteRenderer->End();
	// メッシュの描画
	MeshRenderer* pMeshRenderer = MeshRenderer::GetInstance();
	pMeshRenderer->Begin();
	pMeshRenderer->Draw();
	pMeshRenderer->End();
}
#pragma endregion

/// <summary>
/// 終了処理
/// </summary>
void Game::Finalize()
{
	SAFE_DELETE(m_pObjectManager);
	SAFE_DELETE(m_pSceneManager);
}

/// <summary>
/// リソースの作成処理
/// </summary>
void Game::CreateResources()
{
	// テクスチャ読み込み
	TextureLoader textureLoader;
	TextureRepository* pTexRepo = TextureRepository::GetInstance();
	pTexRepo->AddRepository(textureLoader.LoadTexture(L"sample"));

	// モデルの読み込み
	ModelLoader modelLoader;
	ModelRepository* pModelRepo = ModelRepository::GetInstance();
	pModelRepo->AddRepository(modelLoader.LoadModel(L"sample"));
	pModelRepo->AddRepository(modelLoader.LoadModel(L"floor"));
}
