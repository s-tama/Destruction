//
// Camera.cpp
//


// ヘッダーファイルのインクルード ------------------------------------------
#include "Camera.h"

#include "..\Object\GameObject.h"
#include "Transform.h"
#include "../Object/ObjectManager.h"
#include "..\Common\DeviceResources.h"
#include "..\3D\MeshRenderer.h"


// usingディレクティブ --------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


// 静的メンバ変数の実態 -----------------------------------------------
GameObject* Camera::m_pMain = nullptr;


/// <summary>
/// コンストラクタ	
/// </summary>
Camera::Camera(GameObject* pGameObject):
	Component(pGameObject),
	m_view(Matrix::Identity),
	m_projection(Matrix::Identity),
	m_pTarget(nullptr)
{
	// "MainCamera"タグのオブジェクトをメインに設定
	if (pGameObject->GetTag() == "MainCamera")
	{
		m_pMain = pGameObject;
	}

	// ビュー行列を作成する
	Vector3 eye(0, 1, -10);
	Vector3 trg(0, 0, 0);
	Vector3 up(0, 1, 0);
	m_view = Matrix::CreateLookAt(eye, trg, up);

	// 射影行列を作成する
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	float fov = XM_PI / 4.0f;
	long width = pDeviceResources->GetOutputSize().right;
	long height = pDeviceResources->GetOutputSize().bottom;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float nearPlane = 0.001f;
	float farPlane = 100.0f;
	m_projection = Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// 更新する
/// </summary>
/// <param name="elapsedTime"></param>
void Camera::LateUpdate()
{
	// ビュー行列を作成する
	Vector3 eye(m_pTransform->GetPosition());
	Vector3 trg(0, 0, 0);
	Vector3 up(0, 1, 0);
	m_view = Matrix::CreateLookAt(eye, trg, up);

	// メッシュレンダラーに描画情報を設定する
	MeshRenderer::GetInstance()->SetView(m_view);
	MeshRenderer::GetInstance()->SetProjection(m_projection);
	MeshRenderer::GetInstance()->SetEye(m_pTransform->GetPosition());
}
