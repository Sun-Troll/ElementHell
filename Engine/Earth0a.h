#pragma once

#include "Player.h"

class Earth0a
{
private:
	class Bullet
	{
	public:
		Bullet(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletRegion) const;
		bool PlayerHit(const CircF& pCirc) const;
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, Graphics::DrawRegion cur, Graphics& gfx) const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
		Graphics::DrawRegion drawReg = Graphics::DrawRegion::Rest;
		static constexpr float maxAnimTime = 1.1f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		static constexpr float radius = 7.0f;
		bool active = true;
	};
public:
	Earth0a(const VecF& pos, const VecF& vel);
	void Move(float dt);
	bool Clamp(const RectF& movementRegionEarth0a);
	void Fire(const Player& player0, const Player& player1, bool multiplayer, float dt);
	void UpdateBullets(const RectF& movementRegionBullet, float dt);
	void HitPlayer(Player& player);
	void GetHit(Player& player, float dt);
	bool IsDead() const;
	bool BulletsEmpty() const;
	void DrawPosUpdate();
	void Draw(const std::vector<Surface>& sprites, Graphics::DrawRegion cur, Graphics& gfx) const;
	void DrawPosBulletsUpdate();
	void DrawBullets(const std::vector<Surface>& spritesBullet, Graphics::DrawRegion cur, Graphics& gfx) const;
private:
	static constexpr float speed = 200.0f;
	CircF hitbox;
	VecF vel;
	static constexpr float hpMax = 200.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0aAnim = 0.4f; // normal 0.6
	float curFireBaseEarth0aAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.1f;
	float drawDamageTimeCur = drawDamageTimeMax;
	VecI drawPos;
	int curDrawFrame = 0;
	bool drawDamaged = false;
	Graphics::DrawRegion drawReg = Graphics::DrawRegion::Rest;
	static constexpr float earth0aRadius = 32.0f + 4.0f;
	static constexpr float pi = 3.141592741f;
public:
	static constexpr int nSpritesEarth0a = 6;
	static constexpr int spriteEarth0aWidth = 64;
	static constexpr int spriteEarth0aHeight = 54;
	static constexpr int xOffset = spriteEarth0aWidth / 2;
	static constexpr int yOffset = 19; // must manually test/calculate

// bullets
private:
	static constexpr float bulletSpeed = 400.0f;
	static constexpr float bulletDamage = 50.0f;
	std::vector<Bullet> bullets;
	std::vector<Bullet> bulletsTemp;
public:
	static constexpr int nSpritesBullet = 4;
	static constexpr int spriteBulletDim = 32; // assumes same width/height
	static constexpr int bulOffset = spriteBulletDim / 2;
};