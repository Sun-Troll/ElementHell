#include "Earth0b.h"

Earth0b::Earth0b(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel.GetNormalized() * speed)
{
}

void Earth0b::Move(float dt)
{
	pos += vel * dt;
}

bool Earth0b::Clamp(const RectF& movementRegionEarth0b)
{
	if (pos.x < movementRegionEarth0b.left)
	{
		return true;
	}
	else if (pos.x > movementRegionEarth0b.right)
	{
		return true;
	}
	if (pos.y < movementRegionEarth0b.top)
	{
		return true;
	}
	else if (pos.y > movementRegionEarth0b.bottom)
	{
		return true;
	}
	return false;
}

void Earth0b::Fire(float dt)
{
	if (RectF(pos, spriteEarth0bWidth, spriteEarth0bHeight).isContained(Graphics::GetGameRectF()))
	{
		const VecF earth0aCenter{ pos.x + float(spriteEarth0bWidth) / 2.0f, pos.y + float(spriteEarth0bHeight) / 2.0f };
		curFireBaseEarth0bAnim += dt;
		while (curFireBaseEarth0bAnim >= maxFireTimeEarth0bAnim)
		{
			curFireBaseEarth0bAnim -= maxFireTimeEarth0bAnim;
			bulletsCentE.emplace_back(BulletCentE{
				{ earth0aCenter.x - float(spriteBulletCentEDim) / 2.0f, earth0aCenter.y - float(spriteBulletCentEDim) / 2.0f },
				VecF{ vel.x, vel.y + BulletCentESpeed } });
		}
	}
	else
	{
		curFireBaseEarth0bAnim = 0.0f;
	}
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		drawDamageTimeCur += dt;
	}
}

void Earth0b::UpdateBullets(const RectF& movementRegionBullet, float dt)
{
	for (auto& bc : bulletsCentE)
	{
		bc.Move(dt);
		bc.Animate(dt);
	}

	for (int i = 0; i < bulletsCentE.size(); ++i)
	{
		if (bulletsCentE[i].Clamp(movementRegionBullet))
		{
			PopBulletCentE(i);
			--i;
		}
	}
}

void Earth0b::HitPlayer(Player& player)
{
	for (int i = 0; i < bulletsCentE.size(); ++i)
	{
		if (bulletsCentE[i].PlayerHit(player.GetCircF()))
		{
			PopBulletCentE(i);
			player.Damaged(BulletCentEDamage);
			--i;
		}
	}
}

void Earth0b::GetHit(Player& player, float dt)
{
	const CircF hitBoxEarth0 = { { pos.x + float(spriteEarth0bWidth) / 2.0f,
			pos.y + float(spriteEarth0bHeight) / 2.0f }, earth0bRadius };
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

bool Earth0b::IsDead() const
{
	return hpCur <= 0.0f;
}

void Earth0b::PopBulletCentE(int i)
{
	std::swap(bulletsCentE[i], bulletsCentE.back());
	bulletsCentE.pop_back();
}

bool Earth0b::BulletsEmpty() const
{
	return bulletsCentE.size() == 0;
}

void Earth0b::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iEarth0b = int(curFireBaseEarth0bAnim * nSpritesEarth0b / maxFireTimeEarth0bAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), Colors::Red, sprites[iEarth0b], gfx.GetGameRect());
	}
	else
	{
		gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iEarth0b], gfx.GetGameRect());
	}
}

void Earth0b::DrawBullets(const std::vector<Surface>& spritesBulletCentE, Graphics & gfx) const
{
	for (const auto& bc : bulletsCentE)
	{
		bc.Draw(spritesBulletCentE, gfx);
	}
}

Earth0b::BulletCentE::BulletCentE(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel)
{
}

void Earth0b::BulletCentE::Move(float dt)
{
	pos += vel * dt;
}

void Earth0b::BulletCentE::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Earth0b::BulletCentE::Clamp(const RectF& bulletCentERegion) const
{
	if (pos.x < bulletCentERegion.left)
	{
		return true;
	}
	else if (pos.x > bulletCentERegion.right)
	{
		return true;
	}
	if (pos.y < bulletCentERegion.top)
	{
		return true;
	}
	else if (pos.y > bulletCentERegion.bottom)
	{
		return true;
	}
	return false;
}

bool Earth0b::BulletCentE::PlayerHit(const CircF & pCirc) const
{
	return GetCircF().Coliding(pCirc);
}

CircF Earth0b::BulletCentE::GetCircF() const
{
	const float halfDim = spriteBulletCentEDim * 0.5f;
	return CircF({ pos.x + halfDim, pos.y + halfDim }, radius);
}

void Earth0b::BulletCentE::Draw(const std::vector<Surface>& sprites, Graphics & gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBulletCentE / maxAnimTime);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iBullet], gfx.GetGameRect());
}
