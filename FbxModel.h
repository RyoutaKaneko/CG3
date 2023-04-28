#pragma once
#include <string>
#include <vector>
#include "Vector4.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <DirectXTex.h>

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
//サブクラス
public:
	struct VertexPosNormalUv {
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
	};
private:
	//モデルの名前
	std::string name;
	//ノード配列
	std::vector<Node> nodes;
	//メッシュを持つノード
	Node* meshNode = nullptr;
	//頂点データ
	std::vector<VertexPosNormalUv> vertices;
	//頂点インデックス
	std::vector<unsigned int>indices;
	//アンビエント
	Vector3 ambient = { 1,1,1 };
	//ディフューズ
	Vector3 diffuse = { 1,1,1 };
	//テクスチャメタデータ
	DirectX::TexMetadata metaData = {};
	//スクラッチイメージ
	DirectX::ScratchImage scratchImg = {};
};