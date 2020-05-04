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
		static constexpr float maxAnimTime = 1.4f;
		float curAnimTime = 0.0f;
		static constexpr float radius = 11.0f;
	};
	class BulletSideE
	{
	public:
		BulletSideE(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletSideERegion) const;
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
	Earth0b(const VecF& pos, const VecF& vel);
	void Move(float dt);
	bool Clamp(const RectF& movementRegionEarth0b);
	void Fire(const Player& player0, const Player& player1, bool multiplayer, float dt);
	void UpdateBullets(const RectF& movRegBulCentE, const RectF& movRegBulSideE, float dt);
	void HitPlayer(Player& player);
	void GetHit(Player& player, float dt);
	bool IsDead() const;
	void PopBulletCentE(int i);
	void PopBulletSideE(int i);
	bool BulletsEmpty() const;
	void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
	void DrawBullets(const std::vector<Surface>& spritesBulCentE,
		const std::vector<Surface>& spritesBulSideE, Graphics& gfx) const;
private:
	static constexpr float speed = 30.0f;
	VecF pos;
	VecF vel;
	static constexpr float hpMax = 4000.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0bAnim = 0.4f;
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
	static constexpr float BulletCentESpeed = 100.0f;
	static constexpr float BulletCentEDamage = 150.0f;
	std::vector<BulletCentE> bulletsCentE;
public:
	static constexpr int nSpritesBulletCentE = 4;
	static constexpr int spriteBulletCentEDim = 48; // assumes same width/height

	// BulletSide
private:
	static constexpr float BulletSideESpeed = 200.0f;
	static constexpr float BulletSideEDamage = 50.0f;
	std::vector<BulletSideE> bulletsSideE;
	std::vector<VecF> sideBulOff{ VecF{ 16.0f, 16.0f }, VecF{ -48.0f, 16.0f }
	,VecF{ -48.0f, -48.0f }, VecF{ 16.0f, -48.0f } };
	std::vector<VecF> sideBulVel{ VecF{ 1.0f, 1.0f }.Normalize() * BulletSideESpeed,
		VecF{ -1000.0f, 1000.0f }.Normalize() * BulletSideESpeed,
		VecF{ -1.0f, -1.0f }.Normalize() * BulletSideESpeed,
		VecF{ 1.0f, -1.0f }.Normalize() * BulletSideESpeed };
public:
	static constexpr int nSpritesBulletSideE = 4;
	static constexpr int spriteBulletSideEDim = 32; // assumes same width/height
};