#pragma once
#include "Sprite.h"
class PostEffect
{
public:
	//初期化
	void Initialize(ID3D12Device* dev);
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList_);
	//描画前後
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList_);
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList_);
	//パイプライン生成
	void CreateGraphicsPipelineState();


private:
	static const float clearColor[4];

private:
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	//パイプライン
	ComPtr<ID3D12PipelineState> pipelinestate;
	//cmdList
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	//Device
	ComPtr<ID3D12Device> device;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//定数バッファ用データ構造体
	struct ConstBufferData {
		Vector4 color; // 色 (RGBA)
		Matrix4 mat; //座標
	};
	Vector4 color = { 1,1,1,1 }; // 色 (RGBA)
	Matrix4 mat; //座標
};

