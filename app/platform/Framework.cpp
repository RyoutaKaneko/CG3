#include "Framework.h"

void Framework::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v 
	{
		// ���t���[���X�V
		Update();

		// �I�����N�G�X�g�������烋�[�v�𔲂���
		if (IsEndRequest()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		// �`��
		Draw();
	}

	// �Q�[���̏I��
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPI�̏�����
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	dXCommon = DirectXCommon::GetInstance();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);
	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// �r���[�v���W�F�N�V�����̏�����
	ViewProjection::StaticInitialize(dXCommon->GetDevice());
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dXCommon->GetDevice());
	//fbx�ėp������
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

#pragma endregion ��ՃV�X�e���̏�����

	//�Q�[���V�[��
	gameScene = new GameScene();
	gameScene->Initialize();
}

void Framework::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		// �Q�[�����[�v�𔲂���
		endRequest_ = true;
	}
	gameScene->Update();
	// ���͂̍X�V
	/*input->Update();*/
}

void Framework::Draw()
{
#pragma region �Q�[���V�[���`��


#pragma endregion

#pragma region �`��
	// �`��O����
	dXCommon->PreDraw();
	//=== �Q�[���V�[���`�� ===//
	gameScene->Draw();
	postEffect.Draw(dXCommon->GetCommandList(), spriteCommon, dXCommon->GetDevice());
	// �`��㏈��
	dXCommon->PostDraw();
#pragma endregion
}

void Framework::Finalize()
{
	delete gameScene;
	FbxLoader::GetInstance()->Finalize();
	// WindowsAPI�̏I������
	winApp->Finalize();

}
