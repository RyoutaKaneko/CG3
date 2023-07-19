#include "Boss.h"

void Boss::BossInitialize()
{
	Initialize();
	// OBJからモデルデータを読み込む
	bossModel = Model::LoadFromOBJ("triangle_mat");
	bossModel->LoadTexture("Resources/red.png");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bossModel);
	isDead_ = false;
}

void Boss::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class PlayerBullet";

	//相手がplayerの弾
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
