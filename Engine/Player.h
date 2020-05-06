#pragma once

#include "Graphics.h"
#include "RectF.h"
#include "CircF.h"
#include "Stats.h"
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
		bool Clamp(const RectF& bulletCenterRegion) const;
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
		CircF GetCircF() const;
	private:
		VecF pos;
		VecF vel;
		static constexpr float maxAnimTime = 0.6f;
		float curAnimTime = 0.0f;
	};
	class BulletSide
	{
	public:
		BulletSide(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void SetTarget(const VecF& target);
		void Animate(float dt);
		bool Clamp(const RectF& bulletSideRegion) const;
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
		CircF GetCircF() const;
	private:
		VecF pos;
		VecF vel;
		VecF curTarget;
		static constexpr float maxAnimTime = 0.6f;
		float curAnimTime = 0.0f;
		bool targeting = false;
	};
public:
	Player(const VecF& pos);
	void Respawn(const VecF& pos_in, const Stats& stats);
	void Move(bool left, bool right, bool up, bool down, bool slow, float dt);
	void Clamp();
	void Fire(float dt);
	void UpdateBullets(float dt);
	void AimBullets(VecF target);
	int GetCenterBulletN() const;
	CircF GetCenterBulletCircF(int i) const;
	float GetCenterBulletDamage() const;
	void PopCenterBullet(int i);
	int GetSideBulletN() const;
	CircF GetSideBulletCircF(int i) const;
	float GetSideBulletDamage() const;
	void PopSideBullet(int i);
	float GetHpMax() const;
	float GetHpCur() const;
	bool IsAlive() const;
	void Damaged(float damage);
	VecF GetCenter() const;
	CircF GetCircF() const;
	void Draw(Graphics& gfx) const;
	void DrawBullets(Graphics& gfx) const;
private:
	VecF pos;
	float speedFast = 500.0f;
	float speedSlow = 300.0f;
	static constexpr float hpBase = 1000.0f;
	float hpMax = hpBase;
	float hpCur = hpMax;
	static constexpr float radius = 5.0f;
	static constexpr float baseFireTimePlayerAnim = 110.12f;
	float maxFireTimePlayerAnim = baseFireTimePlayerAnim;
	float curFireBasePlayerAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.2f;
	float drawDamageTimeCur = drawDamageTimeMax + 1.0f;
	static constexpr int nSpritesPlayer = 4;
	static constexpr int spritePlayerWidth = 84;
	static constexpr int spritePlayerHeight = 96;
	std::vector<Surface> spritesPlayer;
	const RectF movementRegionPlayer{ 0.0f, float(Graphics::ScreenWidth - spritePlayerWidth),
		0.0f, float(Graphics::GameHeight - spritePlayerHeight) };
	static constexpr float pi = 3.141592741f;

	//BulletCenter
	static constexpr float baseBulletCenterDamage = 40.0f;
	float bulletCenterDamage = baseBulletCenterDamage;
	static constexpr float bulletCenterSpeed = 1000.0f;
	static constexpr int nSpritesBulletCenter = 4;
	static constexpr int spriteBulletCenterDim = 24; // assumes same width/height
	static constexpr float bulletCenterRadius = float(spriteBulletCenterDim) / 2.0f;
	const RectF movementRegionBulletCenter{ float(-spriteBulletCenterDim), float(Graphics::ScreenWidth),
		float(-spriteBulletCenterDim), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBulletCenter;
	std::vector<BulletCenter> bulletsCenter;
	bool centerFiring = false;

	//BulletSide
	static constexpr float baseBulletSideDamage = 10.0f;
	float bulletSideDamage = baseBulletSideDamage;
	static constexpr float bulletSideSpeed = 100.0f;
	static constexpr float trgSpeedUp = 20.0f;
	static constexpr float bulletSideSpawnDist = 40.0f;
	static constexpr int nSpritesBulletSide = 8;
	static constexpr int spriteBulletSideDim = 16; // assumes same width/height
	static constexpr int nBulletsSideFired = 6;
	static constexpr float bulletSideRadius = float(spriteBulletSideDim) / 2.0f;
	const RectF movementRegionBulletSide{ float(-spriteBulletSideDim), float(Graphics::ScreenWidth),
		float(-spriteBulletSideDim), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBulletSide;
	std::vector<BulletSide> bulletsSide;
	std::vector<VecF> bulletSidePosVel;
};