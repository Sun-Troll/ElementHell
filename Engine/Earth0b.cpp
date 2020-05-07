#include "Earth0b.h"

Earth0b::Earth0b(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, earth0bRadius),
	vel(vel.GetNormalized() * speed),
	drawPos(int(pos.x) - xOffset, int(pos.y) - yOffset)
{
}

void Earth0b::Move(float dt)
{
	hitbox.pos += vel * dt;
}

bool Earth0b::Clamp(const RectF& movementRegionEarth0b)
{
	if (hitbox.pos.x < movementRegionEarth0b.left)
	{
		return true;
	}
	else if (hitbox.pos.x > movementRegionEarth0b.right)
	{
		return true;
	}
	if (hitbox.pos.y < movementRegionEarth0b.top)
	{
		return true;
	}
	else if (hitbox.pos.y > movementRegionEarth0b.bottom)
	{
		return true;
	}
	return false;
}

void Earth0b::Fire(const Player& player0, const Player& player1, bool multiplayer, float dt)
{
	if (RectF(VecF(hitbox.pos.x - float(xOffset), hitbox.pos.y - float(yOffset)),
		spriteEarth0bWidth, spriteEarth0bHeight).isContained(Graphics::GetGameRectF()))
	{
		curFireBaseEarth0bAnim += dt;
		while (curFireBaseEarth0bAnim >= maxFireTimeEarth0bAnim)
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
			curFireBaseEarth0bAnim -= maxFireTimeEarth0bAnim;
			bulletsCentE.emplace_back(BulletCentE{
					hitbox.pos, { (playerCent - hitbox.pos).Normalize() * BulletCentESpeed } });
			bulletsSideE.emplace_back(BulletSideE{ { hitbox.pos.x + bulletSideSpawnOff, hitbox.pos.y + bulletSideSpawnOff },
				{ bulletSideVelComponent, bulletSideVelComponent } });
			bulletsSideE.emplace_back(BulletSideE{ { hitbox.pos.x - bulletSideSpawnOff, hitbox.pos.y + bulletSideSpawnOff },
				{ -bulletSideVelComponent, bulletSideVelComponent } });
			bulletsSideE.emplace_back(BulletSideE{ { hitbox.pos.x - bulletSideSpawnOff, hitbox.pos.y - bulletSideSpawnOff },
				{ -bulletSideVelComponent, -bulletSideVelComponent } });
			bulletsSideE.emplace_back(BulletSideE{ { hitbox.pos.x + bulletSideSpawnOff, hitbox.pos.y - bulletSideSpawnOff },
				{ bulletSideVelComponent, -bulletSideVelComponent } });
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

void Earth0b::UpdateBullets(const RectF& movRegBulCentE, const RectF& movRegBulSideE, float dt)
{
	for (auto& bc : bulletsCentE)
	{
		bc.Move(dt);
		bc.Animate(dt);
	}
	for (auto& bs : bulletsSideE)
	{
		bs.Move(dt);
		bs.Animate(dt);
	}

	for (int i = 0; i < bulletsCentE.size(); ++i)
	{
		if (bulletsCentE[i].Clamp(movRegBulCentE))
		{
			PopBulletCentE(i);
			--i;
		}
	}
	for (int i = 0; i < bulletsSideE.size(); ++i)
	{
		if (bulletsSideE[i].Clamp(movRegBulSideE))
		{
			PopBulletSideE(i);
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

	for (int i = 0; i < bulletsSideE.size(); ++i)
	{
		if (bulletsSideE[i].PlayerHit(player.GetCircF()))
		{
			PopBulletSideE(i);
			player.Damaged(BulletSideEDamage);
			--i;
		}
	}
}

void Earth0b::GetHit(Player& player, float dt)
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

bool Earth0b::IsDead() const
{
	return hpCur <= 0.0f;
}

void Earth0b::PopBulletCentE(int i)
{
	std::swap(bulletsCentE[i], bulletsCentE.back());
	bulletsCentE.pop_back();
}

void Earth0b::PopBulletSideE(int i)
{
	std::swap(bulletsSideE[i], bulletsSideE.back());
	bulletsSideE.pop_back();
}

bool Earth0b::BulletsEmpty() const
{
	return bulletsCentE.size() == 0 && bulletsSideE.size() == 0;
}

void Earth0b::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
}

void Earth0b::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iEarth0b = int(curFireBaseEarth0bAnim * nSpritesEarth0b / maxFireTimeEarth0bAnim);
	if (drawDamageTimeCur <= drawDamageTimeMax)
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, Colors::Red, sprites[iEarth0b], gfx.GetGameRect());
	}
	else
	{
		gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iEarth0b], gfx.GetGameRect());
	}
}

void Earth0b::DrawPosBulletsUpdate()
{
	for (auto& bc : bulletsCentE)
	{
		bc.DrawPosUpdate();
	}

	for (auto& bs : bulletsSideE)
	{
		bs.DrawPosUpdate();
	}
}

void Earth0b::DrawBullets(const std::vector<Surface>& spritesBulCentE,
	const std::vector<Surface>& spritesBulSideE, Graphics& gfx) const
{
	for (const auto& bc : bulletsCentE)
	{
		bc.Draw(spritesBulCentE, gfx);
	}

	for (const auto& bs : bulletsSideE)
	{
		bs.Draw(spritesBulSideE, gfx);
	}
}

Earth0b::BulletCentE::BulletCentE(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulCentOff, int(pos.y) - bulCentOff)
{
}

void Earth0b::BulletCentE::Move(float dt)
{
	hitbox.pos += vel * dt;
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
	if (hitbox.pos.x < bulletCentERegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletCentERegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletCentERegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletCentERegion.bottom)
	{
		return true;
	}
	return false;
}

bool Earth0b::BulletCentE::PlayerHit(const CircF& pCirc) const
{
	return hitbox.Coliding(pCirc);
}

void Earth0b::BulletCentE::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulCentOff, int(hitbox.pos.y) - bulCentOff };
}

void Earth0b::BulletCentE::Draw(const std::vector<Surface>& sprites, Graphics & gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBulletCentE / maxAnimTime);
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iBullet], gfx.GetGameRect());
}

Earth0b::BulletSideE::BulletSideE(const VecF& pos, const VecF& vel)
	:
	hitbox(pos, radius),
	vel(vel),
	drawPos(int(pos.x) - bulSideOff, int(pos.y) - bulSideOff)
{
}

void Earth0b::BulletSideE::Move(float dt)
{
	hitbox.pos += vel * dt;
}

void Earth0b::BulletSideE::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Earth0b::BulletSideE::Clamp(const RectF& bulletSideERegion) const
{
	if (hitbox.pos.x < bulletSideERegion.left)
	{
		return true;
	}
	else if (hitbox.pos.x > bulletSideERegion.right)
	{
		return true;
	}
	if (hitbox.pos.y < bulletSideERegion.top)
	{
		return true;
	}
	else if (hitbox.pos.y > bulletSideERegion.bottom)
	{
		return true;
	}
	return false;
}

bool Earth0b::BulletSideE::PlayerHit(const CircF& pCirc) const
{
	return hitbox.Coliding(pCirc);
}

void Earth0b::BulletSideE::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - bulSideOff, int(hitbox.pos.y) - bulSideOff };
}

void Earth0b::BulletSideE::Draw(const std::vector<Surface>& sprites, Graphics & gfx) const
{
	const int iBullet = int(curAnimTime * nSpritesBulletSideE / maxAnimTime);
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[iBullet], gfx.GetGameRect());
}
