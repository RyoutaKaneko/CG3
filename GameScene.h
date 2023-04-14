#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "time.h"
#include <random>
#include "Model.h"
#include "ViewProjection.h"

class GameScene {
public:
	//�����o�֐�
	GameScene();

	~GameScene();

	void Initialize(SpriteCommon& spriteCommon);

	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon = nullptr;
	WinApp* winApp = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;
	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite wood;
	//�I�u�W�F�N�g�̃|�C���^
	//3D�I�u�W�F�N�g����
	Model* playerModel = nullptr;
	Object3d* player = nullptr;
	//�J����
	ViewProjection* viewProjection = nullptr;
	

};