#include "GameScene.h"

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete player;
}

///-----変数の初期化-----///
void GameScene::Initialize(SpriteCommon& spriteCommon) {
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	
	//player
	playerModel = Model::LoadFromOBJ("triangle_mat");
	player = Object3d::Create();
	player->SetModel(playerModel);
	player->SetPosition(Vector3(0, 0, -25));
	//test
	testModel = Model::LoadFromOBJ("ironSphere");
	test = Object3d::Create();
	test->SetModel(testModel);
	test->SetPosition(Vector3(-3, 0, -15));
	//カメラ
	viewProjection = new ViewProjection;
	viewProjection->Initialize();
	viewProjection->eye = { 0, 3, -30 };
	viewProjection->target = { 0, 0, -15 };

	xmViewProjection = new XMViewProjection;

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dxCommon->GetDevice());

	//木の画像
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, spriteCommon, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//霊夢の画像
	reimu.LoadTexture(spriteCommon_, 1, L"Resources/reimu.png", dxCommon->GetDevice());
	reimu.SetColor(Vector4(1, 1, 1, 1));
	reimu.SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	reimu.SetPosition(Vector3(1100, 0, 0));
	reimu.SetScale(Vector2(128 * 1, 128 * 1));
	reimu.SetRotation(0.0f);
	reimu.SpriteTransferVertexBuffer(reimu, spriteCommon, 1);
	reimu.SpriteUpdate(reimu, spriteCommon_);

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
}

///-----更新処理-----///
void GameScene::Update() {
	input->Update();

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
}

void GameScene::Draw() {
#pragma region 3Dオブジェクト描画

// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	player->Draw(viewProjection);
	test->Draw(viewProjection);

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル
	pm->Draw();
	pm_->Draw();

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///
	wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);
	reimu.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), reimu.vbView);

	// スプライト描画後処理
	Sprite::PostDraw();
}