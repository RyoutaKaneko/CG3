#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
class Boss : public Object3d
{
public:
	//初期化
	void BossInitialize();


	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;

private:

	//デスフラグ
	bool isDead_ = false;

	// モデル
	Model* bossModel = nullptr;
};

