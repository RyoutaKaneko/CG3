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
	//メンバ関数
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
	//入力のポインタ
	Input* input = nullptr;
	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	Object3d* player = Object3d::Create();

	
	
	/////-----ゲームループの変数-----/////
	XMFLOAT3 playerVec;

	XMFLOAT3 move;

};