#include "FbxLoader.h"
#include <cassert>

//静的変数の実体
const std::string FbxLoader::baseDirectory =
"Resources/";

//インスタンスを取得
FbxLoader* FbxLoader::GetInstance() {
	static FbxLoader instance;
	return &instance;
}

//初期化
void FbxLoader::Initialize(ID3D12Device* device) {

	//再初期化チェック
	assert(fbxManager == nullptr);
	//引数からメンバ変数に代入
	this->device = device;
	//FBXマネージャーの生成
	fbxManager = FbxManager::Create();
	//FBXマネージャーの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	//FBXインポーターの生成
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

//モデル読み込み
void FbxLoader::LoadModelFlomFile(const string& modelName) {
	const string directoryPath = baseDirectory + modelName + "/";
	const string fileName = modelName + ".fbx";
	//連結
	const string fullPath = directoryPath + fileName;

	//ファイル名を指定して読み込み
	if (!fbxImporter->Initialize(fullPath.c_str(), -1, fbxManager->GetIOSettings())) {
		assert(0);
	}
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

	//ファイル情報をシーンにインポート
	fbxImporter->Import(fbxScene);
}

//後始末
void FbxLoader::Finalize() {
	//各種インスタンスの破棄
	fbxImporter->Destroy();
	fbxManager->Destroy();
}