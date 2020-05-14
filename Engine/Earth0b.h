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
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
		static constexpr float maxAnimTime = 1.4f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		static constexpr float radius = 11.0f;
		bool active = true;
	};
	class BulletSideE
	{
	public:
		BulletSideE(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletSideERegion) const;
		bool PlayerHit(const CircF& pCirc) const;
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
		static constexpr float maxAnimTime = 1.1f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		static constexpr float radius = 7.0f;
		bool active = true;
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
	bool BulletsEmpty() const;
	void DrawPosUpdate();
	void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
	void DrawPosBulletsUpdate();
	void DrawBullets(const std::vector<Surface>& spritesBulCentE,
		const std::vector<Surface>& spritesBulSideE, const RectI& curRect, Graphics& gfx) const;
private:
	static constexpr float speed = 100.0f;
	CircF hitbox;
	VecF vel;
	static constexpr float hpMax = 250.0f;
	float hpCur = hpMax;
	static constexpr float maxFireTimeEarth0bAnim = 0.6f; // normal 0.3
	float curFireBaseEarth0bAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.1f;
	float drawDamageTimeCur = drawDamageTimeMax;
	VecI drawPos;
	int curDrawFrame = 0;
	bool drawDamaged = false;
	bool drawIsDead = false;
	static constexpr float earth0bRadius = 48.0f;
	static constexpr float pi = 3.141592741f;
public:
	static constexpr int nSpritesEarth0b = 6;
	static constexpr int spriteEarth0bWidth = 96;
	static constexpr int spriteEarth0bHeight = 96;
	static constexpr int xOffset = spriteEarth0bWidth / 2;
	static constexpr int yOffset = spriteEarth0bHeight / 2;

	// BulletCent
private:
	static constexpr float BulletCentESpeed = 300.0f;
	static constexpr float BulletCentEDamage = 150.0f;
	std::vector<BulletCentE> bulletsCentE;
	std::vector<BulletCentE> bulletsCentETemp;
public:
	static constexpr int nSpritesBulletCentE = 4;
	static constexpr int spriteBulletCentEDim = 48; // assumes same width/height
	static constexpr int bulCentOff = spriteBulletCentEDim / 2;

	// BulletSide
private:
	static constexpr float BulletSideESpeed = 400.0f;
	static constexpr float BulletSideEDamage = 50.0f;
	std::vector<BulletSideE> bulletsSideE;
	std::vector<BulletSideE> bulletsSideETemp;
	static constexpr float bulletSideSpawnOff = 32.0f;
	static constexpr float bulletSideVelComponent = BulletSideESpeed * 0.7071067691f;
public:
	static constexpr int nSpritesBulletSideE = 4;
	static constexpr int spriteBulletSideEDim = 32; // assumes same width/height
	static constexpr int bulSideOff = spriteBulletSideEDim / 2;
};