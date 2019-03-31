//
// PrimitiveRenderer.cpp
//



// ヘッダーファイルのインクルード ---------------------------------------------------
#include "PrimitiveRenderer.h"

#include "../Common/DeviceResources.h"



// usingディレクティブ --------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX;
using namespace DirectX::SimpleMath;



// 静的メンバ変数の実態 -------------------------------------------------------------
std::unique_ptr<PrimitiveRenderer> PrimitiveRenderer::m_pInstance = nullptr;



// メンバ関数の定義 -----------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
PrimitiveRenderer::PrimitiveRenderer():
	m_pPrimitiveBatch(nullptr),
	m_pCommonStates(nullptr),
	m_pInputLayout(nullptr),
	m_pAlphaEffect(nullptr),
	m_pBasicEffect(nullptr),
	m_pGeometricPrimitive(nullptr),
	m_pDevice(nullptr),
	m_pContext(nullptr)
{
}

/// <summary>
/// インスタンスを取得
/// </summary>
/// <returns>インスタンスハンドル</returns>
PrimitiveRenderer* PrimitiveRenderer::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance.reset(new PrimitiveRenderer());
	return m_pInstance.get();
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="pDevice">デバイス</param>
/// <param name="pContext">デバイスコンテキスト</param>
void PrimitiveRenderer::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;

	// プリミティブバッチの作成
	m_pPrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(m_pContext);

	// コモンステートの作成
	m_pCommonStates = std::make_unique<CommonStates>(m_pDevice);

	// エフェクトの作成 
	m_pAlphaEffect = std::make_unique<AlphaTestEffect>(m_pDevice);
	m_pAlphaEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_pAlphaEffect->SetReferenceAlpha(255);

	// インプットレイアウトの作成
	void const* shaderByteCode;
	unsigned int byteCodeLength;
	m_pAlphaEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	m_pDevice->CreateInputLayout(VertexPositionTexture::InputElements, VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_pInputLayout.GetAddressOf());
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="pTexture">テクスチャハンドル</param>
/// <param name="world">ワールド行列</param>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void PrimitiveRenderer::Draw(ID3D11ShaderResourceView* pTexture, std::vector<VertexPositionColorTexture> vertices, Matrix world, Matrix view, Matrix projection)
{
	// 頂点情報
	/*VertexPositionTexture vertices[4] =
	{
		VertexPositionTexture(Vector3(1, 1, 0), Vector2(0, 0)),
		VertexPositionTexture(Vector3(-1, 1, 0), Vector2(1, 0)),
		VertexPositionTexture(Vector3(-1, -1, 0), Vector2(1, 1)),
		VertexPositionTexture(Vector3(1, -1, 0), Vector2(0, 1))
	};*/

	// テクスチャサンプラーの設定
	ID3D11SamplerState* pSamplers[1] = { m_pCommonStates->LinearClamp() };
	m_pContext->PSSetSamplers(0, 1, pSamplers);
	// 不透明に設定
	m_pContext->OMSetBlendState(m_pCommonStates->Opaque(), nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込み参照する
	m_pContext->OMSetDepthStencilState(m_pCommonStates->DepthDefault(), 0);
	// カリングは左回り
	m_pContext->RSSetState(m_pCommonStates->CullNone());

	// 不透明のみ描画する設定
	m_pAlphaEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_pAlphaEffect->SetReferenceAlpha(255);

	m_pAlphaEffect->SetWorld(world);
	m_pAlphaEffect->SetView(view);
	m_pAlphaEffect->SetProjection(projection);
	m_pAlphaEffect->SetTexture(pTexture);
	m_pAlphaEffect->Apply(m_pContext);
	m_pContext->IASetInputLayout(m_pInputLayout.Get());

	// 不透明部分の描画
	m_pPrimitiveBatch->Begin();
	m_pPrimitiveBatch->DrawQuad(vertices[0], vertices[1], vertices[2], vertices[3]);
	m_pPrimitiveBatch->End();

	// 不透明以外の半透明部分を描画する設定
	m_pAlphaEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_pAlphaEffect->Apply(m_pContext);

	// 半透明で描画
	m_pContext->OMSetBlendState(m_pCommonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	// 深度バッファに参照のみする
	m_pContext->OMSetDepthStencilState(m_pCommonStates->DepthRead(), 0);

	// 半透明部分の描画
	m_pPrimitiveBatch->Begin();
	m_pPrimitiveBatch->DrawQuad(vertices[0], vertices[1], vertices[2], vertices[3]);
	m_pPrimitiveBatch->End();
}

/// <summary>
/// 線を描画
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="color"></param>
void PrimitiveRenderer::DrawLine(Vector3 start, Vector3 end, Color color)
{
	VertexPositionColorTexture v1, v2;

	v1.position = start;
	v2.position = end;

	v1.color = color;
	v2.color = color;

	m_pAlphaEffect->Apply(m_pContext);
	
	m_pContext->OMSetDepthStencilState(m_pCommonStates->DepthNone(), 0);
	m_pContext->OMSetBlendState(m_pCommonStates->AlphaBlend(), nullptr, 0xffffffff);
	m_pContext->RSSetState(m_pCommonStates->CullNone());
	m_pContext->IASetInputLayout(m_pInputLayout.Get());

	m_pAlphaEffect->SetWorld(Matrix::Identity);
	/*if (m_pCamera != nullptr)
	{
		m_pAlphaEffect->SetView(m_pCamera->GetView());
		m_pAlphaEffect->SetProjection(m_pCamera->GetProjection());
	}
	else
	{
		RECT rect = DeviceResources::GetInstance()->GetOutputSize();
		m_pAlphaEffect->SetView(Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0)));
		m_pAlphaEffect->SetProjection(Matrix::CreateOrthographicOffCenter(static_cast<float>(rect.left), static_cast<float>(rect.right), static_cast<float>(rect.bottom), static_cast<float>(rect.top), 0.1f, 10.0f));
	}*/

	m_pPrimitiveBatch->Begin();
	m_pPrimitiveBatch->DrawLine(v1, v2);
	m_pPrimitiveBatch->End();
}

//void PrimitiveRenderer::DrawCube()
//{
//	
//}

/// <summary>
/// 描画開始
/// </summary>
void PrimitiveRenderer::Begin()
{
//	m_pPrimitiveBatch->Begin();
}

void PrimitiveRenderer::End()
{
//	m_pPrimitiveBatch->End();
}
