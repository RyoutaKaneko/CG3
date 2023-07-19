#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Input.h"
#include "time.h"
#include <random>
#include "Model.h"
#include "ViewProjection.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "FbxObject3d.h"
#include "FbxModel.h"
#include "PostEffect.h"

class GameScene {
public:
	//メンバ関数
	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon = nullptr;
	WinApp* winApp = nullptr;
	//入力のポインタ
	Input* input = nullptr;
	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite wood;
	Sprite reimu;
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	Model* playerModel = nullptr;
	Object3d* player = nullptr;
	Model* testModel = nullptr;
	Object3d* test = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* particle_ = nullptr;
	ParticleManager* pm_ = nullptr;

	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* obj = nullptr;
	FbxModel* cubeModel = nullptr;
	FbxObject3d* cube = nullptr;

};