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
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff;
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
};

