#include "Player.h"
#include <cassert>

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

	for (int i = 0; i < nBulletsSideFired; ++i)
	{
		bulletSidePosVel.emplace_back(VecF{ std::cos(pi + pi / 6 - pi * i / 3), std::sin(pi + pi / 6 - pi * i / 3) });
	}
}

void Player::Respawn(const VecF& pos_in, const Stats& stats)
{
	drawDamageTimeCur = drawDamageTimeMax + 1.0f;
	hitbox.pos = pos_in;
	hpMax = hpBase * float(stats.hp + 1);
	hpCur = hpMax;
	maxFireTimePlayerAnim = baseFireTimePlayerAnim / float(stats.rpm + 1);
	curFireBasePlayerAnim = 0.0f;
	bulletCenterDamage = baseBulletCenterDamage * float(stats.dmgCent + 1);
	bulletsCenter.clear();
	bulletSideDamage = baseBulletSideDamage * float(stats.dmgSide + 1);
	bulletsSide.clear();
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

void Player::Fire(bool fireAim, bool recall, float dt)
{
	curFireBasePlayerAnim += dt;
	curFireTimeAim += dt;
	recallCurCool += dt;
	while (curFireBasePlayerAnim >= maxFireTimePlayerAnim)
	{
		curFireBasePlayerAnim -= maxFireTimePlayerAnim;
		bulletsCenterTemp.emplace_back(BulletCenter{ { hitbox.pos }, { 0.0f, -bulletCenterSpeed } });

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
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		drawDamageTimeCur += dt;
	}
	if (fireAim && curFireTimeAim >= FireRateAim)
	{
		bulletsAimTemp.emplace_back(BulletAim{ { hitbox.pos }, { 0.0f, -bulletAimSpeed } });
		curFireTimeAim = 0.0f;
	}
	if (recall && recallCurCool >= recallCooldown)
	{
		AimBullets(hitbox.pos);
		hpCur -= hpBase * 0.24f;
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
	for (auto& bs : bulletsSide)
	{
		bs.Move(dt);
		bs.Animate(dt);
		if (bs.Clamp(movementRegionBulletSide))
		{
			bs.Deactivate();
		}
	}
	for (auto& bc : bulletsAim)
	{
		bc.Move(dt);
		bc.Animate(dt);
		if (bc.Clamp(movementRegionBulletAim))
		{
			bc.Deactivate();
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
	for (auto& bst : bulletsSideTemp)
	{
		bst.Move(dt);
		bst.Animate(dt);
		if (bst.Clamp(movementRegionBulletSide))
		{
			bst.Deactivate();
		}
	}
	for (auto& bct : bulletsAimTemp)
	{
		bct.Move(dt);
		bct.Animate(dt);
		if (bct.Clamp(movementRegionBulletAim))
		{
			bct.Deactivate();
		}
	}
}

void Player::AimBullets(const VecF& target)
{
	for (auto& bs : bulletsSide)
	{
		bs.SetTarget(target);
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

std::vector<Player::BulletAim>& Player::GetAimBullets()
{
	return bulletsAim;
}

std::vector<Player::BulletAim>& Player::GetAimBulletsTemp()
{
	return bulletsAimTemp;
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

const VecF& Player::GetCenter() const
{
	return hitbox.pos;
}

const CircF& Player::GetCircF() const
{
	return hitbox;
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
	for (auto& bs : bulletsSide)
	{
		bs.DrawPosUpdate();
	}
	for (auto& bs : bulletsAim)
	{
		bs.DrawPosUpdate();
	}
}

void Player::DrawBullets(const RectI& curRect, Graphics& gfx) const
{
	for (const auto& bc : bulletsCenter)
	{
		bc.Draw(spritesBulletCenter, curRect, gfx);
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
	drawPos = { int(hitbox.pos.x) - bulCentOff, int(hitbox.pos.y) - bulCentOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
}

void Player::BulletAim::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

const CircF & Player::BulletAim::GetCircF() const
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
