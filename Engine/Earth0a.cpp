#include "Earth0a.h"
#include <cassert>

Earth0a::Earth0a(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, earth0aRadius),
	vel(vel.GetNormalized() * speed),
	drawPos(int(pos.x) - xOffset, int(pos.y) - yOffset)
{
}

void Earth0a::Move(float dt)
{
	hitbox.pos += vel * dt;
}

bool Earth0a::Clamp(const RectF& movementRegionEarth0a)
{
	if (hitbox.pos.x < movementRegionEarth0a.left)
	{
		return true;
	}
	else if (hitbox.pos.x > movementRegionEarth0a.right)
	{
		return true;
	}
	if (hitbox.pos.y < movementRegionEarth0a.top)
	{
		return true;
	}
	else if (hitbox.pos.y > movementRegionEarth0a.bottom)
	{
		return true;
	}
	return false;
}

void Earth0a::Fire(const Player& player0, const Player& player1, bool multiplayer, float dt)
{
	if (RectF(VecF(hitbox.pos.x - float(xOffset), hitbox.pos.y - float(yOffset)), spriteEarth0aWidth, spriteEarth0aHeight).isContained(Graphics::GetGameRectF()))
	{
		curFireBaseEarth0aAnim += dt;
		while (curFireBaseEarth0aAnim >= maxFireTimeEarth0aAnim)
		{
			VecF playerCent = player0.GetCenter();
			if (multiplayer)
			{
				const VecF playerCent1 = player1.GetCenter();
				if ((playerCent1 - hitbox.pos).GetLengthSq() < (playerCent - hitbox.pos).GetLengthSq())
				{
					playerCent = playerCent1;
				}
			}
			curFireBaseEarth0aAnim -= maxFireTimeEarth0aAnim;
			bullets.emplace_back(Bullet{
					{ hitbox.pos },
					{ (playerCent - hitbox.pos).Normalize() * bulletSpeed } });
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
	for (int i = 0; i < player.GetCenterBulletN(); ++i)
	{
		const CircF curCentBul = player.GetCenterBulletCircF(i);
		if (hitbox.Coliding(curCentBul))
		{
			hpCur -= player.GetCenterBulletDamage();
			player.AimBullets(curCentBul.pos);
			player.PopCenterBullet(i);
			--i;
			drawDamageTimeCur = 0.0f;
		}
	}
	for (int i = 0; i < player.GetSideBulletN(); ++i)
	{
		if (hitbox.Coliding(player.GetSideBulletCircF(i)))
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

void Earth0a::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
}

void Earth0a::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iEarth0a = int(curFireBaseEarth0aAnim * nSpritesEarth0a / maxFireTimeEarth0aAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, Colors::Red, sprites[iEarth0a], gfx.GetGameRect());
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iEarth0a], gfx.GetGameRect());
	}
}

void Earth0a::DrawPosBulletsUpdate()
{
	for (auto& bc : bullets)
	{
		bc.DrawPosUpdate();
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
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulOffset, int(pos.y) - bulOffset)
{
}

void Earth0a::Bullet::Move(float dt)
{
	hitbox.pos += vel * dt;
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
	if (hitbox.pos.x < bulletRegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletRegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletRegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletRegion.bottom)
	{
		return true;
	}
	return false;
}

bool Earth0a::Bullet::PlayerHit(const CircF& pCirc) const
{
	return hitbox.Coliding(pCirc);
}

void Earth0a::Bullet::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulOffset, int(hitbox.pos.y) - bulOffset };
}

void Earth0a::Bullet::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBullet / maxAnimTime);
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iBullet], gfx.GetGameRect());
}
