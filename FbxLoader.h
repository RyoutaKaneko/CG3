#pragma once
#include "fbxsdk.h"

#include "d3d12.h"
#include "d3dx12.h"
#include <string>
#include "FbxModel.h"
#include "Matrix4.h"

class FbxLoader {
	//�G�C���A�X
private:
	using string = std::string;

public:
	//�V���O���g���C���X�^���X�̎擾
	//<return>�C���X�^���X</return>
	static FbxLoader* GetInstance();

	//������
	void Initialize(ID3D12Device* device);

	//fbx�t�@�C�����烂�f���ǂݍ���
	void LoadModelFlomFile(const string& modelName);

	//�m�[�h���
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);

	//��n��
	void Finalize();

private:
	//D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	//FBX�}�l�[�W���[
	FbxManager* fbxManager = nullptr;
	//FBX�C���|�[�^�[
	FbxImporter* fbxImporter = nullptr;

private:
	//private�ȃR���X�g���N�^
	FbxLoader() = default;
	//private�ȃf�X�g���N�^
	~FbxLoader() = default;
	//�R�s�[�R���X�g���N�^���֎~
	FbxLoader(const FbxLoader& obj) = delete;
	//�R�s�[������Z�q���֎~
	void operator=(const FbxLoader& obj) = delete;

public:
	static const string baseDirectory;
};