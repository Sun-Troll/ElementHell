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
			bulletsTemp.emplace_back(Bullet{
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
		if (bc.Clamp(movementRegionBullet))
		{
			bc.Deactivate();
		}
	}
	for (auto& bct : bulletsTemp)
	{
		bct.Move(dt);
		bct.Animate(dt);
		if (bct.Clamp(movementRegionBullet))
		{
			bct.Deactivate();
		}
	}
}

void Earth0a::HitPlayer(Player& player)
{
	for (auto& bc : bullets)
	{
		if (bc.GetActive() && bc.PlayerHit(player.GetCircF()))
		{
			bc.Deactivate();
			player.Damaged(bulletDamage);
		}
	}
	for (auto& bct : bulletsTemp)
	{
		if (bct.GetActive() && bct.PlayerHit(player.GetCircF()))
		{
			bct.Deactivate();
			player.Damaged(bulletDamage);
		}
	}
}

void Earth0a::GetHit(Player& player, float dt)
{
	assert(hpCur > 0.0f);
	for (auto& bc : player.GetCenterBullets())
	{
		if (bc.GetActive())
		{
			if (hitbox.Coliding(bc.GetCircF()))
			{
				hpCur -= player.GetCenterBulletDamage();
				bc.Deactivate();
				drawDamageTimeCur = 0.0f;
			}
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.04f);
			return;
		}
	}
	for (auto& bp : player.GetPierceBullets())
	{
		if (bp.GetActive() && bp.GetCharged() && hitbox.Coliding(bp.GetCircF()))
		{
			hpCur -= player.GetPierceBulletDamage();
			bp.Discharge();
			drawDamageTimeCur = 0.0f;
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.03f);
			return;
		}
	}
	for (auto& bs : player.GetSideBullets())
	{
		if (bs.GetActive() && hitbox.Coliding(bs.GetCircF()))
		{
			hpCur -= player.GetSideBulletDamage();
			bs.Deactivate();
			drawDamageTimeCur = 0.0f;
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.02f);
			return;
		}
	}
	for (auto& ba : player.GetAimBullets())
	{
		if (ba.GetActive())
		{
			const CircF curAimBul = ba.GetCircF();
			if (hitbox.Coliding(curAimBul))
			{
				player.AimBullets((curAimBul.pos + hitbox.pos) * 0.5f);
				ba.Deactivate();
			}
		}
	}

	for (auto& bct : player.GetCenterBulletsTemp())
	{
		if (bct.GetActive())
		{
			if (hitbox.Coliding(bct.GetCircF()))
			{
				hpCur -= player.GetCenterBulletDamage();
				bct.Deactivate();
				drawDamageTimeCur = 0.0f;
			}
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.04f);
			return;
		}
	}
	for (auto& bpt : player.GetPierceBulletsTemp())
	{
		if (bpt.GetActive() && bpt.GetCharged() && hitbox.Coliding(bpt.GetCircF()))
		{
			hpCur -= player.GetPierceBulletDamage();
			bpt.Discharge();
			drawDamageTimeCur = 0.0f;
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.03f);
			return;
		}
	}
	for (auto& bst : player.GetSideBulletsTemp())
	{
		if (hpCur <= 0.0f)
		{
			return;
		}
		if (bst.GetActive() && hitbox.Coliding(bst.GetCircF()))
		{
			hpCur -= player.GetSideBulletDamage();
			bst.Deactivate();
			drawDamageTimeCur = 0.0f;
		}
		if (hpCur <= 0.0f)
		{
			player.Heal(0.02f);
			return;
		}
	}
	for (auto& bat : player.GetAimBulletsTemp())
	{
		if (bat.GetActive())
		{
			const CircF curAimBul = bat.GetCircF();
			if (hitbox.Coliding(curAimBul))
			{
				player.AimBullets((curAimBul.pos + hitbox.pos) * 0.5f);
				bat.Deactivate();
			}
		}
	}
}

bool Earth0a::IsDead() const
{
	return hpCur <= 0.0f;
}

bool Earth0a::BulletsEmpty() const
{
	return bullets.size() == 0;
}

void Earth0a::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
	curDrawFrame = int(curFireBaseEarth0aAnim * nSpritesEarth0a / maxFireTimeEarth0aAnim);
	drawDamaged = drawDamageTimeCur <= drawDamageTimeMax;
	drawIsDead = IsDead();
}

void Earth0a::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	if (!drawIsDead)
	{
		if (drawDamaged)
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, Colors::Red, sprites[curDrawFrame], curRect);
		}
		else
		{
			gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
		}
	}
}

void Earth0a::DrawPosBulletsUpdate()
{
	for (const auto& bct : bulletsTemp)
	{
		bullets.emplace_back(bct);
	}
	bulletsTemp.clear();

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (!bullets[i].GetActive())
		{
			std::swap(bullets[i], bullets.back());
			bullets.pop_back();
			--i;
		}
	}

	for (auto& bc : bullets)
	{
		bc.DrawPosUpdate();
	}
}

void Earth0a::DrawBullets(const std::vector<Surface>& spritesBullet, const RectI& curRect, Graphics& gfx) const
{
	for (const auto& bc : bullets)
	{
		bc.Draw(spritesBullet, curRect, gfx);
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
	assert(active);
	drawPos = { int(hitbox.pos.x) - bulOffset, int(hitbox.pos.y) - bulOffset };
	curDrawFrame = int(curAnimTime * nSpritesBullet / maxAnimTime);
}

void Earth0a::Bullet::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

bool Earth0a::Bullet::GetActive() const
{
	return active;
}

void Earth0a::Bullet::Deactivate()
{
	active = false;
}
