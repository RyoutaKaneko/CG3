#include "GameScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

GameScene::GameScene() {

}
GameScene::~GameScene() {
	delete player;
}

///-----変数の初期化-----///
void GameScene::Initialize() {
	//基盤
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();

	//player
	playerModel = Model::LoadFromOBJ("triangle_mat");
	player = Object3d::Create();
	player->SetModel(playerModel);
	player->SetPosition(Vector3(0, 0, 0));
	//test
	testModel = Model::LoadFromOBJ("ironSphere");
	test = Object3d::Create();
	test->SetModel(testModel);
	test->SetPosition(Vector3(-3, 0, -15));
	//カメラ
	viewProjection = new ViewProjection;
	viewProjection->Initialize();
	viewProjection->eye = { 0, 3, -15 };
	viewProjection->target = { 0, 0, 0 };

	xmViewProjection = new XMViewProjection;

	//FbxObjectの静的初期化
	//カメラをセット
	FbxObject3d::SetCamera(viewProjection);
	//グラフィックスパイプラインを初期化
	FbxObject3d::CreateGraphicsPipeline();

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());
	sprite->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	sprite->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/reimu.png", dxCommon->GetDevice());

	//木の画像
	wood.SpriteCreate(dxCommon->GetDevice());
	wood.SetTexNumber(0);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer();
	wood.SpriteUpdate(spriteCommon_);

	////霊夢の画像
	reimu.SpriteCreate(dxCommon->GetDevice());
	reimu.SetTexNumber(1);
	reimu.SetPosition(Vector3(1100, 0, 0));
	reimu.SetScale(Vector2(128 * 1, 128 * 1));
	reimu.SpriteTransferVertexBuffer();
	reimu.SpriteUpdate(spriteCommon_);

	//パーティクル初期化
	particle = Particle::LoadParticleTexture("wood.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("reimu.png");
	pm = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm->SetParticleModel(particle);
	pm_->SetParticleModel(particle_);
	//カメラをセット
	pm->SetXMViewProjection(xmViewProjection);
	pm_->SetXMViewProjection(xmViewProjection);

	//モデル名を指定して読み込み
	obj = new FbxObject3d;
	model = FbxLoader::GetInstance()->LoadModelFlomFile("boneTest");
	obj->SetModel(model);
	obj->Initialize();
	obj->SetPosition(Vector3(0, 0, 0));
	obj->SetScale(Vector3(1, 1, 1));
	obj->SetRotation(Vector3(0, 90, 0));

	cube = new FbxObject3d;
	cubeModel = FbxLoader::GetInstance()->LoadModelFlomFile("cube");
	cube->SetModel(cubeModel);
	cube->Initialize();
	cube->SetPosition(Vector3(1, 0, -8));
	cube->SetScale(Vector3((float)0.01, (float)0.01, (float)0.01));
}

///-----更新処理-----///
void GameScene::Update() {
	input->Update();

	/*wood.SetRotation(wood.GetRotation() + 0.1f);
	wood.SpriteTransferVertexBuffer();
	wood.SpriteUpdate(spriteCommon_);*/
	//player移動
	if (input->PushKey(DIK_W)) {
		player->SetPosition(player->GetPosition() + Vector3(0, 0, 0.1f));
	}
	if (input->PushKey(DIK_A)) {
		player->SetPosition(player->GetPosition() + Vector3(-0.1f, 0, 0));
	}
	if (input->PushKey(DIK_D)) {
		player->SetPosition(player->GetPosition() + Vector3(0.1f, 0, 0));
	}
	if (input->PushKey(DIK_S)) {
		player->SetPosition(player->GetPosition() + Vector3(0, 0, -0.1f));
	}

	//パーティクル
	if (input->PushKey(DIK_SPACE))
	{
		pm->Fire(particle, 30, 0.2f, 0, 2, { 8.0f, 0.0f });
		pm_->Fire(particle_, 30, 0.2f, 0, 1, { 8.0f, 0.0f });
	}

	//カメラ 
	if (input->PushKey(DIK_RIGHT)) {
		viewProjection->eye += Vector3(0.1f, 0, 0);
	}
	if (input->PushKey(DIK_LEFT)) {
		viewProjection->eye += Vector3(-0.1f, 0, 0);
	}
	if (input->PushKey(DIK_UP)) {
		viewProjection->eye += Vector3(0, 0, 0.1f);
	}
	if (input->PushKey(DIK_DOWN)) {
		viewProjection->eye += Vector3(0, 0, -0.1f);
	}
	//視点移動
	if (input->PushKey(DIK_J)) {
		viewProjection->target += Vector3(-0.1f, 0, 0);
	}
	if (input->PushKey(DIK_L)) {
		viewProjection->target += Vector3(0.1f, 0, 0);
	}
	if (input->PushKey(DIK_I)) {
		viewProjection->target += Vector3(0, 0.1f, 0);
	}
	if (input->PushKey(DIK_K)) {
		viewProjection->target += Vector3(0, -0.1f, 0);
	}


	//更新
	player->Update();
	test->Update();
	viewProjection->UpdateMatrix();
	pm->Update();
	pm_->Update();
	obj->Update();
	cube->Update();
}

void GameScene::Draw() {
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	//player->Draw(viewProjection);
	//test->Draw(viewProjection);

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	FbxObject3d::PreDraw(dxCommon->GetCommandList());

	obj->Draw(viewProjection);
	cube->Draw(viewProjection);

	// 3Dオブジェクト描画後処理
	FbxObject3d::PostDraw();

#pragma endregion

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル
	//pm->Draw();
	//pm_->Draw();

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	//Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);
	sprite->SpriteCommonBeginDraw(dxCommon->GetCommandList(), spriteCommon_);

	/////=== スプライト描画 ===///
	wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	reimu.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());

	// スプライト描画後処理
	//Sprite::PostDraw();
}