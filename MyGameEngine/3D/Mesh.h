//
// Mesh.h
// 作成者: Tamamura Shuuki
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------------------
#include "../Component/Component.h"

#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

#include "..\Component\Transform.h"
#include "..\Utility\BinaryFile.h"
#include "../Shader/MyShader.h"


namespace MyLibrary
{
	/// <summary>
	/// メッシュデータ
	/// </summary>
	class Mesh : public Component
	{
	private:

		static const D3D11_INPUT_ELEMENT_DESC INPUT_LAYOUT[];	// 頂点レイアウト


	public:

		// 頂点情報
		struct Vertex
		{
			Vertex()
			{
				ZeroMemory(this, sizeof(Vertex));
			}

			DirectX::SimpleMath::Vector3 position;
			DirectX::SimpleMath::Vector3 normal;
		};

		// インデックスデータ
		struct Index
		{
			Index()
			{
				ZeroMemory(this, sizeof(Index));
			}

			uint16_t positions;
			uint16_t normals;
		};

		// メッシュの三角形ポリゴンデータ
		struct Triangle
		{
			Triangle(DirectX::SimpleMath::Vector3 p0, DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 p2):
				point{ p0, p1, p2 },
				world(DirectX::SimpleMath::Matrix::Identity)
			{	
				// 3頂点から面法線を計算する
				DirectX::SimpleMath::Vector3 v0, v1;
				v0 = p0 - p1;
				v1 = p2 - p1;
				normal = v0.Cross(v1);
			}

			DirectX::SimpleMath::Vector3 point[3];	
			DirectX::SimpleMath::Vector3 normal;
			DirectX::SimpleMath::Matrix world;	
		};


	public:

		Mesh(GameObject* pGameObject);
		~Mesh();

		HRESULT CreateShaderFromCSO(const wchar_t* vs, const wchar_t* ps = nullptr, const wchar_t* gs = nullptr);
		HRESULT CreateMeshFromObj(const wchar_t* pFileName);

		// 描画
		void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Vector3 eye);

		// プロパティ
		const std::vector<Triangle>& GetTriangles() { return m_triangles; }


	private:

		ID3D11InputLayout* m_pInputLayout;
		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		ID3D11GeometryShader* m_pGeometryShader;

		ID3D11Buffer* m_pConstBuffer[3];
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		std::vector<Triangle> m_triangles;		// 三角形ポリゴンデータ

		std::vector<DirectX::SimpleMath::Vector3> m_vertices;
		std::vector<uint16_t> m_indices;
		size_t m_indexCount;
		size_t m_vertexCount;

		float m_totalTime;
	};
}
