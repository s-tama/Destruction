//
// GameObject.h
//
#pragma once


// ヘッダーファイルのインクルード ---------------------------------------------------------
#include <string>
#include <vector>
#include <memory>

#include "Object.h"
#include "../Component/Component.h"
#include "..\Component\Transform.h"
#include "..\Component\Collider.h"


// クラスの定義 ---------------------------------------------------------------------------
namespace MyLibrary
{
	class Sprite;
	class SpriteRenderer;
	class Mesh;
	class MeshRenderer;

	/// <summary>
	/// ゲームオブジェクトクラス
	/// </summary>
	class GameObject : public Object
	{
	public:

		GameObject();
		virtual ~GameObject();

		// メイン処理
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();

		// 当たった時の処理
		virtual void OnCollisionStay(GameObject* collider){}
		virtual void OnCollisionEnter(Collider* collider){}
		virtual void OnCollisionExit(Collider* collision){}

		// 変換情報(読み取り専用)
		Transform* GetTransform() const { return m_pTransform; }

		// タグ
		void SetTag(std::string tag) { m_tag = tag; }
		std::string GetTag() const { return m_tag; }

		// コンポーネントの追加
		template <typename T>
		T* AddComponent()
		{
			Component* component = new T(this);
			m_pComponents.push_back(component);
			return dynamic_cast<T*>(component);
		}
		// コンポーネントの削除
		template <typename T>
		void RemoveComponent()
		{
			auto it = m_pComponents.begin();
			while (it != m_pComponents.end())
			{
				Sprite* pSprite = dynamic_cast<Sprite*>(*it);
				if (pSprite) SpriteRenderer::GetInstance()->RemoveSprite(pSprite);
				Mesh* pMesh = dynamic_cast<Mesh*>(*it);
				if (pMesh) MeshRenderer::GetInstance()->RemoveMesh(pMesh);

				if (dynamic_cast<T*>(*it))
				{
					delete *it;
					it = m_pComponents.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		// コンポーネントの取得
		template <typename T>
		T* GetComponent() const 
		{
			for (auto& components : m_pComponents)
			{
				T* pComponent = dynamic_cast<T*>(components);
				if (pComponent)
				{
					return pComponent;
				}
			}
			return nullptr;
		}
		// 全コンポーネントの取得
		std::vector<Component*> GetComponents() { return m_pComponents; }

		void RemoveComponent(Component* pComponent);


	private:

		std::string m_tag;		// タグ名
		std::vector<Component*> m_pComponents;		// コンポネント配列

		
	protected:

		Transform* m_pTransform;		// 変換情報
	};
}
