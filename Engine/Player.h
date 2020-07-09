#pragma once

#include "Graphics.h"
#include "Rect.h"
#include "Circ.h"
#include "Stats.h"
#include "Effect.h"
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
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		const CircF& GetCircF() const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
		static constexpr float radius = 13.0f;
		static constexpr float maxAnimTime = 0.6f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		bool active = true;
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
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		const CircF& GetCircF() const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecF curTarget;
		VecI drawPos;
		static constexpr float radius = 9.0f;
		static constexpr float maxAnimTime = 0.4f;
		static constexpr float trgSpeedUp = 64.0f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		bool targeting = false;
		bool active = true;
	};
	class BulletAim
	{
	public:
		BulletAim(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void Animate(float dt);
		bool Clamp(const RectF& bulletCenterRegion) const;
		void DrawPosUpdate();
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		const CircF& GetCircF() const;
		bool GetActive() const;
		void Deactivate();
	private:
		CircF hitbox;
		VecF vel;
		VecI drawPos;
		static constexpr float radius = 17.0f;
		static constexpr float maxAnimTime = 1.0f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		bool active = true;
	};
	class BulletPierce
	{
	public:
		BulletPierce(const VecF& pos, const VecF& vel);
		void Move(float dt);
		void SetTarget(const VecF& target);
		void Animate(float dt);
		bool Clamp(const RectF& bulletCenterRegion) const;
		void DrawPosUpdate(float chargeTime);
		void Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const;
		const CircF& GetCircF() const;
		bool GetActive() const;
		void Deactivate();
		bool GetCharged(float chargeTime) const;
		void Discharge();
	private:
		CircF hitbox;
		VecF vel;
		VecF curTarget;
		VecI drawPos;
		static constexpr float radius = 26.0f;
		static constexpr float trgSpeedUp = 256.0f;
		float curAnimTime = 0.0f;
		int curDrawFrame = 0;
		bool targeting = false;
		bool active = true;
	};
public:
	Player(const VecF& pos);
	void Respawn(const VecF& pos_in, const Stats& stats);
	void Move(bool left, bool right, bool up, bool down, bool slow, float dt);
	void Clamp();
	void Fire(bool fireAim, bool recall, bool rapid, bool pierce, float dt);
	void UpdateBullets(float dt);
	void AimBullets(const VecF& target);
	std::vector<BulletCenter>& GetCenterBullets();
	std::vector<BulletCenter>& GetCenterBulletsTemp();
	float GetCenterBulletDamage() const;
	std::vector<BulletSide>& GetSideBullets();
	std::vector<BulletSide>& GetSideBulletsTemp();
	float GetSideBulletDamage() const;
	int GetSideBulletsN() const;
	std::vector<BulletAim>& GetAimBullets();
	std::vector<BulletAim>& GetAimBulletsTemp();
	std::vector<BulletPierce>& GetPierceBullets();
	std::vector<BulletPierce>& GetPierceBulletsTemp();
	float GetPierceBulletDamage() const;
	float GetPierBulCharTime() const;
	float GetHpMax() const;
	float GetHpCur() const;
	bool IsAlive() const;
	void Damaged(float damage);
	void Heal(float percent);
	const VecF& GetCenter() const;
	const CircF& GetCircF() const;
	void SpawnEffect(const VecF& pos, Effect::EffectType type);
	void EffectTempUpdate(float dt);
	void EffectUpdate(float time);
	void EffectDrawUpdate();
	void EffectDraw(const RectI& curRect, Graphics& gfx) const;
	void DrawPosUpdate();
	void Draw(const RectI& curRect, Graphics& gfx) const;
	void DrawPosBulletsUpdate();
	void DrawBullets(const RectI& curRect, Graphics& gfx) const;
private:
	CircF hitbox;
	static constexpr float speedFast = 500.0f;
	static constexpr float speedSlow = 300.0f;
	static constexpr float hpBase = 1000.0f;
	float hpMax = hpBase;
	float hpCur = hpMax;
	float heal = 1.0f;
	static constexpr float radius = 5.0f;
	static constexpr float baseFireTimePlayerAnim = 0.3f; // starts lagging at 0.001f normal 0.12f
	float maxFireTimePlayerAnim = baseFireTimePlayerAnim;
	float curFireBasePlayerAnim = 0.0f;
	static constexpr float recallCooldown = 0.5f;
	float recallCurCool = 0.0f;
	static constexpr float baseRapidFireDur = 1.0f;
	float maxRapidFireDur = baseRapidFireDur;
	float curRapidFireDur = maxRapidFireDur + 1.0f;
	static constexpr float drawDamageTimeMax = 0.2f;
	float drawDamageTimeCur = drawDamageTimeMax + 1.0f;
	static constexpr int nSpritesPlayer = 4;
	static constexpr int spritePlayerWidth = 84;
	static constexpr int spritePlayerHeight = 96;
	static constexpr int xOffset = spritePlayerWidth / 2;
	static constexpr int yOffset = spritePlayerHeight / 2;
	VecI drawPos;
	int curDrawFrame = 0;
	bool drawDamaged = false;
	std::vector<Surface> spritesPlayer;
	const RectF movementRegionPlayer{ xOffset, float(Graphics::ScreenWidth - xOffset),
		yOffset, float(Graphics::GameHeight - yOffset) };
	static constexpr float pi = 3.141592741f;

	//Effects
	std::vector<int> efWidthsHalf{ 32, 12, 16, 32 };
	std::vector<int> efHeightsHalf{ 25, 12, 16, 32 };
	std::vector<float> efDurations{ 0.07f, 0.04f ,0.1f, 0.2f };
	std::vector<Effect> effects;
	std::vector<Effect> effectsTemp;
	static constexpr int nEffectsPlayer = 4;
	std::vector<Surface> effectsPlayer;

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
	std::vector<BulletCenter> bulletsCenterTemp;

	//BulletSide
	static constexpr float baseBulletSideDamage = 10.0f;
	float bulletSideDamage = baseBulletSideDamage;
	static constexpr float bulletSideSpeed = 40.0f;
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
	std::vector<BulletSide> bulletsSideTemp;
	std::vector<VecF> bulletSidePosVel;
	bool sideFiring = false;

	//BulletAim
	float FireRateAim = maxFireTimePlayerAnim * 2.0f;
	float curFireTimeAim = 0.0f;
	static constexpr float bulletAimSpeed = 1500.0f;
	static constexpr int nSpritesBulletAim = 6;
	static constexpr int spriteBulletAimDim = 32; // assumes same width/height
	static constexpr int bulAimOff = spriteBulletAimDim / 2;
	static constexpr float bulletAimRadius = float(spriteBulletAimDim) / 2.0f;
	const RectF movementRegionBulletAim{ float(-bulAimOff), float(Graphics::ScreenWidth + bulAimOff),
		float(-bulAimOff), float(Graphics::GameHeight + bulAimOff) };
	std::vector<Surface> spritesBulletAim;
	std::vector<BulletAim> bulletsAim;
	std::vector<BulletAim> bulletsAimTemp;

	//BulletPierce
	static constexpr float baseAnimTimePierce = 2.0f;
	float maxAnimTimePierce = baseAnimTimePierce;
	static constexpr float bulletPierceDamage = 20.0f;
	static constexpr float bulletPierceSpeed = 20.0f;
	static constexpr int nSpritesBulletPierce = 7;
	static constexpr int spriteBulletPierceDim = 48; // assumes same width/height
	static constexpr int bulPierOff = spriteBulletPierceDim / 2;
	static constexpr float bulletPierceRadius = float(spriteBulletPierceDim) / 2.0f;
	const RectF movementRegionBulletPierce{ float(-bulPierOff), float(Graphics::ScreenWidth + bulPierOff),
		float(-bulPierOff), float(Graphics::GameHeight + bulPierOff) };
	std::vector<Surface> spritesBulletPierce;
	std::vector<BulletPierce> bulletsPierce;
	std::vector<BulletPierce> bulletsPierceTemp;
};