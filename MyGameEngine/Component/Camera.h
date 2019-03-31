//
// Camera.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------
#include "Component.h"


namespace MyLibrary
{
	/// <summary>
	/// カメラクラス
	/// </summary>
	class Camera : public Component
	{
	public:

		Camera(GameObject* pGameObject);
		~Camera();

		// 更新
		void LateUpdate() override;

		// ターゲットの設定
		void SetTarget(Transform* pTarget) { m_pTarget = pTarget; }
		// ビュー行列の取得
		DirectX::SimpleMath::Matrix GetView() { return m_view; }
		// 射影行列の取得
		DirectX::SimpleMath::Matrix GetProjection() { return m_projection; }


	protected:
		
		DirectX::SimpleMath::Matrix m_view;			// ビュー行列
		DirectX::SimpleMath::Matrix m_projection;	// 射影行列

		Transform* m_pTarget;	// ターゲット


	private:

		static GameObject* m_pMain;		// メインカメラへのポインタ
	};
}
