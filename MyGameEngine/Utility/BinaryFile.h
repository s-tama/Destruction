//
// BinaryFile.h
//
#pragma once


// ヘッダーファイルのインクルード -------------------------------------------------------------------
#include <memory>


// クラスの定義 --------------------------------------------------------------------------------
namespace MyLibrary
{
	/// <summary>
	/// バイナリファイルを扱うクラス
	/// </summary>
	class BinaryFile
	{
	public:

		// コンストラクタ
		BinaryFile();
		BinaryFile(BinaryFile&& in);

		// ファイルの読み込み
		static BinaryFile Load(const wchar_t* pFileName);

		// プロパティメソッド
		char* GetData() { return m_data.get(); }
		unsigned int GetSize() { return m_size; }


	private:

		std::unique_ptr<char[]> m_data;		// データ
		unsigned int m_size;				// サイズ
	};
}
