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
protected://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public://�萔
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;
public:
	static void StaticInitialize(ID3D12Device* device);
	static void SetCamera(ViewProjection* view_) { FbxObject3d::view = view_; }

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	/// �`��㏈��
	static void PostDraw();
	
	static void CreateGraphicsPipeline();
private://�ÓI�����o�ϐ�
	static ID3D12Device* device;
	static ViewProjection* view;
public://�T�u�N���X
	struct ConstBufferDataTransform {
		Matrix4 viewproj;
		Matrix4 world;
		Vector3 cameraPos;
	};
	//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin
	{
		Matrix4 bones[MAX_BONES];
	};
public://�����o�֐�
	void Initialize();

	void Update();

	void SetModel(FbxModel* model) { this->model = model; }

	void Draw(ViewProjection* viewProjection);

	const Vector3& GetPosition() const { return worldTransform.position_; }
	void SetPosition(const Vector3& position) { this->worldTransform.position_ = position; }
	// �I�u�W�F�N�g�̑傫��
	void SetScale(const Vector3& scale) { this->worldTransform.scale_ = scale; }
	const Vector3& GetScale() const { return worldTransform.scale_; }
	// �I�u�W�F�N�g�̉�]
	void SetRotation(const Vector3& rotation) { this->worldTransform.rotation_ = rotation; }
	const Vector3& GetRotation() const { return worldTransform.rotation_; }
	//�A�j���[�V�����Đ�
	void PlayAnimation();

protected://�����o�ϐ�
	ComPtr<ID3D12Resource> constBuffTransform;
	ComPtr<ID3D12Resource> constBuffSkin;
private:
	static ComPtr<ID3D12RootSignature> rootsignature;
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;

	WorldTransform worldTransform;
	FbxModel* model = nullptr;

	//�ϐ�
	FbxTime frameTime;
	FbxTime startTime;
	FbxTime endTime;
	FbxTime currentTime;
	bool isPlay = false;
};