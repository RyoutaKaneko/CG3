#include "Framework.h"

void Framework::Run()
{
	// ゲームの初期化
	Initialize();

	while (true) // ゲームループ 
	{
		// 毎フレーム更新
		Update();

		// 終了リクエストが来たらループを抜ける
		if (IsEndRequest()) {
			// ゲームループを抜ける
			break;
		}

		// 描画
		Draw();
	}

	// ゲームの終了
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPIの初期化
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectXの初期化
	dXCommon = DirectXCommon::GetInstance();
	dXCommon->Initialize(winApp);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize(winApp);
	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// ビュープロジェクションの初期化
	ViewProjection::StaticInitialize(dXCommon->GetDevice());
	// パーティクル静的初期化
	ParticleManager::StaticInitialize(dXCommon->GetDevice());
	//fbx汎用初期化
	FbxLoader::GetInstance()->Initialize(dXCommon->GetDevice());
	//
	FbxObject3d::StaticInitialize(dXCommon->GetDevice());

	post = new PostEffect();
	spriteCommon = post->SpriteCommonCreate(dXCommon->GetDevice());
	post->SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/white1x1.png", dXCommon->GetDevice());
	postEffect.SpriteCreate(dXCommon->GetDevice());
	postEffect.SetTexNumber(0);
	postEffect.SetPosition(Vector3(0, 100, 0));
	postEffect.SetScale(Vector2(256 * 1, 256 * 1));
	postEffect.SpriteTransferVertexBuffer();
	postEffect.SpriteUpdate(spriteCommon);

#pragma endregion 基盤システムの初期化

	//ゲームシーン
	gameScene = new GameScene();
	gameScene->Initialize();
}

void Framework::Update()
{
	// Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		// ゲームループを抜ける
		endRequest_ = true;
	}
	gameScene->Update();
	// 入力の更新
	/*input->Update();*/
}

void Framework::Draw()
{
#pragma region ゲームシーン描画


#pragma endregion

#pragma region 描画
	// 描画前処理
	dXCommon->PreDraw();
	//=== ゲームシーン描画 ===//
	gameScene->Draw();
	postEffect.Draw(dXCommon->GetCommandList(), spriteCommon, dXCommon->GetDevice());
	// 描画後処理
	dXCommon->PostDraw();
#pragma endregion
}

void Framework::Finalize()
{
	delete gameScene;
	FbxLoader::GetInstance()->Finalize();
	// WindowsAPIの終了処理
	winApp->Finalize();

}
