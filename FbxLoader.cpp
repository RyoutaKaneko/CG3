#include "FbxLoader.h"
#include <cassert>

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
}

//��n��
void FbxLoader::Finalize() {
	//�e��C���X�^���X�̔j��
	fbxImporter->Destroy();
	fbxManager->Destroy();
}