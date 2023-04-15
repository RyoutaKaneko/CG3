#include "GameScene.h"

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete player;
}

///-----�ϐ��̏�����-----///
void GameScene::Initialize(SpriteCommon& spriteCommon) {
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	
	//player
	playerModel = Model::LoadFromOBJ("triangle_mat");
	player = Object3d::Create();
	player->SetModel(playerModel);
	player->SetPosition(Vector3(0, 0, -25));
	//�J����
	viewProjection = new ViewProjection;
	viewProjection->Initialize();
	viewProjection->eye = { 0, 3, -30 };
	viewProjection->target = { 0, 0, -15 };

	xmViewProjection = new XMViewProjection;

	// �X�v���C�g�̏�����
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice(), 1280, 720);
	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dxCommon->GetDevice());

	//�؂̉摜
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(50 * 1, 50 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, spriteCommon, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//�p�[�e�B�N��������
	particle = Particle::LoadParticleTexture("effect1.png");
	pm = ParticleManager::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	pm->SetParticleModel(particle);
	//�J�������Z�b�g
	pm->SetXMViewProjection(xmViewProjection);
}

///-----�X�V����-----///
void GameScene::Update() {
	input->Update();

	//player�ړ�
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

	//�p�[�e�B�N��
	if (input->PushKey(DIK_SPACE))
	{
		pm->Fire(particle, 30, 0.2f, 0, 2, { 8.0f, 0.0f });
	}

	//�X�V
	player->Update();
	viewProjection->UpdateMatrix();
	pm->Update();
}

void GameScene::Draw() {
#pragma region 3D�I�u�W�F�N�g�`��

// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	player->Draw(viewProjection);

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

#pragma endregion

#pragma region �p�[�e�B�N���`��

	// �p�[�e�B�N���`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== �p�[�e�B�N���`�� ====///
	//�p�[�e�B�N��
	pm->Draw();

	// �p�[�e�B�N���`��㏈��
	ParticleManager::PostDraw();

#pragma endregion

#pragma region �X�v���C�g�`��

	// �X�v���C�g�`��O����
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== �X�v���C�g�`�� ===///
	wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}