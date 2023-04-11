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

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

using namespace Microsoft::WRL;

//// �E�B���h�E�v���V�[�W��
//LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
//	switch (msg)
//	{
//		//�E�B���h�E���j�����ꂽ
//	case WM_DESTROY:
//		//OS�ɑ΂��āA�A�v���̏I����`����
//		PostQuitMessage(0);
//		return 0;
//	}
//
//	//�W���̃��b�Z�[�W�������s��
//	return DefWindowProc(hwnd, msg, wparam, lparam);
//}

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial {
	XMFLOAT4 color;//�F(RGBA)
};

//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
struct ConstBufferDataTransform {
	XMMATRIX mat; //3D�ϊ��s��
};

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
		
		gameScene->Draw();
	}

#pragma region �ŏ��̃V�[���̏I��

	//�����Ƀ|���S���̏���������������

#pragma endregion �ŏ��̃V�[���̏I��

#pragma region ��ՃV�X�e���̏I��

	//3D�I�u�W�F�N�g���
	delete gameScene;

	//WindowsAPI�̏I������
	winApp->Finalize();

#pragma endregion ��ՃV�X�e���̏I��

	return 0;
}