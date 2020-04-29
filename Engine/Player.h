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
		void Animate(float dt);
		bool Clamp(const RectF& bulletSideRegion) const;
		void Draw(const std::vector<Surface>& sprites, Graphics& gfx) const;
		CircF GetCircF() const;
	private:
		VecF pos;
		VecF vel;
		static constexpr float maxAnimTime = 0.6f;
		float curAnimTime = 0.0f;
	};
public:
	Player(const VecF& pos);
	void Respawn(const VecF& pos_in, const Stats& stats);
	void Move(bool left, bool right, bool up, bool down, float dt);
	void Clamp();
	void Fire(float dt);
	void UpdateBullets(float dt);
	int GetCenterBulletN() const;
	CircF GetCenterBulletCircF(int i) const;
	float GetCenterBulletDPS() const;
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
	float speed = 200.0f;
	static constexpr float hpBase = 1000.0f;
	float hpMax = hpBase;
	float hpCur = hpMax;
	static constexpr float radius = 5.0f;
	static constexpr float baseFireTimePlayerAnim = 0.6f;
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
	static constexpr float baseBulletCenterDPS = 100.0f;
	float bulletCenterDPS = baseBulletCenterDPS;
	static constexpr float bulletCenterSpeed = 400.0f;
	static constexpr int nSpritesBulletCenter = 2;
	static constexpr int spriteBulletCenterDim = 12; // assumes same width/height
	static constexpr float bulletCenterRadius = float(spriteBulletCenterDim) / 2.0f;
	const RectF movementRegionBulletCenter{ float(-spriteBulletCenterDim), float(Graphics::ScreenWidth),
		float(-spriteBulletCenterDim), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBulletCenter;
	std::vector<BulletCenter> bulletsCenter;
	bool isFiring = false;

	//BulletSide
	static constexpr float baseBulletSideDamage = 10.0f;
	float bulletSideDamage = baseBulletSideDamage;
	static constexpr float bulletSideSpeed = 600.0f;
	static constexpr float bulletSideSpawnDist = 40.0f;
	static constexpr int nSpritesBulletSide = 2;
	static constexpr int spriteBulletSideDim = 8; // assumes same width/height
	static constexpr int nBulletsSideFired = 6;
	static constexpr float bulletSideRadius = float(spriteBulletSideDim) / 2.0f;
	const RectF movementRegionBulletSide{ float(-spriteBulletSideDim), float(Graphics::ScreenWidth),
		float(-spriteBulletSideDim), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBulletSide;
	std::vector<BulletSide> bulletsSide;
	std::vector<VecF> bulletSidePosVel;
};