#include "Player.h"
#include <cassert>
#include <algorithm>

Player::Player(const VecF& pos)
	:
	hitbox(pos, radius),
	drawPos(int(pos.x) - xOffset, int(pos.y) - yOffset)
{
	spritesPlayer.resize(nSpritesPlayer);
	for (int i = 0; i < nSpritesPlayer; ++i)
	{
		const std::string bitmapFile = "Sprites\\Player\\Player" + std::to_string(i) + ".bmp";
		spritesPlayer[i] = Surface(bitmapFile);
		assert(spritesPlayer[i].GetWidth() == spritePlayerWidth
			&& spritesPlayer[i].GetHeight() == spritePlayerHeight);
	}
	effectsPlayer.resize(nEffectsPlayer);
	for (int i = 0; i < nEffectsPlayer; ++i)
	{
		const std::string bitmapFile = "Sprites\\Effects\\Player\\PlayerEf" + std::to_string(i) + ".bmp";
		effectsPlayer[i] = Surface(bitmapFile);
		assert(effectsPlayer[i].GetWidth() == efWidthsHalf[i] * 2
			&& effectsPlayer[i].GetHeight() == efHeightsHalf[i] * 2);
	}
	spritesBulletCenter.resize(nSpritesBulletCenter);
	for (int i = 0; i < nSpritesBulletCenter; ++i)
	{
		const std::string bitmapFile = "Sprites\\PlBulCenter\\PlBulCenter" + std::to_string(i) + ".bmp";
		spritesBulletCenter[i] = Surface(bitmapFile);
		assert(spritesBulletCenter[i].GetWidth() == spriteBulletCenterDim
			&& spritesBulletCenter[i].GetHeight() == spriteBulletCenterDim);
	}
	spritesBulletSide.resize(nSpritesBulletSide);
	for (int i = 0; i < nSpritesBulletSide; ++i)
	{
		const std::string bitmapFile = "Sprites\\PlBulSide\\PlBulSide" + std::to_string(i) + ".bmp";
		spritesBulletSide[i] = Surface(bitmapFile);
		assert(spritesBulletSide[i].GetWidth() == spriteBulletSideDim
			&& spritesBulletSide[i].GetHeight() == spriteBulletSideDim);
	}
	spritesBulletAim.resize(nSpritesBulletAim);
	for (int i = 0; i < nSpritesBulletAim; ++i)
	{
		const std::string bitmapFile = "Sprites\\PlBulAim\\PlBulAim" + std::to_string(i) + ".bmp";
		spritesBulletAim[i] = Surface(bitmapFile);
		assert(spritesBulletAim[i].GetWidth() == spriteBulletAimDim
			&& spritesBulletAim[i].GetHeight() == spriteBulletAimDim);
	}
	spritesBulletPierce.resize(nSpritesBulletPierce);
	for (int i = 0; i < nSpritesBulletPierce; ++i)
	{
		const std::string bitmapFile = "Sprites\\PlBulPierce\\PlBulPierce" + std::to_string(i) + ".bmp";
		spritesBulletPierce[i] = Surface(bitmapFile);
		assert(spritesBulletPierce[i].GetWidth() == spriteBulletPierceDim
			&& spritesBulletPierce[i].GetHeight() == spriteBulletPierceDim);
	}

	for (int i = 0; i < nBulletsSideFired; ++i)
	{
		bulletSidePosVel.emplace_back(VecF{ std::cos(pi + pi / 6 - pi * i / 3), std::sin(pi + pi / 6 - pi * i / 3) });
	}
}

void Player::Respawn(const VecF& pos_in, const Stats& stats)
{
	drawDamageTimeCur = drawDamageTimeMax + 1.0f;
	hitbox.pos = pos_in;
	hpMax = hpBase * (float(stats.hp + 5) / 5.0f);
	hpCur = hpMax;
	heal = 1.0f + stats.lifeSteal / 10.0f;
	maxFireTimePlayerAnim = baseFireTimePlayerAnim / (float(stats.rpm + 10) / 10.0f);
	curFireBasePlayerAnim = 0.0f;
	bulletCenterDamage = baseBulletCenterDamage * (float(stats.dmgCent + 2) / 2.0f);
	sideFiring = false;
	bulletsCenter.clear();
	bulletsCenterTemp.clear();
	bulletSideDamage = baseBulletSideDamage * (float(stats.dmgSide + 5) / 5.0f);
	bulletsSide.clear();
	bulletsSideTemp.clear();
	FireRateAim = maxFireTimePlayerAnim * 2.0f;
	curFireTimeAim = 0.0f;
	bulletsAim.clear();
	bulletsAimTemp.clear();
	recallCurCool = 0.0f;
	maxRapidFireDur = baseRapidFireDur * (float(stats.rapidFire + 5) / 5.0f);
	curRapidFireDur = maxRapidFireDur + 1.0f;
	maxAnimTimePierce = baseAnimTimePierce / (float(stats.pierceShot + 5) / 5.0f);
}

