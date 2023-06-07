#include "RideLight.h"

void RideLight::Initialize()
{
	// 基底クラスの初期化
	RLFramework::Initialize();

	dXCommon = DirectXCommon::GetInstance();

	// ゲームシーンの生成と初期化
	scene_ = new GamePlayScene();
	scene_->Initialize(spriteCommon);
}

void RideLight::Update()
{
	// 基底クラスの更新処理
	RLFramework::Update();

	// ImGui受付開始
	imGuiManager->Begin();

	// ゲームシーンの更新
	scene_->Update(spriteCommon);

	// ImGui受付終了
	imGuiManager->End();
}

void RideLight::Draw()
{
#pragma region ゲームシーン描画
	// レンダーテクスチャの前処理
	postEffect_->PreDrawScene(dXCommon->GetCommandList());

	//=== ゲームシーン描画 ===//
	scene_->Draw(spriteCommon);

	// レンダーテクスチャの後処理
	postEffect_->PostDrawScene(dXCommon->GetCommandList());
#pragma endregion

#pragma region 描画
	// 描画前処理
	dXCommon->PreDraw();
	
	//=== ポストエフェクトの描画 ===//
	postEffect_->Draw(dXCommon->GetCommandList());

	//=== ImGui描画 ===//
	imGuiManager->Draw(dXCommon);

	// 描画後処理
	dXCommon->PostDraw();
#pragma endregion
}

void RideLight::Finalize()
{
	// ゲームシーンの終了処理
	scene_->Finalize();
	// ゲームシーンの解放
	delete scene_;

	// 基底クラスの終了処理
	RLFramework::Finalize();
}
