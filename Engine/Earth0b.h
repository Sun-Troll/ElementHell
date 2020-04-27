#pragma once

#include "Player.h"

class Earth0b
{
private:
	class BulletCentE
	{
	public:
		BulletCentE(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletCentERegion) const;
		bool PlayerHit(const CircF& pCirc) const;
		CircF GetCircF() const;
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	private:
		VecF pos;
		VecF vel;
		static constexpr float maxAnimTime = 1.1f;
		float curAnimTime = 0.0f;
		static constexpr float radius = 11.0f;
	};
public:
	Earth0b(const VecF& pos, const VecF& vel);
	void Move(float dt);
	bool Clamp(const RectF& movementRegionEarth0b);
	void Fire(float dt);
	void UpdateBullets(const RectF& movementRegionBullet, float dt);
	void HitPlayer(Player& player);
	void GetHit(Player& player, float dt);
	bool IsDead() const;
	void PopBulletCentE(int i);
	bool BulletsEmpty() const;
	void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	void DrawBullets(const std::vector<Surface>& spritesBulletCentE, Graphics& gfx) const;
private:
	static constexpr float speed = 30.0f;
	VecF pos;
	VecF vel;
	static constexpr float hpMax = 400.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0bAnim = 2.0f;
	float curFireBaseEarth0bAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.1f;
	float drawDamageTimeCur = drawDamageTimeMax;
	static constexpr float earth0bRadius = 48.0f;
	static constexpr float pi = 3.141592741f;
public:
	static constexpr int nSpritesEarth0b = 6;
	static constexpr int spriteEarth0bWidth = 96;
	static constexpr int spriteEarth0bHeight = 96;

	// BulletCent
private:
	static constexpr float BulletCentESpeed = 70.0f;
	static constexpr float BulletCentEDamage = 150.0f;
	std::vector<BulletCentE> bulletsCentE;
public:
	static constexpr int nSpritesBulletCentE = 4;
	static constexpr int spriteBulletCentEDim = 48; // assumes same width/height
};