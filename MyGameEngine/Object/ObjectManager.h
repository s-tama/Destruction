//
// ObjectManager.h
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------------------
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>

#include "..\Common\StepTimer.h"


// 使用ライブラリ ----------------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


namespace MyLibrary
{
	class Object;
	class GameObject;

	/// <summary>
	/// オブジェクト管理クラス
	/// </summary>
	class ObjectManager
	{
	public:

		ObjectManager();
		~ObjectManager();

		// オブジェクトを初期化する
		void Initialize();
		// オブジェクトを更新する
		void Update();

		// オブジェクトを追加する
		static void Add(GameObject* pGameObject);

		// オブジェクトを取得する
		static GameObject* FindGameObjectWithTag(std::string tag);
		static std::vector<GameObject*> FindGameObjectsWithTag(std::string tag);
		static std::vector<GameObject*> GetGameObjects();
		

	private:

		static std::vector<GameObject*> m_pObjects;		// ゲームオブジェクト配列
	};
}
