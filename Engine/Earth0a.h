#pragma once

#include "Player.h"

class Earth0a
{
public:
	Earth0a(const VecF& pos, const VecF& vel);
	void Move(bool left, bool right, bool up, bool down, float dt);
	void Clamp();
	void Fire(float dt);
	void UpdateBullets(float dt);
	void PopCenterBullet(int i);
	void PopSideBullet(int i);
	float GetHpMax() const;
	float GetHpCur() const;
	void Draw(Graphics& gfx) const;
	void DrawBullets(Graphics& gfx) const;
private:
	VecF pos;
	VecF vel;
	static constexpr float hpMax = 200.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0aAnim = 0.6f;
	float curFireBaseEarth0aAnim = 0.0f;
	static constexpr int nSpritesEarth0a = 6;
	static constexpr int spriteEarth0aWidth = 64;
	static constexpr int spriteEarth0aHeight = 54;
	std::vector<Surface> spritesEarth0a;
	const RectF movementRegionEarth0a{ 0.0f, float(Graphics::ScreenWidth - spriteEarth0aWidth),
		0.0f, float(Graphics::GameHeight - spriteEarth0aHeight) };
	static constexpr float pi = 3.141592741f;
};