//
// GameObject.cpp
//



// ヘッダーファイルのインクルード -----------------------------------------------------
#include "GameObject.h"

#include "ObjectManager.h"

#include "..\2D\Sprite.h"
#include "..\2D\SpriteRenderer.h"
#include "..\3D\Mesh.h"
#include "..\3D\MeshRenderer.h"



// usingディレクティブ ----------------------------------------------------------------
using namespace MyLibrary;



// メンバ関数の定義 -------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">タグ名</param>
GameObject::GameObject():
	m_tag("")
{
	AddComponent<Transform>();
	m_pTransform = GetComponent<Transform>();

	ObjectManager::Add(this);
}

/// <summary>
/// 仮想デストラクタ
/// </summary>
GameObject::~GameObject()
{
	for (auto& component : m_pComponents)
	{
		delete component;
		component = nullptr;
	}
	m_pComponents.clear();
}

/// <summary>
/// 初期化
/// </summary>
void GameObject::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::Update()
{
	for (auto& component : m_pComponents)
	{
		component->Update();
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::LateUpdate()
{
	for (auto& component : m_pComponents)
	{
		component->LateUpdate();
	}
}

/// <summary>
/// コンポーネントを開放する
/// </summary>
/// <param name="pComponent">削除するコンポーネント</param>
void GameObject::RemoveComponent(Component* pComponent)
{
	auto it = m_pComponents.begin();
	while (it != m_pComponents.end())
	{
		if(dynamic_cast<Mesh*>(*it) != nullptr)
			MeshRenderer::GetInstance()->RemoveMesh(dynamic_cast<Mesh*>(*it));

		delete *it;
		(*it) = nullptr;
		it = m_pComponents.erase(it);
		it++;
	}
}
