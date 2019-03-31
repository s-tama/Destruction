//
// SceneManager.h
//
#pragma once

#include "SceneBase.h"


namespace MyLibrary
{
	class SceneManager
	{
	public:

		SceneManager();
		~SceneManager();

		void StartScene(SceneBase* pStartScene);
		void Update();
		void Render();

		static void LoadScene(SceneBase* pNextScene);


	private:

		bool ChangeScene();


	private:

		SceneBase* m_pActiveScene;
		static SceneBase* m_pNextScene;
	};
}
