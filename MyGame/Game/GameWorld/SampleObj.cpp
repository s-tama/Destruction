//
// SampleObj.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード --------------------------------------------------------------------
#include "SampleObj.h"


// usingディレクティブ ---------------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


// メンバ関数の定義 -----------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SampleObj::SampleObj()
{
	Mesh* pMesh = AddComponent<Mesh>();
	pMesh->CreateShaderFromCSO(L"Resources\\Shaders\\SimpleVS.cso", L"Resources\\Shaders\\SimplePS.cso", L"Resources\\Shaders\\SimpleGS.cso");
	pMesh->CreateMeshFromObj(L"Resources\\Obj\\Sphere.obj");
	//pMesh->CreateCube();
	//Sprite* pSprite = AddComponent<Sprite>();
	//pSprite->SetTexture(TextureRepository::GetInstance()->GetTexture(L"sample"));
	//pSprite->AnchorPoint() = Vector2(0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
SampleObj::~SampleObj()
{
}
