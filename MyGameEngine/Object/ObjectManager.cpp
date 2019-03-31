//
// ObjectManager.cp
//


// ヘッダーファイルのインクルード ---------------------------------------------------------------
#include "ObjectManager.h"

#include "Object.h"
#include "GameObject.h"
#include "../Component/Component.h"


// usingディレクティブ ----------------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX::SimpleMath;


// 静的メンバ変数の実態 -------------------------------------------------------------------
std::vector<GameObject*> ObjectManager::m_pObjects;


// メンバ関数の定義 ------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
ObjectManager::ObjectManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectManager::~ObjectManager()
{
	for (auto& obj : m_pObjects)
	{
		delete obj;
		obj = nullptr;
	}
	m_pObjects.clear();
}

/// <summary>
/// オブジェクトを追加する
/// </summary>
/// <param name="pGameObject"></param>
void ObjectManager::Add(GameObject* pGameObject)
{
	pGameObject->Initialize();
	m_pObjects.push_back(pGameObject);
}

/// <summary>
/// 指定タグのオブジェクトを取得する	
/// </summary>
/// <param name="tag"></param>
/// <returns></returns>
GameObject* ObjectManager::FindGameObjectWithTag(std::string tag)
{
	for (auto obj : m_pObjects)
	{
		if (obj->GetTag() == tag)
		{
			return obj;
		}
	}

	return nullptr;
}

/// <summary>
/// 指定タグのオブジェクトをすべて取得する
/// </summary>
/// <param name="tag"></param>
/// <returns></returns>
std::vector<GameObject*> ObjectManager::FindGameObjectsWithTag(std::string tag)
{
	std::vector<GameObject*> pObjs;

	for (auto obj : m_pObjects)
	{
		if (obj->GetTag() == tag)
		{
			pObjs.push_back(obj);
		}
	}

	return pObjs;
}

/// <summary>
/// 全オブジェクトを取得する
/// </summary>
/// <returns></returns>
std::vector<GameObject*> ObjectManager::GetGameObjects()
{
	return m_pObjects;
}

/// <summary>
/// 初期化
/// </summary>
void ObjectManager::Initialize()
{
	for (auto& obj : m_pObjects)
	{
		obj->Initialize();
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void ObjectManager::Update()
{
	// オブジェクトを更新する
	for (auto& obj : m_pObjects)
	{
		obj->Update();
	}

	for (auto& obj : m_pObjects)
	{
		obj->LateUpdate();
	}
}