void Player::Move(bool left, bool right, bool up, bool down, bool slow, float dt)
{
	VecF dir{ 0.0f, 0.0f };
	if (left)
	{
		dir.x -= speedFast;
	}
	if (right)
	{
		dir.x += speedFast;
	}
	if (up)
	{
		dir.y -= speedFast;
	}
	if (down)
	{
		dir.y += speedFast;
	}
	if (slow)
	{
		hitbox.pos += dir.GetNormalized() * speedSlow * dt;
	}
	else
	{
		hitbox.pos += dir.GetNormalized() * speedFast * dt;
	}
}

void Player::Clamp()
{
	if (hitbox.pos.x < movementRegionPlayer.left)
	{
		hitbox.pos.x = movementRegionPlayer.left;
	}
	else if (hitbox.pos.x > movementRegionPlayer.right)
	{
		hitbox.pos.x = movementRegionPlayer.right;
	}
	if (hitbox.pos.y < movementRegionPlayer.top)
	{
		hitbox.pos.y = movementRegionPlayer.top;
	}
	else if (hitbox.pos.y > movementRegionPlayer.bottom)
	{
		hitbox.pos.y = movementRegionPlayer.bottom;
	}
}

void Player::Fire(bool fireAim, bool recall, bool rapid, bool pierce, float dt)
{
	curFireBasePlayerAnim += dt;
	curFireTimeAim += dt;
	recallCurCool += dt;
	curRapidFireDur += dt;
	if (pierce && hpCur == hpMax)
	{
		bulletsPierceTemp.emplace_back(BulletPierce{ { hitbox.pos }, { 0.0f, -bulletPierceSpeed} });
		hpCur -= hpMax * 0.999f;
	}
	if (rapid && curRapidFireDur > maxRapidFireDur && hpCur >= hpMax * 0.5f)
	{
		curRapidFireDur = 0.0f;
		hpCur -= hpMax * 0.499f;
	}
	while (curFireBasePlayerAnim >= maxFireTimePlayerAnim)
	{
		curFireBasePlayerAnim -= maxFireTimePlayerAnim;
		bulletsCenterTemp.emplace_back(BulletCenter{ { hitbox.pos }, { 0.0f, -bulletCenterSpeed } });

		if (curRapidFireDur <= maxRapidFireDur)
		{
			for (int i = 0; i < nBulletsSideFired; ++i)
			{
				for (int n = 0; n < nBulletsSideFired; ++n)
				{
					bulletsSideTemp.emplace_back(BulletSide{
						{ hitbox.pos.x + bulletSidePosVel[i].x * bulletSideSpawnDist,
						hitbox.pos.y + bulletSidePosVel[i].y * bulletSideSpawnDist },
						{ bulletSidePosVel[n].x * bulletSideSpeed, bulletSidePosVel[n].y * bulletSideSpeed } });
				}
			}
		}
		else
		{
			if (sideFiring)
			{
				for (int i = 0; i < nBulletsSideFired; ++i)
				{
					bulletsSideTemp.emplace_back(BulletSide{
						{ hitbox.pos.x + bulletSidePosVel[i].x * bulletSideSpawnDist,
						hitbox.pos.y + bulletSidePosVel[i].y * bulletSideSpawnDist },
						{ bulletSidePosVel[i].x * bulletSideSpeed, bulletSidePosVel[i].y * bulletSideSpeed } });
				}
				sideFiring = false;
			}
			else
			{
				sideFiring = true;
			}
		}
	}
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		drawDamageTimeCur += dt;
	}
	if (fireAim && curFireTimeAim >= FireRateAim)
	{
		bulletsAimTemp.emplace_back(BulletAim{ { hitbox.pos }, { 0.0f, -bulletAimSpeed } });
		curFireTimeAim = 0.0f;
	}
	if (recall && recallCurCool >= recallCooldown && hpCur >= hpMax * 0.25f)
	{
		AimBullets(hitbox.pos);
		hpCur -= hpMax * 0.249f;
		recallCurCool = 0.0f;
	}
}

