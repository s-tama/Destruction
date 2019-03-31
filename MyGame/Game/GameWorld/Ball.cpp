//
// Ball.cpp
//

#include "Ball.h"

#include "Floor.h"

using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
MyGame::Ball::Ball():
	m_velocity(0.f)
{
	SetTag("Ball");
}

/// <summary>
/// 開始
/// </summary>
void Ball::Start()
{
	// カメラの情報
	Camera* pCamera = dynamic_cast<Camera*>(NodeManager::FindGameObjectWithTag("MainCamera"));

	// オブジェクト
	Obj3D* pObj = new Obj3D();
	pObj->SetModel(ModelRepository::GetInstance()->GetModel(L"sample"));
	pObj->GetTransform()->SetParent(this->GetTransform());
	pObj->SetCamera(pCamera);
	pObj->SetLight(true);
	AddChild(pObj);

	m_pTransform->SetPosition(0, 10, 0);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void MyGame::Ball::Update(float elapsedTime)
{
	//Floor* pFloor = dynamic_cast<Floor*>(NodeManager::FindGameObjectWithTag("Floor"));

	//float gravity = 0.0098f;
	//m_velocity.y -= gravity;

	//Vector3 vebuf(m_velocity);
	//Vector3 tamamura(m_velocity);
	//tamamura.Normalize();
	//vebuf += tamamura * 0.5f;


	//Vector3 pa = pFloor->GetTransform()->GetPosition() - m_pTransform->GetPosition();
	//float dot_pa_n = pFloor->GetTransform()->GetUp().Dot(pa);
	//Vector3 pb = pFloor->GetTransform()->GetPosition() - (m_pTransform->GetPosition() + m_velocity);
	//float dot_pb_n = pFloor->GetTransform()->GetUp().Dot(pb);
	//if ((dot_pa_n >= 0.0f && dot_pb_n <= 0.0f) || (dot_pa_n <= 0.0f && dot_pb_n >= 0.0f))
	//{
	//	// 交差してるときの処理

	//	// 交点
	//	Vector3 x = m_pTransform->GetPosition() + vebuf * (dot_pa_n / (dot_pa_n + dot_pb_n));
	//	Vector3 dist_ball_floor = m_pTransform->GetPosition() - x;
	//	//dist_ball_floor = Vector3(abs(dist_ball_floor.x), abs(dist_ball_floor.y), abs(dist_ball_floor.z));
	//	Vector3 over = m_velocity - dist_ball_floor;
	//	Vector3 vel = pFloor->GetLowPointMost() - pFloor->GetTransform()->GetPosition();
	//	vel.Normalize();
	//	float f = vel.Dot(over);
	//	vebuf = vel * f;
	//	m_pTransform->SetPosition(x.x, x.y, x.z);
	//}

	//m_pTransform->SetPosition(m_pTransform->GetPosition() + m_velocity);

	//GameText::GetInstance()->AddText(Vector2(0, 100), L"%f", pFloor->GetLowPointMost().y);
}
