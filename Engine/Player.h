#pragma once

#include "Graphics.h"
#include "RectF.h"
#include <vector>

class Player
{
private:
	class BulletCenter
	{
	public:
		BulletCenter(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletCenterRegion);
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	private:
		VecF pos;
		VecF vel;
		static constexpr float maxAnimTime = 0.6f;
		float curAnimTime = 0.0f;
	};
public:
	Player(const VecF& pos);
	void Move(bool left, bool right, bool up, bool down, float dt);
	void Clamp();
	void Fire(float dt);
	void UpdateCenterBullets(float dt);
	void PopCenterBullet(int i);
	void Draw(Graphics& gfx) const;
	void DrawBulletsCenter(Graphics& gfx) const;
private:
	VecF pos;
	float speed = 200.0f;
	float hpMax = 1000.0f;
	float hpCur = hpMax;
	float maxFireTimePlayerAnim = 0.5f;
	float curFireBasePlayerAnim = 0.0f;
	static constexpr int nSpritesPlayer = 4;
	static constexpr int spritePlayerWidth = 84;
	static constexpr int spritePlayerHeight = 96;
	std::vector<Surface> spritesPlayer;
	const RectF movementRegionPlayer{ 0.0f, float(Graphics::ScreenWidth - spritePlayerWidth),
		0.0f, float(Graphics::ScreenHeight - spritePlayerHeight) };

	//BulletCenter
	static constexpr float bulletCenterSpeed = 400.0f;
	static constexpr int nSpritesBulletCenter = 2;
	static constexpr int spriteBulletCenterDim = 12; // assumes same width/height
	const RectF movementRegionBulletCenter{ float(-spriteBulletCenterDim), float(Graphics::ScreenWidth),
		float(-spriteBulletCenterDim), float(Graphics::ScreenHeight) };
	std::vector<Surface> spritesBulletCenter;
	std::vector<BulletCenter> bulletsCenter;
	bool isFiring = false;

	//BulletSide
};