void Player::UpdateBullets(float dt)
{
	for (auto& bc : bulletsCenter)
	{
		bc.Move(dt);
		bc.Animate(dt);
		if (bc.Clamp(movementRegionBulletCenter))
		{
			bc.Deactivate();
		}
	}
	for (auto& bp : bulletsPierce)
	{
		bp.Move(dt);
		bp.Animate(dt);
		if (bp.Clamp(movementRegionBulletPierce))
		{
			bp.Deactivate();
		}
	}
	for (auto& bs : bulletsSide)
	{
		bs.Move(dt);
		bs.Animate(dt);
		if (bs.Clamp(movementRegionBulletSide))
		{
			bs.Deactivate();
		}
	}
	for (auto& ba : bulletsAim)
	{
		ba.Move(dt);
		ba.Animate(dt);
		if (ba.Clamp(movementRegionBulletAim))
		{
			ba.Deactivate();
		}
	}

	for (auto& bct : bulletsCenterTemp)
	{
		bct.Move(dt);
		bct.Animate(dt);
		if (bct.Clamp(movementRegionBulletCenter))
		{
			bct.Deactivate();
		}
	}
	for (auto& bpt : bulletsPierceTemp)
	{
		bpt.Move(dt);
		bpt.Animate(dt);
		if (bpt.Clamp(movementRegionBulletPierce))
		{
			bpt.Deactivate();
		}
	}
	for (auto& bst : bulletsSideTemp)
	{
		bst.Move(dt);
		bst.Animate(dt);
		if (bst.Clamp(movementRegionBulletSide))
		{
			bst.Deactivate();
		}
	}
	for (auto& bat : bulletsAimTemp)
	{
		bat.Move(dt);
		bat.Animate(dt);
		if (bat.Clamp(movementRegionBulletAim))
		{
			bat.Deactivate();
		}
	}
}

void Player::AimBullets(const VecF& target)
{
	for (auto& bp : bulletsPierce)
	{
		bp.SetTarget(target);
	}
	for (auto& bs : bulletsSide)
	{
		bs.SetTarget(target);
	}

	for (auto& bpt : bulletsPierceTemp)
	{
		bpt.SetTarget(target);
	}
	for (auto& bst : bulletsSideTemp)
	{
		bst.SetTarget(target);
	}
}

std::vector<Player::BulletCenter>& Player::GetCenterBullets()
{
	return bulletsCenter;
}

std::vector<Player::BulletCenter>& Player::GetCenterBulletsTemp()
{
	return bulletsCenterTemp;
}

float Player::GetCenterBulletDamage() const
{
	return bulletCenterDamage;
}

std::vector<Player::BulletSide>& Player::GetSideBullets()
{
	return bulletsSide;
}

std::vector<Player::BulletSide>& Player::GetSideBulletsTemp()
{
	return bulletsSideTemp;
}

float Player::GetSideBulletDamage() const
{
	return bulletSideDamage;
}

int Player::GetSideBulletsN() const
{
	return int(bulletsSide.size() + bulletsSideTemp.size());
}

std::vector<Player::BulletAim>& Player::GetAimBullets()
{
	return bulletsAim;
}

std::vector<Player::BulletAim>& Player::GetAimBulletsTemp()
{
	return bulletsAimTemp;
}

std::vector<Player::BulletPierce>& Player::GetPierceBullets()
{
	return bulletsPierce;
}

std::vector<Player::BulletPierce>& Player::GetPierceBulletsTemp()
{
	return bulletsPierceTemp;
}

float Player::GetPierceBulletDamage() const
{
	return bulletPierceDamage;
}

float Player::GetPierBulCharTime() const
{
	return maxAnimTimePierce;
}

float Player::GetHpMax() const
{
	return hpMax;
}

float Player::GetHpCur() const
{
	return hpCur;
}

bool Player::IsAlive() const
{
	return hpCur > 0.0f;
}

void Player::Damaged(float damage)
{
	hpCur -= damage;
	drawDamageTimeCur = 0.0f;
}

void Player::Heal(float percent)
{
	hpCur += hpMax * percent * heal;
	if (hpCur > hpMax)
	{
		hpCur = hpMax;
	}
}

const VecF& Player::GetCenter() const
{
	return hitbox.pos;
}

const CircF& Player::GetCircF() const
{
	return hitbox;
}

void Player::SpawnEffect(const VecF& pos, Effect::EffectType type)
{
	const int i = int(type);
	effectsTemp.emplace_back(efDurations[i], VecI(int(pos.x) - efWidthsHalf[i], int(pos.y) - efHeightsHalf[i]), type);
}

