#pragma once
#include "Sprite.h"
class PostEffect : public Sprite
{
public:
	void Initialize(ID3D12Device* dev);
	void Draw(ID3D12GraphicsCommandList* cmdList_,
		ID3D12Device* dev);
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList_);
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList_);

private:
	static const float clearColor[4];

private:
	SpriteCommon spriteCommon;
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
};

