#include "FbxLoader.h"
#include <cassert>
#include "Vector3.h"

//�ÓI�ϐ��̎���
const std::string FbxLoader::baseDirectory =
"Resources/";

//�C���X�^���X���擾
FbxLoader* FbxLoader::GetInstance() {
	static FbxLoader instance;
	return &instance;
}

//������
void FbxLoader::Initialize(ID3D12Device* device) {

	//�ď������`�F�b�N
	assert(fbxManager == nullptr);
	//�������烁���o�ϐ��ɑ��
	this->device = device;
	//FBX�}�l�[�W���[�̐���
	fbxManager = FbxManager::Create();
	//FBX�}�l�[�W���[�̓��o�͐ݒ�
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	//FBX�C���|�[�^�[�̐���
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

//���f���ǂݍ���
void FbxLoader::LoadModelFlomFile(const string& modelName) {
	const string directoryPath = baseDirectory + modelName + "/";
	const string fileName = modelName + ".fbx";
	//�A��
	const string fullPath = directoryPath + fileName;

	//�t�@�C�������w�肵�ēǂݍ���
	if (!fbxImporter->Initialize(fullPath.c_str(), -1, fbxManager->GetIOSettings())) {
		assert(0);
	}
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

	//�t�@�C�������V�[���ɃC���|�[�g
	fbxImporter->Import(fbxScene);

	//���f������
	FbxModel* model = new FbxModel();
	model->name = modelName;
	//�m�[�h�����擾
	int nodeCount = fbxScene->GetNodeCount();

	model->nodes.reserve(nodeCount);

	ParseNodeRecursive(model, fbxScene->GetRootNode());
	fbxScene->Destroy();
}

//�m�[�h���
void FbxLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent) {

	model->nodes.emplace_back();
	Node& node = model->nodes.back();
	//�m�[�h�����擾
	node.name = fbxNode->GetName();

	//fbx�m�[�h�̃��[�J���ړ����
	FbxDouble3 rotation = fbxNode->LclRotation.Get();
	FbxDouble3 scaling = fbxNode->LclScaling.Get();
	FbxDouble3 translation = fbxNode->LclTranslation.Get();

	//�`���ϊ����đ��
	node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
	node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
	node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };

	//��]�p��Degree���烉�W�A���ɕϊ�
	node.rotation.x = Matrix4::ConvertToRadian(node.rotation.x);
	node.rotation.y = Matrix4::ConvertToRadian(node.rotation.y);
	node.rotation.z = Matrix4::ConvertToRadian(node.rotation.z);

	//�p�s��̌v�Z
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

	//���[�J���ϊ��s��̌v�Z
	node.tranform = Matrix4::identity();
	node.tranform *= matScaling;
	node.tranform *= matRotation;
	node.tranform *= matTranslation;

	//�O���[�o���ό`�s��̌v�Z
	node.globalTransform = node.tranform;
	if (parent) {
		node.parent = parent;
		//�e�̕ό`����Z
		node.globalTransform *= parent->globalTransform;
	}

	//�q�m�[�h�ɑ΂��čċN�Ăяo��
	for (int i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i),&node);
	}


}

//��n��
void FbxLoader::Finalize() {
	//�e��C���X�^���X�̔j��
	fbxImporter->Destroy();
	fbxManager->Destroy();
}