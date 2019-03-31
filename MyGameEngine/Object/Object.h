//
// Object.h
//
#pragma once


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


#include <d3d11.h>
#include <SimpleMath.h>
#include <list>
#include <vector>
#include <functional>
#include <string>

#include "../Utility/Flag.h"


namespace MyLibrary
{
	/// <summary>
	/// オブジェクトノードクラス
	/// </summary>
	class Object
	{
	private:

		const byte IS_ACTIVE = 1 << 7;
		const byte IS_REMOVE = 1 << 6;


	public:

		Object(){}
		virtual ~Object(){}

		virtual void Create(){}
		virtual void Initialize(){}
		virtual void Update(){}
		virtual void LateUpdate(){}

		// オブジェクト名
		std::string GetName() { return m_name; }

		// アクティブ状態の取得
		void SetActive(bool activeState) { if (activeState) m_flag.On(IS_ACTIVE); else { m_flag.Off(IS_ACTIVE); } }
		bool IsActive() { return m_flag.Check(IS_ACTIVE); }


	private:

		std::string m_name;	// オブジェクト名

		Utility::Flag m_flag;	// フラグ
	};
}
