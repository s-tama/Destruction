//
// Mesh.h
// 作成者: Tamamura Shuuki
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード -----------------------------------------------------------------
#include "Mesh.h"

#include <string>
#include <iostream>
#include <fstream>

#include "..\Common\DeviceResources.h"

#include "..\Utility\Macro.h"
#include "MeshRenderer.h"

#include "..\Utility\Time.h"


// usingディレクティブ -------------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


// 頂点インプットレイアウトを定義 ---------------------------------------------------------------
const D3D11_INPUT_ELEMENT_DESC Mesh::INPUT_LAYOUT[] =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0xffffffff, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


// メンバ関数の定義 --------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
Mesh::Mesh(GameObject* pGameObject):
	Component(pGameObject),
	m_pInputLayout(nullptr),
	m_pVertexShader(nullptr),
	m_pPixelShader(nullptr),
	m_pGeometryShader(nullptr),
	m_pConstBuffer{nullptr},
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr),
	m_totalTime(0)
{
	MeshRenderer::GetInstance()->AddMesh(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Mesh::~Mesh()
{
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pGeometryShader);
	SAFE_RELEASE(m_pConstBuffer[0]);
	SAFE_RELEASE(m_pConstBuffer[1]);
	SAFE_RELEASE(m_pConstBuffer[2]);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

/// <summary>
/// コンパイルされたファイルからシェーダを作成する
/// </summary>
/// <param name="vs">頂点シェーダ</param>
/// <param name="ps">ピクセルシェーダ</param>
/// <param name="gs">ジオメトリシェーダ</param>
HRESULT Mesh::CreateShaderFromCSO(const wchar_t* vs, const wchar_t* ps, const wchar_t* gs)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	HRESULT hr;

	// コンパイルされたデータ
	BinaryFile compiledVS = BinaryFile::Load(vs);
	
	// 入力レイアウトを作成
	
	UINT numElements = sizeof(INPUT_LAYOUT) / sizeof(INPUT_LAYOUT[0]);
	hr = device->CreateInputLayout(INPUT_LAYOUT, numElements, compiledVS.GetData(), compiledVS.GetSize(), &m_pInputLayout);

	//hr = device->CreateInputLayout(VertexPositionNormal::InputElements, VertexPositionNormal::InputElementCount, compiledVS.GetData(), compiledVS.GetSize(), &m_pInputLayout);
	//if (FAILED(hr)) return E_FAIL;

	// 頂点シェーダを作成
	hr = device->CreateVertexShader(compiledVS.GetData(), compiledVS.GetSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr)) return E_FAIL;

	// ジオメトリシェーダを作成
	if (gs != nullptr)
	{
		BinaryFile compiledGS = BinaryFile::Load(gs);
		hr = device->CreateGeometryShader(compiledGS.GetData(), compiledGS.GetSize(), nullptr, &m_pGeometryShader);
		if (FAILED(hr)) return E_FAIL;
	}

	// ピクセルシェーダを作成
	if (ps != nullptr)
	{
		BinaryFile compiledPS = BinaryFile::Load(ps);
		hr = device->CreatePixelShader(compiledPS.GetData(), compiledPS.GetSize(), nullptr, &m_pPixelShader);
		if (FAILED(hr)) return E_FAIL;
	}

	// 定数バッファを作成する
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = 0;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DEFAULT;
	// バッファ0
	cb.ByteWidth = sizeof(ConstBuffer0);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer[0]);
	if (FAILED(hr)) return E_FAIL;
	// バッファ1
	cb.ByteWidth = sizeof(ConstBuffer1);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer[1]);
	if (FAILED(hr)) return E_FAIL;
	// バッファ2
	cb.ByteWidth = sizeof(ConstBuffer2);
	hr = device->CreateBuffer(&cb, NULL, &m_pConstBuffer[2]);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

