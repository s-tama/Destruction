//
// MainCamera.h
//
#pragma once


// ヘッダーファイルのインクルード ------------------------------------------------------
#include "MyLibrary.h"


// クラスの定義 ------------------------------------------------------------------------
namespace MyGame
{
	/// <summary>
	/// メインカメラクラス
	/// </summary>
	class MainCamera : public MyLibrary::GameObject
	{
	public:

		// コンストラクタ
		MainCamera();


	private:

		MyLibrary::Camera* m_pCamera;
	};
}
