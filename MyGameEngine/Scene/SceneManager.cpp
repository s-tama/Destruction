//
// SceneManager.cpp
//

#include "SceneManager.h"

using namespace MyLibrary;


// 次のシーンへのポインタ
SceneBase* SceneManager::m_pNextScene = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager():
	m_pActiveScene(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	m_pActiveScene->Finalize();
	delete m_pActiveScene;
	m_pActiveScene = nullptr;
}

/// <summary>
/// 開始シーン
/// </summary>
/// <param name="pStartScene">開始シーンを設定</param>
void SceneManager::StartScene(SceneBase* pStartScene)
{
	m_pActiveScene = pStartScene;
	m_pActiveScene->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void SceneManager::Update()
{
	if (m_pActiveScene != nullptr)
	{
		m_pActiveScene->Update();
	}

	if (m_pNextScene != nullptr)
	{
		ChangeScene();
		m_pNextScene = nullptr;
	}
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Render()
{
	if (m_pActiveScene != nullptr)
	{
		m_pActiveScene->Render();
	}
}

/// <summary>
/// シーンのロード
/// </summary>
/// <param name="pSceneBase"></param>
void SceneManager::LoadScene(SceneBase* pNextScene)
{
	if (m_pNextScene == nullptr)
	{
		m_pNextScene = pNextScene;
	}
}

/// <summary>
/// シーンを変更する
/// </summary>
/// <returns></returns>
bool SceneManager::ChangeScene()
{
	m_pActiveScene->Finalize();
	delete m_pActiveScene;
	m_pActiveScene = m_pNextScene;
	m_pActiveScene->Initialize();

	return true;
}
