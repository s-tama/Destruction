//
// MeshRenderer.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード ---------------------------------------------------------------
#include "MeshRenderer.h"

#include "Mesh.h"


// usingディレクティブ -----------------------------------------------------------------------
using namespace DirectX;
using namespace MyLibrary;


// 静的メンバ変数の実態 --------------------------------------------------------------------
std::unique_ptr<MeshRenderer> MeshRenderer::m_pInstance = nullptr;


/// <summary>
/// コンストラクタ
/// </summary>
MeshRenderer::MeshRenderer()
{
}

/// <summary>
/// クラスのインスタンスを取得する
/// </summary>
/// <returns></returns>
MeshRenderer* MeshRenderer::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance.reset(new MeshRenderer());
	return m_pInstance.get();
}

/// <summary>
/// メッシュを追加する
/// </summary>
/// <param name="pMesh"></param>
void MeshRenderer::AddMesh(Mesh* pMesh)
{
	m_pMeshes.push_back(pMesh);
}

/// <summary>
/// 指定メッシュを配列から削除する
/// メモリは最後にすべて開放されるので、開放は行わない
/// 必ずメッシュコンポーネントが外されるときに一緒に呼び出すこと
/// </summary>
/// <param name="pMesh">削除したいメッシュ</param>
void MeshRenderer::RemoveMesh(Mesh* pMesh)
{
	auto it = m_pMeshes.begin();
	while (it != m_pMeshes.end())
	{
		if ((*it) == pMesh)
		{
			it = m_pMeshes.erase(it);
		}
		else
		{
			it++;
		}
	}
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pDevice">デバイス</param>
/// <param name="pContext">デバイスコンテキスト</param>
void MeshRenderer::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;

	// コモンステートを作成する
	m_pCommonStates = std::make_unique<CommonStates>(pDevice);
}

/// <summary>
/// メッシュを描画する
/// 必ずMeshRendererのBeginとEndの間で呼び出すこと
/// </summary>
void MeshRenderer::Draw()
{
	for (auto& mesh : m_pMeshes)
	{
		mesh->Draw(m_view, m_projection, m_eye);
	}
}

/// <summary>
/// 描画開始
/// 必ず描画の前に呼び出すこと
/// </summary>
void MeshRenderer::Begin()
{
	// 使用するシェーダーの登録
	m_pContext->VSSetShader(nullptr, nullptr, 0);
	m_pContext->GSSetShader(nullptr, nullptr, 0);
	m_pContext->PSSetShader(nullptr, nullptr, 0);

	// 描画情報の設定
	m_pContext->OMSetBlendState(m_pCommonStates->NonPremultiplied(), nullptr, 0xffffffff);
	m_pContext->OMSetDepthStencilState(m_pCommonStates->DepthDefault(), 0);
	m_pContext->RSSetState(m_pCommonStates->CullNone());
}

/// <summary>
/// 描画終了
/// 必ず描画の後に呼び出すこと
/// </summary>
void MeshRenderer::End()
{
	// 使用するシェーダーの登録
	m_pContext->VSSetShader(nullptr, nullptr, 0);
	m_pContext->GSSetShader(nullptr, nullptr, 0);
	m_pContext->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// メッシュ配列を削除する
/// 必ずシーンを終了するたびに呼び出すこと
/// </summary>
void MeshRenderer::Reset()
{
	m_pMeshes.clear();
}
