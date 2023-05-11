#define DIRECTINPUT_VERSION    0x0800 //DirectInput�̃o�[�W�����w��
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

#pragma region ��ՃV�X�e���̏�����
	// WindowsAPI�̏�����
	WinApp* winApp = nullptr;
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	DirectXCommon* dxCommon = nullptr;
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	// ���͂̏�����
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(winApp);
	//�X�v���C�g
	SpriteCommon spriteCommon;
	//�Q�[���V�[��
	GameScene* gameScene = nullptr;
	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// �r���[�v���W�F�N�V�����̏�����
	ViewProjection::StaticInitialize(dxCommon->GetDevice());
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice());
	//fbx�ėp������
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//
	FbxObject3d::StaticInitialize(dxCommon->GetDevice());
#pragma endregion ��ՃV�X�e���̏�����

	//�Q�[���V�[��
	gameScene = new GameScene();
	gameScene->Initialize(spriteCommon);
///-------------�Q�[�����[�v---------------///
	while (true)
	{
#pragma region ��ՃV�X�e���̍X�V

		//Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage())
		{
			//�Q�[�����[�v�𔲂���
			break;
		}

		gameScene->Update();

#pragma endregion ��ՃV�X�e���̍X�V
		
		dxCommon->PreDraw();
		gameScene->Draw();
		dxCommon->PostDraw();
	}

#pragma region �ŏ��̃V�[���̏I��

	//�����Ƀ|���S���̏���������������

#pragma endregion �ŏ��̃V�[���̏I��

#pragma region ��ՃV�X�e���̏I��

	//3D�I�u�W�F�N�g���
	delete gameScene;
	FbxLoader::GetInstance()->Finalize();

	//WindowsAPI�̏I������
	winApp->Finalize();

#pragma endregion ��ՃV�X�e���̏I��

	return 0;
}