#pragma once
#include "Sprite.h"
class PostEffect : public Sprite
{
public:
	void Initialize(ID3D12Device* dev);
	void Draw(ID3D12GraphicsCommandList* cmdList_,
		ID3D12Device* dev);

private:
	SpriteCommon spriteCommon;
	ComPtr<ID3D12Resource> texBuff;
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
};

