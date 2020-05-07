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

void Player::Fire(float dt)
{
	curFireBasePlayerAnim += dt;
	while (curFireBasePlayerAnim >= maxFireTimePlayerAnim)
	{
		curFireBasePlayerAnim -= maxFireTimePlayerAnim;
		if (centerFiring)
		{
			bulletsCenter.emplace_back(BulletCenter{
				{ hitbox.pos },
				{ 0.0f, -bulletCenterSpeed } });
			centerFiring = false;
		}
		else
		{
			centerFiring = true;
		}
		const VecF bulSideBasePos{ hitbox.pos };
		for (int i = 0; i < nBulletsSideFired; ++i)
		{
			bulletsSide.emplace_back(BulletSide{
				{ bulSideBasePos.x + bulletSidePosVel[i].x * bulletSideSpawnDist,
				bulSideBasePos.y + bulletSidePosVel[i].y * bulletSideSpawnDist },
				{ bulletSidePosVel[i].x * bulletSideSpeed, bulletSidePosVel[i].y * bulletSideSpeed } });
		}
	}
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		drawDamageTimeCur += dt;
	}
}

void Player::UpdateBullets(float dt)
{
	for (auto& bc : bulletsCenter)
	{
		bc.Move(dt);
		bc.Animate(dt);
	}
	for (auto& bs : bulletsSide)
	{
		bs.Move(dt);
		bs.Animate(dt);
	}

	for (int i = 0; i < bulletsCenter.size(); ++i)
	{
		if (bulletsCenter[i].Clamp(movementRegionBulletCenter))
		{
			PopCenterBullet(i);
			--i;
		}
	}
	for (int i = 0; i < bulletsSide.size(); ++i)
	{
		if (bulletsSide[i].Clamp(movementRegionBulletSide))
		{
			PopSideBullet(i);
			--i;
		}
	}
}

void Player::AimBullets(const VecF& target)
{
	for (auto& bs : bulletsSide)
	{
		bs.SetTarget(target);
	}
}

int Player::GetCenterBulletN() const
{
	return int(bulletsCenter.size());
}

CircF Player::GetCenterBulletCircF(int i) const
{
	return bulletsCenter[i].GetCircF();
}

float Player::GetCenterBulletDamage() const
{
	return bulletCenterDamage;
}

void Player::PopCenterBullet(int i)
{
	std::swap(bulletsCenter[i], bulletsCenter.back());
	bulletsCenter.pop_back();
}

int Player::GetSideBulletN() const
{
	return int(bulletsSide.size());
}

CircF Player::GetSideBulletCircF(int i) const
{
	return bulletsSide[i].GetCircF();
}

float Player::GetSideBulletDamage() const
{
	return bulletSideDamage;
}

void Player::PopSideBullet(int i)
{
	std::swap(bulletsSide[i], bulletsSide.back());
	bulletsSide.pop_back();
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

VecF Player::GetCenter() const
{
	return hitbox.pos;
}

CircF Player::GetCircF() const
{
	return hitbox;
}

void Player::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
}

void Player::Draw(Graphics& gfx) const
{
	const int iSpritePlayer = int(curFireBasePlayerAnim * nSpritesPlayer / maxFireTimePlayerAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, Colors::Red, spritesPlayer[iSpritePlayer]);
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, spritesPlayer[iSpritePlayer]);
	}
}

void Player::DrawPosBulletsUpdate()
{
	for (auto& bc : bulletsCenter)
	{
		bc.DrawPosUpdate();
	}
	for (auto& bs : bulletsSide)
	{
		bs.DrawPosUpdate();
	}
}

void Player::DrawBullets(Graphics& gfx) const
{
	for (const auto& bc : bulletsCenter)
	{
		bc.Draw(spritesBulletCenter, gfx);
	}
	for (const auto& bs : bulletsSide)
	{
		bs.Draw(spritesBulletSide, gfx);
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
}

void Player::BulletCenter::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iBullet], gfx.GetGameRect());
}

CircF Player::BulletCenter::GetCircF() const
{
	return hitbox;
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
}

void Player::BulletSide::Draw(const std::vector<Surface>& sprites, Graphics & gfx) const
{
	int iBullet = int(curAnimTime * nSpritesBulletSide / maxAnimTime / 2);
	if (targeting)
	{
		iBullet += nSpritesBulletSide / 2;
	}
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iBullet], gfx.GetGameRect());
}

CircF Player::BulletSide::GetCircF() const
{
	return hitbox;
}
