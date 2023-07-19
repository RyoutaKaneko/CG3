#pragma once
#include "Sprite.h"
class PostEffect : public Sprite
{
public:
	void Draw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon,
		ID3D12Device* dev);

private:
};

