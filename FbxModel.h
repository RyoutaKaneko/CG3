#pragma once
#include <string>
#include <vector>
#include "Vector4.h"
#include "Matrix4.h"

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
private:
	//���f���̖��O
	std::string name;
	//�m�[�h�z��
	std::vector<Node> nodes;
};