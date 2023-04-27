#include "FbxLoader.h"
#include <cassert>
#include "Vector3.h"

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

	//モデル生成
	FbxModel* model = new FbxModel();
	model->name = modelName;
	//ノード数を取得
	int nodeCount = fbxScene->GetNodeCount();

	model->nodes.reserve(nodeCount);

	ParseNodeRecursive(model, fbxScene->GetRootNode());
	fbxScene->Destroy();
}

//ノード解析
void FbxLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent) {

	model->nodes.emplace_back();
	Node& node = model->nodes.back();
	//ノード名を取得
	node.name = fbxNode->GetName();

	//fbxノードのローカル移動情報
	FbxDouble3 rotation = fbxNode->LclRotation.Get();
	FbxDouble3 scaling = fbxNode->LclScaling.Get();
	FbxDouble3 translation = fbxNode->LclTranslation.Get();

	//形式変換して代入
	node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
	node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
	node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };

	//回転角をDegreeからラジアンに変換
	node.rotation.x = Matrix4::ConvertToRadian(node.rotation.x);
	node.rotation.y = Matrix4::ConvertToRadian(node.rotation.y);
	node.rotation.z = Matrix4::ConvertToRadian(node.rotation.z);

	//角行列の計算
	Matrix4 matScaling, matRotation, matTranslation;
	Matrix4 matRotX, matRotY, matRotZ;
	Vector3 scl = { node.scaling.x,node.scaling.y ,node.scaling.z };
	matScaling = Matrix4::identity();
	matScaling.scale(scl);
	matRotation = Matrix4::identity();
	matRotation *= matRotZ.rotateZ(Matrix4::ConvertToRadian(node.rotation.z));
	matRotation *= matRotX.rotateX(Matrix4::ConvertToRadian(node.rotation.x));
	matRotation *= matRotY.rotateY(Matrix4::ConvertToRadian(node.rotation.y));
	Vector3 trl = { node.translation.x,node.translation.y,node.translation.z };
	matTranslation = Matrix4::identity();
	matTranslation.translate(trl);

	//ローカル変換行列の計算
	node.tranform = Matrix4::identity();
	node.tranform *= matScaling;
	node.tranform *= matRotation;
	node.tranform *= matTranslation;

	//グローバル変形行列の計算
	node.globalTransform = node.tranform;
	if (parent) {
		node.parent = parent;
		//親の変形を乗算
		node.globalTransform *= parent->globalTransform;
	}

	//子ノードに対して再起呼び出し
	for (int i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i),&node);
	}


}

//後始末
void FbxLoader::Finalize() {
	//各種インスタンスの破棄
	fbxImporter->Destroy();
	fbxManager->Destroy();
}