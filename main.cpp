#define DIRECTINPUT_VERSION    0x0800 //DirectInputのバージョン指定
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Object3d.h"

#include<windows.h>
#include<cassert>
#include<vector>
#include<string>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<dinput.h>
#include<DirectXTex.h>
#include "GameScene.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region 基盤システムの初期化
	// WindowsAPIの初期化
	WinApp* winApp = nullptr;
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectXの初期化
	DirectXCommon* dxCommon = nullptr;
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	// 入力の初期化
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(winApp);
	//スプライト
	SpriteCommon spriteCommon;
	//ゲームシーン
	GameScene* gameScene = nullptr;
	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// ビュープロジェクションの初期化
	ViewProjection::StaticInitialize(dxCommon->GetDevice());
	// パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice());
	//fbx汎用初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//
	FbxObject3d::StaticInitialize(dxCommon->GetDevice());
#pragma endregion 基盤システムの初期化

	//ゲームシーン
	gameScene = new GameScene();
	gameScene->Initialize(spriteCommon);
///-------------ゲームループ---------------///
	while (true)
	{
#pragma region 基盤システムの更新

		//Windowsのメッセージ処理
		if (winApp->ProcessMessage())
		{
			//ゲームループを抜ける
			break;
		}

		gameScene->Update();

#pragma endregion 基盤システムの更新
		
		dxCommon->PreDraw();
		gameScene->Draw();
		dxCommon->PostDraw();
	}

#pragma region 最初のシーンの終了

	//ここにポリゴンの初期化処理を書く

#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了

	//3Dオブジェクト解放
	delete gameScene;
	FbxLoader::GetInstance()->Finalize();

	//WindowsAPIの終了処理
	winApp->Finalize();

#pragma endregion 基盤システムの終了

	return 0;
}