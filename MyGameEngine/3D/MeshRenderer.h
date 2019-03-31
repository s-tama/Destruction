//
// MeshRenderer.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------------------
#include <d3d11.h>
#include <memory>
#include <vector>
#include <SimpleMath.h>
#include <CommonStates.h>


// 使用ライブラリ -----------------------------------------------------------------------------
#pragma comment(lib, "DirectXTK.lib")


namespace MyLibrary
{
	class Mesh;

	/// <summary>
	/// メッシュの描画専用
	/// </summary>
	class MeshRenderer
	{
	private:

		// コンストラクタ
		MeshRenderer();


	public:

		// インスタンスを取得
		static MeshRenderer* GetInstance();

		// メッシュの追加
		void AddMesh(Mesh* pMesh);
		// メッシュの削除
		void RemoveMesh(Mesh* pMesh);

		// 初期化
		void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
		// メッシュを描画する
		void Draw();

		// 描画情報の設定
		void SetView(DirectX::SimpleMath::Matrix view) { m_view = view; }
		void SetProjection(DirectX::SimpleMath::Matrix projection) { m_projection = projection; }
		void SetEye(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }

		// 描画に必要(必ずBeginとEndの間で呼び出すこと)
		void Begin();
		void End();

		// リセット
		void Reset();


	private:

		static std::unique_ptr<MeshRenderer> m_pInstance;		// インスタンス

		std::vector<Mesh*> m_pMeshes;	// メッシュデータ

		ID3D11Device* m_pDevice;			// デバイス
		ID3D11DeviceContext* m_pContext;	// デバイスコンテキスト

		std::unique_ptr<DirectX::CommonStates> m_pCommonStates;	// コモンステート

		DirectX::SimpleMath::Matrix m_view;				// ビュー行列
		DirectX::SimpleMath::Matrix m_projection;		// 射影行列
		DirectX::SimpleMath::Vector3 m_eye;
	};
}
