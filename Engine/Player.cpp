#include "Player.h"
#include <cassert>

Player::Player(const VecF& pos)
	:
	pos(pos)
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
	pos = pos_in;
	hpMax = hpBase * float(stats.hp + 1);
	hpCur = hpMax;
	maxFireTimePlayerAnim = baseFireTimePlayerAnim / float(stats.rpm + 1);
	curFireBasePlayerAnim = 0.0f;
	bulletCenterDPS = baseBulletCenterDPS * float(stats.dmgCent + 1);
	bulletsCenter.clear();
	bulletSideDamage = baseBulletSideDamage * float(stats.dmgSide + 1);
	bulletsSide.clear();
}

void Player::Move(bool left, bool right, bool up, bool down, float dt)
{
	VecF dir{ 0.0f, 0.0f };
	if (left)
	{
		dir.x -= speed;
	}
	if (right)
	{
		dir.x += speed;
	}
	if (up)
	{
		dir.y -= speed;
	}
	if (down)
	{
		dir.y += speed;
	}
	pos += dir.GetNormalized() * speed * dt;
}

void Player::Clamp()
{
	if (pos.x < movementRegionPlayer.left)
	{
		pos.x = movementRegionPlayer.left;
	}
	else if (pos.x > movementRegionPlayer.right)
	{
		pos.x = movementRegionPlayer.right;
	}
	if (pos.y < movementRegionPlayer.top)
	{
		pos.y = movementRegionPlayer.top;
	}
	else if (pos.y > movementRegionPlayer.bottom)
	{
		pos.y = movementRegionPlayer.bottom;
	}
}

void Player::Fire(float dt)
{
	const VecF playerCenter{ pos.x + float(spritePlayerWidth) * 0.5f, pos.y + float(spritePlayerHeight) * 0.5f };
	const VecF target{ playerCenter.x, playerCenter.y - 500.0f };
	curFireBasePlayerAnim += dt;
	while (curFireBasePlayerAnim >= maxFireTimePlayerAnim)
	{
		curFireBasePlayerAnim -= maxFireTimePlayerAnim;
		bulletsCenter.emplace_back(BulletCenter{
			{ playerCenter.x - float(spriteBulletCenterDim) * 0.5f, playerCenter.y - float(spriteBulletCenterDim) * 0.5f },
			{ (target - playerCenter).GetNormalized() * bulletCenterSpeed } });

		const VecF bulSideBasePos{ playerCenter.x - float(spriteBulletSideDim) * 0.5f,
			playerCenter.y - float(spriteBulletSideDim) * 0.5f };
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

int Player::GetCenterBulletN() const
{
	return int(bulletsCenter.size());
}

CircF Player::GetCenterBulletCircF(int i) const
{
	return bulletsCenter[i].GetCircF();
}

float Player::GetCenterBulletDPS() const
{
	return bulletCenterDPS;
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

CircF Player::GetCircF() const
{
	return CircF({pos.x + spritePlayerWidth * 0.5f, pos.y + spritePlayerHeight * 0.5f }, radius);
}

void Player::Draw(Graphics& gfx) const
{
	const int iSpritePlayer = int(curFireBasePlayerAnim * nSpritesPlayer / maxFireTimePlayerAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), Colors::Red, spritesPlayer[iSpritePlayer]);
	}
	else
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), spritesPlayer[iSpritePlayer]);
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
	pos(pos),
	vel(vel)
{
}

void Player::BulletCenter::Move(float dt)
{
	pos += vel * dt;
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
	if (pos.x < bulletCenterRegion.left)
	{
		return true;
	}
	else if (pos.x > bulletCenterRegion.right)
	{
		return true;
	}
	if (pos.y < bulletCenterRegion.top)
	{
		return true;
	}
	else if (pos.y > bulletCenterRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletCenter::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iBulletCenter = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iBulletCenter], gfx.GetGameRect());
}

CircF Player::BulletCenter::GetCircF() const
{
	return CircF({pos.x + bulletCenterRadius, pos.y + bulletCenterRadius}, bulletCenterRadius);
}

Player::BulletSide::BulletSide(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel)
{
}

void Player::BulletSide::Move(float dt)
{
	pos += vel * dt;
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
	if (pos.x < bulletSideRegion.left)
	{
		return true;
	}
	else if (pos.x > bulletSideRegion.right)
	{
		return true;
	}
	if (pos.y < bulletSideRegion.top)
	{
		return true;
	}
	else if (pos.y > bulletSideRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletSide::Draw(const std::vector<Surface>& sprites, Graphics & gfx) const
{
	const int iBulletSide = int(curAnimTime * nSpritesBulletSide / maxAnimTime);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iBulletSide], gfx.GetGameRect());
}

CircF Player::BulletSide::GetCircF() const
{
	return CircF({ pos.x + bulletSideRadius, pos.y + bulletSideRadius }, bulletSideRadius);
}
