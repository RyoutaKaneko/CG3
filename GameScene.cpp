#include "GameScene.h"

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete input;
	delete player;
}

///-----変数の初期化-----///
void GameScene::Initialize(WinApp* winApp, DirectXCommon* dxCommon) {
	//入力の初期化
	input = new Input();
	input->Initialize(winApp);
	//スプライトの初期化
	sprite->SetSize(XMFLOAT2(256, 128));
	sprite->Initialize(dxCommon, WinApp::window_width, WinApp::window_height);
	sprite->LoadTexture(1, L"Resources/wood.png", dxCommon);
	player->SetPosition(XMFLOAT3(0, 0, -25));
	player->SetEye(XMFLOAT3(0, 3, -30));
	player->SetTarget(XMFLOAT3(0, 0, -15));
	//乱数
	srand(time(NULL));
}

///-----更新処理-----///
void GameScene::Update() {
	input->Update();

	
		///--------------更新処理を記述-------------///
		//毎ループ初期化
		playerVec = { 0.0f,0.0f,0.0f };
		move = { 0,0,0 };

		//移動

		if (input->PushKey(DIK_A)) {
			if (player->GetPositionX() > -4) {
				playerVec.x = -0.4f;
				player->SetPosition(AddXMFLOAT3(player->GetPosition(), playerVec));
			}
		}
		else if (input->PushKey(DIK_D)) {
			if (player->GetPositionX() < 4) {
				playerVec.x = 0.4f;
				player->SetPosition(AddXMFLOAT3(player->GetPosition(), playerVec));
			}
		}
		else if (input->PushKey(DIK_W)) {
			playerVec.z = 0.4f;
			player->SetPosition(AddXMFLOAT3(player->GetPosition(), playerVec));
		}
		else if (input->PushKey(DIK_S)) {
			playerVec.z = -0.4f;
			player->SetPosition(AddXMFLOAT3(player->GetPosition(), playerVec));
		}


		player->Update();
		
}

void GameScene::Draw(DirectXCommon* dxCommon) {
	//描画前処理
	dxCommon->PreDraw();

#pragma region 最初のシーンの描画
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	player->Draw();

	//3Dオブジェクト描画前処理
	Object3d::PostDraw();

	//ここにポリゴンなどの描画処理を書く
	
		sprite->Draw(dxCommon);
	

#pragma endregion 最初のシーンの描画
	// 描画後処理
	dxCommon->PostDraw();
}

XMFLOAT3 GameScene::AddXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
	XMFLOAT3 tmp;
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	tmp.z = a.z + b.z;
	return tmp;
}

XMFLOAT3 GameScene::SubXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) {
	XMFLOAT3 tmp;
	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;
	return tmp;
}

int GameScene::CheckHit(Object3d* object) {
	//弾座標
	float olx = object->GetPositionX() - object->GetScaleX();
	float orx = object->GetPositionX() + object->GetScaleX();
	float oty = object->GetPositionY() + object->GetScaleY();
	float oby = object->GetPositionY() - object->GetScaleY();
	float ofz = object->GetPositionZ() - object->GetScaleZ();
	float obz = object->GetPositionZ() + object->GetScaleZ();
	//プレイヤー座標
	float plx = player->GetPositionX() - player->GetScaleX();
	float prx = player->GetPositionX() + player->GetScaleX();
	float pty = player->GetPositionY() + player->GetScaleY();
	float pby = player->GetPositionY() - player->GetScaleY();
	float pfz = player->GetPositionZ() - player->GetScaleZ();
	float pbz = player->GetPositionZ() + player->GetScaleZ();

	if (olx < prx && plx < orx) {
		if (oby < pty && pby < oty) {
			if (ofz < pbz && pfz < ofz) {
				return true;
			}
		}
	}
}