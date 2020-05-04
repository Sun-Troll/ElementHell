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
		CircF GetCircF() const;
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	private:
		VecF pos;
		VecF vel;
		static constexpr float maxAnimTime = 1.1f;
		float curAnimTime = 0.0f;
		static constexpr float radius = 7.0f;
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
	void PopBullet(int i);
	bool BulletsEmpty() const;
	void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	void DrawBullets(const std::vector<Surface>& spritesBullet, Graphics& gfx) const;
private:
	static constexpr float speed = 80.0f;
	VecF pos;
	VecF vel;
	static constexpr float hpMax = 300.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0aAnim = 1.0f;
	float curFireBaseEarth0aAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.1f;
	float drawDamageTimeCur = drawDamageTimeMax;
	//static constexpr int nSpritesEarth0a = 6;
	//static constexpr int spriteEarth0aWidth = 64;
	//static constexpr int spriteEarth0aHeight = 54;
	static constexpr float earth0aRadius = 32.0f + 4.0f;
	static constexpr float pi = 3.141592741f;
public:
	static constexpr int nSpritesEarth0a = 6;
	static constexpr int spriteEarth0aWidth = 64;
	static constexpr int spriteEarth0aHeight = 54;
// bullets
private:
	static constexpr float bulletSpeed = 200.0f;
	VecF bulletSideVelRight = VecF(32.0f, -19.0f).Normalize() * bulletSpeed;
	VecF bulletSideVelLeft = VecF(-32.0f, -19.0f).Normalize() * bulletSpeed;
	static constexpr float bulletDamage = 50.0f;
	//static constexpr int nSpritesBulletCenter = 4;
	//static constexpr int spriteBulletCenterDim = 32; // assumes same width/height
	std::vector<Bullet> bullets;
public:
	static constexpr int nSpritesBullet = 4;
	static constexpr int spriteBulletDim = 32; // assumes same width/height
};