/// <summary>
/// OBJファイルからメッシュデータを作成する
/// </summary>
/// <param name="pFileName">.objファイル</param>
HRESULT Mesh::CreateMeshFromObj(const wchar_t* pFileName)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	//Vertex* vertices = new Vertex[0xffff];	// 頂点データ
	//Vector3 vertices[0xff][2];
	//uint16_t indices[0xffff][2];			// インデックスデータ
	std::vector<Vertex> vertices;	// 頂点データ配列
	std::vector<Vector3> positions;		// 頂点格納用
	std::vector<Vector3> normals;		// 法線格納用
	std::vector<uint16_t> indices;		// 頂点インデックス配列
	std::vector<uint16_t> vIndices;
	std::vector<uint16_t> nIndices;
	size_t vCount = 0;		// 格納した頂点数
	size_t vnCount = 0;		// 格納した法線数
	size_t iCount = 0;		// 格納したインデックス数

	// objファイル読み込み
	std::ifstream ifs(pFileName);

	std::string str;
	while (getline(ifs, str))
	{
		// 頂点情報
		if (str[0] == 'v')
		{
			// 頂点座標
			if (str[1] == ' ')
			{
				Vector3 v;
				sscanf_s(str.data(), "v  %f %f %f", &v.x, &v.y, &v.z);
				positions.push_back(v);
				vCount++;
			}
			// 法線
			else if (str[1] == 'n')
			{
				Vector3 vn;
				sscanf_s(str.data(), "vn  %f %f %f", &vn.x, &vn.y, &vn.z);
				normals.push_back(vn);
				vnCount++;
			}
		}
		// インデックス情報
		if (str[0] == 'f')
		{
			int va, vb, vc;
			int na, nb, nc;
			sscanf_s(str.data(), "f %d//%d %d//%d %d//%d", &va, &na, &vb, &nb, &vc, &nc);
			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する
			if (va != vb && va != vc && vb != vc)
			{
				Index index;

				// 0
				index.positions = va - 1;
				index.normals = na - 1;
				indices.push_back(index.positions);
				vIndices.push_back(va - 1);
				nIndices.push_back(na - 1);
				iCount++;
				// 1
				index.positions = vb - 1;
				index.normals = nb - 1;
				indices.push_back(index.positions);
				vIndices.push_back(vb - 1);
				nIndices.push_back(nb - 1);
				iCount++;
				// 2
				index.positions = vc - 1;
				index.normals = nc - 1;
				indices.push_back(index.positions);
				vIndices.push_back(vc - 1);
				nIndices.push_back(nc - 1);
				iCount++;
			}
		}
	}
	ifs.close();

	// 頂点データを作成する
	for (size_t i = 0; i < iCount / 3; i++)
	{
		// 一時頂点バッファ
		Vertex vertex[3];

		// 位置情報を作成
		Vector3 v0, v1, v2;
		v0 = positions[vIndices[i * 3 + 0]];
		v1 = positions[vIndices[i * 3 + 1]];
		v2 = positions[vIndices[i * 3 + 2]];
		if (v0 != v1 && v0 != v2 && v1 != v2)
		{
		}

		vertex[0].position = v0;
		vertex[1].position = v1;
		vertex[2].position = v2;

		// 法線を作成
		vertex[0].normal = normals[nIndices[i * 3 + 0]];
		vertex[1].normal = normals[nIndices[i * 3 + 1]];
		vertex[2].normal = normals[nIndices[i * 3 + 2]];

		// 頂点バッファに追加
		vertices.push_back(vertex[0]);
		vertices.push_back(vertex[1]);
		vertices.push_back(vertex[2]);
	}
	m_indexCount = iCount;
	m_vertexCount = vertices.size();

	// 頂点バッファの作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &vertices[0];
	device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);

	// インデックスバッファの作成
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(uint16_t) * iCount;
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;	// インデックスバッファ
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//InitData.pSysMem = &indices[0];
	//device->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);

	return S_OK;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
/// <param name="world">ワールド行列</param>
/// <param name="color">色</param>
void Mesh::Draw(Matrix view, Matrix projection, Vector3 eye)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto context = pDeviceResources->GetD3DDeviceContext();

	// このメッシュコンポーネントを所持しているオブジェクトのモデル行列
	Matrix world = m_pTransform->GetWorld();
	// ワールドから射影までの変換行列を作成
	Matrix wvp = world * view * projection;

	// シェーダの定数バッファに各種データを渡す
	// バッファ0
	ConstBuffer0 cb0;
	cb0.world = world.Transpose();
	cb0.view = view.Transpose();
	cb0.proj = projection.Transpose();
	cb0.wvp = wvp.Transpose();
	context->UpdateSubresource(m_pConstBuffer[0], 0, NULL, &cb0, 0, 0);
	// バッファ1
	ConstBuffer1 cb1;
	cb1.diffuse = Vector4(1, 1, 1, 1);
	cb1.ambient = Vector4(1, 1, 1, 1);
	cb1.specular = Vector4(1, 1, 1, 1);
	cb1.lightPos = Vector4(0, 1, -1, 1);
	cb1.cameraPos = Vector4(eye.x, eye.y, eye.z, 1);
	context->UpdateSubresource(m_pConstBuffer[1], 0, NULL, &cb1, 0, 0);
	// バッファ2
	ConstBuffer2 cb2;
	float time = Time::GetInstance()->GetTotalTime();
	cb2.time = Vector4(time / 20, time, time * 2, time * 3);
	cb2.sinTime = Vector4(sin(time / 20), sin(time), sin(time * 2), sin(time * 3));
	cb2.cosTime = Vector4(cos(time / 20), cos(time), cos(time * 2), cos(time * 3));
	context->UpdateSubresource(m_pConstBuffer[2], 0, NULL, &cb2, 0, 0);

	//使用するシェーダーの登録
	context->VSSetShader(m_pVertexShader, NULL, 0);
	context->PSSetShader(m_pPixelShader, NULL, 0);
	context->GSSetShader(m_pGeometryShader, NULL, 0);

	// 作成した定数バッファを、使用するシェーダに設定
	context->VSSetConstantBuffers(0, 1, &m_pConstBuffer[0]);
	context->GSSetConstantBuffers(0, 1, &m_pConstBuffer[0]);
	context->PSSetConstantBuffers(0, 1, &m_pConstBuffer[0]);
	context->VSSetConstantBuffers(1, 1, &m_pConstBuffer[1]);
	context->GSSetConstantBuffers(1, 1, &m_pConstBuffer[1]);
	context->PSSetConstantBuffers(1, 1, &m_pConstBuffer[1]);
	context->VSSetConstantBuffers(2, 1, &m_pConstBuffer[2]);
	context->GSSetConstantBuffers(2, 1, &m_pConstBuffer[2]);
	context->PSSetConstantBuffers(2, 1, &m_pConstBuffer[2]);
	
	// 頂点バッファをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	//context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// 入力レイアウトをセット
	context->IASetInputLayout(m_pInputLayout);

	// プリミティブ・トポロジーをセット
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// プリミティブをレンダリング
	//context->DrawIndexed(m_indexCount, 0, 0);
	context->Draw(m_vertexCount, 0);
}
