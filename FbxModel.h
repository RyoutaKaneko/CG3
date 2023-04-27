#pragma once
#include <string>
#include <vector>
#include "Vector4.h"
#include "Matrix4.h"

//ノード
struct Node {
	//名前
	std::string name;
	//スケール
	Vector4 scaling = { 1,1,1,0 };
	//回転角
	Vector4 rotation = { 0,0,0,0 };
	//ローカル移動
	Vector4 translation = { 0,0,0,1 };
	//ローカル変形行列
	Matrix4 tranform;
	//グローバル変形行列
	Matrix4 globalTransform;
	//親ノード
	Node* parent = nullptr;
};

class FbxModel {
public:
	friend class FbxLoader;
private:
	//モデルの名前
	std::string name;
	//ノード配列
	std::vector<Node> nodes;
};