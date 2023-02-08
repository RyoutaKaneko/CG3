#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "time.h"
#include <random>
using namespace DirectX;

class GameScene {
public:
	//�����o�֐�
	GameScene();

	~GameScene();

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Update();

	void Draw(DirectXCommon* dxCommon);

	XMFLOAT3 AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

	XMFLOAT3 SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b);

	int CheckHit(Object3d* object);

	void Reset();

	void Sporn(Object3d* object);

private:
	//���͂̃|�C���^
	Input* input = nullptr;
	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	//�I�u�W�F�N�g�̃|�C���^
	//3D�I�u�W�F�N�g����
	Object3d* player = Object3d::Create();

	
	
	/////-----�Q�[�����[�v�̕ϐ�-----/////
	XMFLOAT3 playerVec;

	XMFLOAT3 move;

};