void Player::EffectTempUpdate(float dt)
{
	for (auto& pet : effectsTemp)
	{
		pet.Update(dt);
	}
}

void Player::EffectUpdate(float time)
{
	for (auto& pe : effects)
	{
		pe.Update(time);
	}
}

void Player::EffectDrawUpdate()
{
	for (const auto& pet : effectsTemp)
	{
		effects.emplace_back(pet);
	}
	effectsTemp.clear();
	for (int i = 0; i < effects.size(); ++i)
	{
		if (effects[i].Expired())
		{
			std::swap(effects[i], effects.back());
			effects.pop_back();
			--i;
		}
	}
}

void Player::EffectDraw(const RectI& curRect, Graphics& gfx) const
{
	for (const auto& pe : effects)
	{
		gfx.DrawSprite(pe.GetPosX(), pe.GetPosY(), effectsPlayer[pe.GetCurEffInt()], curRect);
	}
}

void Player::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
	curDrawFrame = int(curFireBasePlayerAnim * nSpritesPlayer / maxFireTimePlayerAnim);
	drawDamaged = drawDamageTimeCur <= drawDamageTimeMax;
}

void Player::Draw(const RectI& curRect, Graphics& gfx) const
{
	if (drawDamaged)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, Colors::Red, spritesPlayer[curDrawFrame], curRect);
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, spritesPlayer[curDrawFrame], curRect);
	}
}

void Player::DrawPosBulletsUpdate()
{
	for (const auto& bct : bulletsCenterTemp)
	{
		bulletsCenter.emplace_back(bct);
	}
	bulletsCenterTemp.clear();
	for (const auto& bpt : bulletsPierceTemp)
	{
		bulletsPierce.emplace_back(bpt);
	}
	bulletsPierceTemp.clear();
	for (const auto& bst : bulletsSideTemp)
	{
		bulletsSide.emplace_back(bst);
	}
	bulletsSideTemp.clear();
	for (const auto& bst : bulletsAimTemp)
	{
		bulletsAim.emplace_back(bst);
	}
	bulletsAimTemp.clear();

	for (int i = 0; i < bulletsCenter.size(); ++i)
	{
		if (!bulletsCenter[i].GetActive())
		{
			std::swap(bulletsCenter[i], bulletsCenter.back());
			bulletsCenter.pop_back();
			--i;
		}
	}
	for (int i = 0; i < bulletsPierce.size(); ++i)
	{
		if (!bulletsPierce[i].GetActive())
		{
			std::swap(bulletsPierce[i], bulletsPierce.back());
			bulletsPierce.pop_back();
			--i;
		}
	}
	for (int i = 0; i < bulletsSide.size(); ++i)
	{
		if (!bulletsSide[i].GetActive())
		{
			std::swap(bulletsSide[i], bulletsSide.back());
			bulletsSide.pop_back();
			--i;
		}
	}
	for (int i = 0; i < bulletsAim.size(); ++i)
	{
		if (!bulletsAim[i].GetActive())
		{
			std::swap(bulletsAim[i], bulletsAim.back());
			bulletsAim.pop_back();
			--i;
		}
	}

	for (auto& bc : bulletsCenter)
	{
		bc.DrawPosUpdate();
	}
	for (auto& bp : bulletsPierce)
	{
		bp.DrawPosUpdate(maxAnimTimePierce);
	}
	for (auto& bs : bulletsSide)
	{
		bs.DrawPosUpdate();
	}
	for (auto& ba : bulletsAim)
	{
		ba.DrawPosUpdate();
	}
}

void Player::DrawBullets(const RectI& curRect, Graphics& gfx) const
{
	for (const auto& bc : bulletsCenter)
	{
		bc.Draw(spritesBulletCenter, curRect, gfx);
	}
	for (const auto& bp : bulletsPierce)
	{
		bp.Draw(spritesBulletPierce, curRect, gfx);
	}
	for (const auto& bs : bulletsSide)
	{
		bs.Draw(spritesBulletSide, curRect, gfx);
	}
	for (const auto& bs : bulletsAim)
	{
		bs.Draw(spritesBulletAim, curRect, gfx);
	}
}

Player::BulletCenter::BulletCenter(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulCentOff, int(pos.y) - bulCentOff)
{
}

void Player::BulletCenter::Move(float dt)
{
	hitbox.pos += vel * dt;
}

