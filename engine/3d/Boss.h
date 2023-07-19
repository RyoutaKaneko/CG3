#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
class Boss : public Object3d
{
public:
	//������
	void BossInitialize();


	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;

private:

	//�f�X�t���O
	bool isDead_ = false;

	// ���f��
	Model* bossModel = nullptr;
};

