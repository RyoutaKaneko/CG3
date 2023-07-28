#pragma once

#include <Windows.h>
#include <D3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include <DirectXTex.h>
#include <wrl.h>
#include <array>
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

#include "DirectXCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;


struct VertexPosUv {
	Vector3 pos;
	Vector2 uv;
};

// �p�C�v���C���Z�b�g
struct PipelineSet {
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
};

//�X�v���C�g�̋��ʃf�[�^
struct SpriteCommon {

	//�e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

	//�p�C�v���C���Z�b�g
	PipelineSet pipelineSet;

	// �ˉe�s��
	Matrix4 matProjection{};

	//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`���\�[�X(�e�N�X�`���o�b�t�@)�̔z��
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];

};

class Sprite
{
public:
	/// <summary>
	/// �X�v���C�g����
	/// </summary>
	void SpriteCreate(ID3D12Device* dev);

	/// <summary>
	/// �X�v���C�g���ʃf�[�^����
	/// </summary>
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev);

	/// <summary>
	/// �X�v���C�g���ʃO���t�B�b�N�X�R�}���h�̃Z�b�g
	/// </summary>
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g�P�̕`��
	/// </summary>
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev);
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev, float alpha_);
	void DrawC(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev, Vector4 color_);

	/// <summary>
	/// �X�v���C�g�P�̍X�V
	/// </summary>
	void SpriteUpdate(const SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	/// </summary>
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);

	/// <summary>
	/// �X�v���C�g�P�̒��_�o�b�t�@�̓]��
	/// </summary>
	void SpriteTransferVertexBuffer();

	void SetTexNumber(UINT texnumber) { this->texNumber = texnumber; }
	void SetPosition(Vector3 position) { this->position = position; }
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetRotation(float rotate) { this->rotation = rotation; }
	const Vector3& GetPosition() const { return position; }

	void Release();


	void SetAlpha(float alpha_);
	void SetColor(Vector4 color_);

	float GetRotation() { return rotation; }

public:
	void SetPiplineSet(PipelineSet piplineSet);

	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

protected:
	struct ConstBufferData {
		Vector4 color; // �F (RGBA)
		Matrix4 mat; //���W
	};

	UINT texNumber = 0;

	DirectXCommon* dXCommon = nullptr;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	ComPtr<ID3D12Resource> constBuff;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	// ���[���h�s��
	Matrix4 matWorld;
	// ���W�A�傫�� ��]
	Vector3 position = { 0,0,0 };
	Vector2 scale = { 1,1 };
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };

	// Z�����̉�]
	float rotation = 0.0f;
};
