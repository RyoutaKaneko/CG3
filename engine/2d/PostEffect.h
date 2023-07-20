#pragma once
#include "Sprite.h"
class PostEffect
{
public:
	//������
	void Initialize(ID3D12Device* dev);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList_);
	//�`��O��
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList_);
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList_);
	//�p�C�v���C������
	void CreateGraphicsPipelineState();


private:
	static const float clearColor[4];

private:
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
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C��
	ComPtr<ID3D12PipelineState> pipelinestate;
	//cmdList
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	//Device
	ComPtr<ID3D12Device> device;
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		Vector4 color; // �F (RGBA)
		Matrix4 mat; //���W
	};
	Vector4 color = { 1,1,1,1 }; // �F (RGBA)
	Matrix4 mat; //���W
};

