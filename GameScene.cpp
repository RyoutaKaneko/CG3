#include "GameScene.h"

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete input;
	delete player;
}

///-----�ϐ��̏�����-----///
void GameScene::Initialize(WinApp* winApp, DirectXCommon* dxCommon) {
	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);
	//�X�v���C�g�̏�����
	sprite->SetSize(XMFLOAT2(256, 128));
	sprite->Initialize(dxCommon, WinApp::window_width, WinApp::window_height);
	sprite->LoadTexture(1, L"Resources/wood.png", dxCommon);
	player->SetPosition(XMFLOAT3(0, 0, -25));
	player->SetEye(XMFLOAT3(0, 3, -30));
	player->SetTarget(XMFLOAT3(0, 0, -15));
	//����
	srand(time(NULL));
}

///-----�X�V����-----///
void GameScene::Update() {
	input->Update();

	
		///--------------�X�V�������L�q-------------///
		//�����[�v������
		playerVec = { 0.0f,0.0f,0.0f };
		move = { 0,0,0 };

		//�ړ�

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
	//�`��O����
	dxCommon->PreDraw();

#pragma region �ŏ��̃V�[���̕`��
	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	player->Draw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PostDraw();

	//�����Ƀ|���S���Ȃǂ̕`�揈��������
	
		sprite->Draw(dxCommon);
	

#pragma endregion �ŏ��̃V�[���̕`��
	// �`��㏈��
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
	//�e���W
	float olx = object->GetPositionX() - object->GetScaleX();
	float orx = object->GetPositionX() + object->GetScaleX();
	float oty = object->GetPositionY() + object->GetScaleY();
	float oby = object->GetPositionY() - object->GetScaleY();
	float ofz = object->GetPositionZ() - object->GetScaleZ();
	float obz = object->GetPositionZ() + object->GetScaleZ();
	//�v���C���[���W
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