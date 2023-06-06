#pragma once
#include <string>
#include <vector>
#include "Vector4.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <DirectXTex.h>

//�m�[�h
struct Node {
	//���O
	std::string name;
	//�X�P�[��
	Vector4 scaling = { 1,1,1,0 };
	//��]�p
	Vector4 rotation = { 0,0,0,0 };
	//���[�J���ړ�
	Vector4 translation = { 0,0,0,1 };
	//���[�J���ό`�s��
	Matrix4 tranform;
	//�O���[�o���ό`�s��
	Matrix4 globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};

class FbxModel {
public:
	friend class FbxLoader;
//�T�u�N���X
public:
	struct VertexPosNormalUv {
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
	};
private:
	//���f���̖��O
	std::string name;
	//�m�[�h�z��
	std::vector<Node> nodes;
	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^
	std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X
	std::vector<unsigned int>indices;
	//�A���r�G���g
	Vector3 ambient = { 1,1,1 };
	//�f�B�t���[�Y
	Vector3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	DirectX::TexMetadata metaData = {};
	//�X�N���b�`�C���[�W
	DirectX::ScratchImage scratchImg = {};
};