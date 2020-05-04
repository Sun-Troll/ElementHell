#include "Earth0a.h"
#include <cassert>

Earth0a::Earth0a(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel.GetNormalized() * speed)
{
}

void Earth0a::Move(float dt)
{
	pos += vel * dt;
}

bool Earth0a::Clamp(const RectF& movementRegionEarth0a)
{
	if (pos.x < movementRegionEarth0a.left)
	{
		return true;
	}
	else if (pos.x > movementRegionEarth0a.right)
	{
		return true;
	}
	if (pos.y < movementRegionEarth0a.top)
	{
		return true;
	}
	else if (pos.y > movementRegionEarth0a.bottom)
	{
		return true;
	}
	return false;
}

void Earth0a::Fire(const Player& player0, const Player& player1, bool multiplayer, float dt)
{
	if (RectF(pos, spriteEarth0aWidth, spriteEarth0aHeight).isContained(Graphics::GetGameRectF()))
	{
		curFireBaseEarth0aAnim += dt;
		while (curFireBaseEarth0aAnim >= maxFireTimeEarth0aAnim)
		{
			const VecF earth0aCenter{ pos.x + float(spriteEarth0aWidth) / 2.0f,
			pos.y + float(spriteBulletDim) / 2.0f + 3.0f };
			VecF playerCent = player0.GetCenter();
			if (multiplayer)
			{
				const VecF playerCent1 = player1.GetCenter();
				if ((playerCent1 - earth0aCenter).GetLengthSq() < (playerCent - earth0aCenter).GetLengthSq())
				{
					playerCent = playerCent1;
				}
			}
			curFireBaseEarth0aAnim -= maxFireTimeEarth0aAnim;
			bullets.emplace_back(Bullet{
					{ earth0aCenter.x - float(spriteBulletDim) / 2.0f, earth0aCenter.y - float(spriteBulletDim) / 2.0f },
					{ (playerCent - earth0aCenter).Normalize() * bulletSpeed } });
		}
	}
	else
	{
		curFireBaseEarth0aAnim = 0.0f;
	}
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		drawDamageTimeCur += dt;
	}
}

void Earth0a::UpdateBullets(const RectF& movementRegionBullet, float dt)
{
	for (auto& bc : bullets)
	{
		bc.Move(dt);
		bc.Animate(dt);
	}

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].Clamp(movementRegionBullet))
		{
			PopBullet(i);
			--i;
		}
	}
}

void Earth0a::HitPlayer(Player& player)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].PlayerHit(player.GetCircF()))
		{
			PopBullet(i);
			player.Damaged(bulletDamage);
			--i;
		}
	}
}

void Earth0a::GetHit(Player& player, float dt)
{
	const CircF hitBoxEarth0 = { { pos.x + float(spriteEarth0aWidth) / 2.0f,
			pos.y + float(spriteBulletDim) / 2.0f + 3.0f }, earth0aRadius };
	const float centerBulletDamage = player.GetCenterBulletDPS() * dt;
	for (int i = 0; i < player.GetCenterBulletN(); ++i)
	{
		if (hitBoxEarth0.Coliding(player.GetCenterBulletCircF(i)))
		{
			hpCur -= centerBulletDamage;
			drawDamageTimeCur = 0.0f;
		}
	}
	for (int i = 0; i < player.GetSideBulletN(); ++i)
	{
		if (hitBoxEarth0.Coliding(player.GetSideBulletCircF(i)))
		{
			hpCur -= player.GetSideBulletDamage();
			player.PopSideBullet(i);
			--i;
			drawDamageTimeCur = 0.0f;
		}
	}
}

bool Earth0a::IsDead() const
{
	return hpCur <= 0.0f;
}

void Earth0a::PopBullet(int i)
{
	std::swap(bullets[i], bullets.back());
	bullets.pop_back();
}

bool Earth0a::BulletsEmpty() const
{
	return bullets.size() == 0;
}

void Earth0a::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iEarth0a = int(curFireBaseEarth0aAnim * nSpritesEarth0a / maxFireTimeEarth0aAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), Colors::Red, sprites[iEarth0a], gfx.GetGameRect());
	}
	else
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iEarth0a], gfx.GetGameRect());
	}
}

void Earth0a::DrawBullets(const std::vector<Surface>& spritesBullet, Graphics& gfx) const
{
	for (const auto& bc : bullets)
	{
		bc.Draw(spritesBullet, gfx);
	}
}

Earth0a::Bullet::Bullet(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel)
{
}

void Earth0a::Bullet::Move(float dt)
{
	pos += vel * dt;
}

void Earth0a::Bullet::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Earth0a::Bullet::Clamp(const RectF& bulletRegion) const
{
	if (pos.x < bulletRegion.left)
	{
		return true;
	}
	else if (pos.x > bulletRegion.right)
	{
		return true;
	}
	if (pos.y < bulletRegion.top)
	{
		return true;
	}
	else if (pos.y > bulletRegion.bottom)
	{
		return true;
	}
	return false;
}

bool Earth0a::Bullet::PlayerHit(const CircF& pCirc) const
{
	return GetCircF().Coliding(pCirc);
}

CircF Earth0a::Bullet::GetCircF() const
{
	const float halfDim = spriteBulletDim * 0.5f;
	return CircF({ pos.x + halfDim, pos.y + halfDim }, radius);
}

void Earth0a::Bullet::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBullet / maxAnimTime);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iBullet], gfx.GetGameRect());
}
