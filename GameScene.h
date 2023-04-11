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
	//メンバ関数
	GameScene();

	~GameScene();

	void Initialize(SpriteCommon& spriteCommon);

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
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	Model* playerModel = nullptr;
	Object3d* player = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	

};