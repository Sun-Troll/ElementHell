#pragma once

#include "Graphics.h"
#include "RectF.h"
#include <vector>

class Player
{
private:
	class BulletBasic
	{
		VecF pos;
		VecF vel;
	};
public:
	Player(const VecF& pos);
	void Move(bool left, bool right, bool up, bool down, float dt);
	void Clamp();
	void Draw(Graphics& gfx) const;
private:
	VecF pos;
	float speed = 100.0f;
	float hpMax = 1000.0f;
	float hpCur = hpMax;
	Surface spriteBase;
	const RectF movementRegion{ 0.0f, float(Graphics::ScreenWidth - spriteBase.GetWidth()),
		0.0f, float(Graphics::ScreenHeight - spriteBase.GetHeight()) };

	//BulletBasic
	std::vector<BulletBasic> bBasics;
	bool isFiring = false;
	float fireRate = 0.5f;
	float fireTime = 0.0f;
};