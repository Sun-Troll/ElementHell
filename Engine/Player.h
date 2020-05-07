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
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
		CircF GetCircF() const;
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
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
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
		CircF GetCircF() const;
	private:
		CircF hitbox;
		VecF vel;
		VecF curTarget;
		VecI drawPos;
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
	void AimBullets(const VecF& target);
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
	void DrawPosUpdate();
	void Draw(Graphics& gfx) const;
	void DrawPosBulletsUpdate();
	void DrawBullets(Graphics& gfx) const;
private:
	CircF hitbox;
	float speedFast = 500.0f;
	float speedSlow = 300.0f;
	static constexpr float hpBase = 1000.0f;
	float hpMax = hpBase;
	float hpCur = hpMax;
	static constexpr float radius = 5.0f;
	static constexpr float baseFireTimePlayerAnim = 0.12f; // starts lagging at 0.001f
	float maxFireTimePlayerAnim = baseFireTimePlayerAnim;
	float curFireBasePlayerAnim = 0.0f;
	static constexpr float drawDamageTimeMax = 0.2f;
	float drawDamageTimeCur = drawDamageTimeMax + 1.0f;
	static constexpr int nSpritesPlayer = 4;
	static constexpr int spritePlayerWidth = 84;
	static constexpr int spritePlayerHeight = 96;
	static constexpr int xOffset = spritePlayerWidth / 2;
	static constexpr int yOffset = spritePlayerHeight / 2;
	VecI drawPos;
	std::vector<Surface> spritesPlayer;
	const RectF movementRegionPlayer{ xOffset, float(Graphics::ScreenWidth - xOffset),
		yOffset, float(Graphics::GameHeight - yOffset) };
	static constexpr float pi = 3.141592741f;

	//BulletCenter
	static constexpr float baseBulletCenterDamage = 40.0f;
	float bulletCenterDamage = baseBulletCenterDamage;
	static constexpr float bulletCenterSpeed = 1000.0f;
	static constexpr int nSpritesBulletCenter = 4;
	static constexpr int spriteBulletCenterDim = 24; // assumes same width/height
	static constexpr int bulCentOff = spriteBulletCenterDim / 2;
	static constexpr float bulletCenterRadius = float(spriteBulletCenterDim) / 2.0f;
	const RectF movementRegionBulletCenter{ float(-bulCentOff), float(Graphics::ScreenWidth + bulCentOff),
		float(-bulCentOff), float(Graphics::GameHeight + bulCentOff) };
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
	static constexpr int bulSideOff = spriteBulletSideDim / 2;
	static constexpr int nBulletsSideFired = 6;
	static constexpr float bulletSideRadius = float(spriteBulletSideDim) / 2.0f;
	const RectF movementRegionBulletSide{ float(-bulSideOff), float(Graphics::ScreenWidth + bulSideOff),
		float(-bulSideOff), float(Graphics::GameHeight + bulSideOff) };
	std::vector<Surface> spritesBulletSide;
	std::vector<BulletSide> bulletsSide;
	std::vector<VecF> bulletSidePosVel;
};