void Player::BulletCenter::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Player::BulletCenter::Clamp(const RectF& bulletCenterRegion) const
{
	if (hitbox.pos.x < bulletCenterRegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletCenterRegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletCenterRegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletCenterRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletCenter::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulCentOff, int(hitbox.pos.y) - bulCentOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
}

void Player::BulletCenter::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

const CircF& Player::BulletCenter::GetCircF() const
{
	return hitbox;
}

bool Player::BulletCenter::GetActive() const
{
	return active;
}

void Player::BulletCenter::Deactivate()
{
	active = false;
}

Player::BulletSide::BulletSide(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulSideOff, int(pos.y) - bulSideOff),
	curTarget(pos)
{
}

void Player::BulletSide::Move(float dt)
{
	if (targeting)
	{
		const VecF posTemp = hitbox.pos;
		hitbox.pos += vel * trgSpeedUp * dt;
		if ((hitbox.pos - curTarget).GetLengthSq() > (posTemp - curTarget).GetLengthSq())
		{
			targeting = false;
		}
	}
	else
	{
		hitbox.pos += vel * dt;
	}
}

void Player::BulletSide::SetTarget(const VecF& target)
{
	vel = (target - hitbox.pos).GetNormalized() * bulletSideSpeed;
	curTarget = target;
	targeting = true;
}

void Player::BulletSide::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Player::BulletSide::Clamp(const RectF& bulletSideRegion) const
{
	if (hitbox.pos.x < bulletSideRegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletSideRegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletSideRegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletSideRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletSide::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulSideOff, int(hitbox.pos.y) - bulSideOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletSide / maxAnimTime / 2);
	if (targeting)
	{
		curDrawFrame += nSpritesBulletSide / 2;
	}
}

void Player::BulletSide::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics & gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

const CircF& Player::BulletSide::GetCircF() const
{
	return hitbox;
}

bool Player::BulletSide::GetActive() const
{
	return active;
}

void Player::BulletSide::Deactivate()
{
	active = false;
}

Player::BulletAim::BulletAim(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulAimOff, int(pos.y) - bulAimOff)
{
}

void Player::BulletAim::Move(float dt)
{
	hitbox.pos += vel * dt;
}

void Player::BulletAim::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Player::BulletAim::Clamp(const RectF& bulletCenterRegion) const
{
	if (hitbox.pos.x < bulletCenterRegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletCenterRegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletCenterRegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletCenterRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletAim::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulAimOff, int(hitbox.pos.y) - bulAimOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
}

void Player::BulletAim::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

const CircF& Player::BulletAim::GetCircF() const
{
	return hitbox;
}

bool Player::BulletAim::GetActive() const
{
	return active;
}

void Player::BulletAim::Deactivate()
{
	active = false;
}

Player::BulletPierce::BulletPierce(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulSideOff, int(pos.y) - bulSideOff),
	curTarget(pos)
{
}

void Player::BulletPierce::Move(float dt)
{
	if (targeting)
	{
		const VecF posTemp = hitbox.pos;
		hitbox.pos += vel * trgSpeedUp * dt;
		if ((hitbox.pos - curTarget).GetLengthSq() > (posTemp - curTarget).GetLengthSq())
		{
			targeting = false;
		}
	}
	else
	{
		hitbox.pos += vel * dt;
	}
}

void Player::BulletPierce::SetTarget(const VecF& target)
{
	vel = (target - hitbox.pos).GetNormalized() * bulletPierceSpeed;
	curTarget = target;
	targeting = true;
}

void Player::BulletPierce::Animate(float dt)
{
	curAnimTime += dt;
}

bool Player::BulletPierce::Clamp(const RectF& bulletPierceRegion) const
{
	if (hitbox.pos.x < bulletPierceRegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletPierceRegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletPierceRegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletPierceRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletPierce::DrawPosUpdate(float chargeTime)
{
	drawPos = { int(hitbox.pos.x) - bulPierOff, int(hitbox.pos.y) - bulPierOff };
	curDrawFrame = std::min(int(curAnimTime * nSpritesBulletPierce / chargeTime), nSpritesBulletPierce - 1);
}

void Player::BulletPierce::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

const CircF& Player::BulletPierce::GetCircF() const
{
	return hitbox;
}

bool Player::BulletPierce::GetActive() const
{
	return active;
}

void Player::BulletPierce::Deactivate()
{
	active = false;
}

bool Player::BulletPierce::GetCharged(float chargeTime) const
{
	return curAnimTime >= chargeTime;
}

void Player::BulletPierce::Discharge()
{
	curAnimTime = 0.0f;
}
