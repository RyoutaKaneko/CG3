#pragma once
#include "fbxsdk.h"

#include "d3d12.h"
#include "d3dx12.h"
#include <string>
#include "FbxModel.h"
#include "Matrix4.h"

class FbxLoader {
	//エイリアス
private:
	using string = std::string;

public:
	//シングルトンインスタンスの取得
	//<return>インスタンス</return>
	static FbxLoader* GetInstance();

	//初期化
	void Initialize(ID3D12Device* device);

	//fbxファイルからモデル読み込み
	void LoadModelFlomFile(const string& modelName);

	//ノード解析
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);

	//後始末
	void Finalize();

private:
	//D3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポーター
	FbxImporter* fbxImporter = nullptr;

private:
	//privateなコンストラクタ
	FbxLoader() = default;
	//privateなデストラクタ
	~FbxLoader() = default;
	//コピーコンストラクタを禁止
	FbxLoader(const FbxLoader& obj) = delete;
	//コピー代入演算子を禁止
	void operator=(const FbxLoader& obj) = delete;

public:
	static const string baseDirectory;
};