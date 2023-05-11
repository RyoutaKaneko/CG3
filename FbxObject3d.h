#pragma once

#include "FbxModel.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxObject3d {
protected://エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static void StaticInitialize(ID3D12Device* device);
	static void SetCamera(ViewProjection* view_) { FbxObject3d::view = view_; }

	/// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	/// 描画後処理
	static void PostDraw();
	
	static void CreateGraphicsPipeline();
private://静的メンバ変数
	static ID3D12Device* device;
	static ViewProjection* view;
public://サブクラス
	struct ConstBufferDataTransform {
		Matrix4 viewproj;
		Matrix4 world;
		Vector3 cameraPos;
	};
public://メンバ関数
	void Initialize();

	void Update();

	void SetModel(FbxModel* model) { this->model = model; }

	void Draw(ID3D12GraphicsCommandList* cmdList);
protected://メンバ変数
	ComPtr<ID3D12Resource> constBuffTransform;
private:
	static ComPtr<ID3D12RootSignature> rootsignature;
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;

	WorldTransform* worldTransform = nullptr;
	FbxModel* model = nullptr;
};