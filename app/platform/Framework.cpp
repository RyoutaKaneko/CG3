#include "RLFramework.h"

void RLFramework::Run()
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

void RLFramework::Initialize()
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

	// ImGuiの初期化
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// ポストエフェクトの初期化
	postEffect_ = PostEffect::GetInstance();
	postEffect_->Initialize();

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	//レール描画静的初期化
	Line::StaticInitialize(dXCommon->GetDevice());

	// パーティクル静的初期化
	ParticleManager::StaticInitialize(dXCommon->GetDevice());

	// ビュープロジェクションの初期化
	ViewProjection::StaticInitialize(dXCommon->GetDevice());

}

void RLFramework::Update()
{
	// Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		// ゲームループを抜ける
		endRequest_ = true;
	}

	// 入力の更新
	input->Update();
}

void RLFramework::Finalize()
{
	// imguiの終了処理
	imGuiManager->Finalize();
	// imguiの解放
	delete imGuiManager;
	imGuiManager = nullptr;

	// WindowsAPIの終了処理
	winApp->Finalize();
	
	// DirectX解放
	dXCommon->fpsFixedFinalize();
	
}
