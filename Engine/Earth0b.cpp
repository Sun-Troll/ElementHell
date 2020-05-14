#include "Earth0b.h"
#include <cassert>

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
			bulletsCentETemp.emplace_back(BulletCentE{
					hitbox.pos, { (playerCent - hitbox.pos).Normalize() * BulletCentESpeed } });
			bulletsSideETemp.emplace_back(BulletSideE{ { hitbox.pos.x + bulletSideSpawnOff, hitbox.pos.y + bulletSideSpawnOff },
				{ bulletSideVelComponent, bulletSideVelComponent } });
			bulletsSideETemp.emplace_back(BulletSideE{ { hitbox.pos.x - bulletSideSpawnOff, hitbox.pos.y + bulletSideSpawnOff },
				{ -bulletSideVelComponent, bulletSideVelComponent } });
			bulletsSideETemp.emplace_back(BulletSideE{ { hitbox.pos.x - bulletSideSpawnOff, hitbox.pos.y - bulletSideSpawnOff },
				{ -bulletSideVelComponent, -bulletSideVelComponent } });
			bulletsSideETemp.emplace_back(BulletSideE{ { hitbox.pos.x + bulletSideSpawnOff, hitbox.pos.y - bulletSideSpawnOff },
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
		if (bc.Clamp(movRegBulCentE))
		{
			bc.Deactivate();
		}
	}
	for (auto& bs : bulletsSideE)
	{
		bs.Move(dt);
		bs.Animate(dt);
		if (bs.Clamp(movRegBulSideE))
		{
			bs.Deactivate();
		}
	}

	for (auto& bct : bulletsCentETemp)
	{
		bct.Move(dt);
		bct.Animate(dt);
		if (bct.Clamp(movRegBulCentE))
		{
			bct.Deactivate();
		}
	}
	for (auto& bst : bulletsSideETemp)
	{
		bst.Move(dt);
		bst.Animate(dt);
		if (bst.Clamp(movRegBulSideE))
		{
			bst.Deactivate();
		}
	}
}

void Earth0b::HitPlayer(Player& player)
{
	for (auto& bc : bulletsCentE)
	{
		if (bc.GetActive() && bc.PlayerHit(player.GetCircF()))
		{
			bc.Deactivate();
			player.Damaged(BulletCentEDamage);
		}
	}
	for (auto& bs : bulletsSideE)
	{
		if (bs.GetActive() && bs.PlayerHit(player.GetCircF()))
		{
			bs.Deactivate();
			player.Damaged(BulletCentEDamage);
		}
	}

	for (auto& bct : bulletsCentETemp)
	{
		if (bct.GetActive() && bct.PlayerHit(player.GetCircF()))
		{
			bct.Deactivate();
			player.Damaged(BulletCentEDamage);
		}
	}
	for (auto& bst : bulletsSideETemp)
	{
		if (bst.GetActive() && bst.PlayerHit(player.GetCircF()))
		{
			bst.Deactivate();
			player.Damaged(BulletCentEDamage);
		}
	}
}

void Earth0b::GetHit(Player& player, float dt)
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

bool Earth0b::IsDead() const
{
	return hpCur <= 0.0f;
}

bool Earth0b::BulletsEmpty() const
{
	return bulletsCentE.size() == 0 && bulletsSideE.size() == 0;
}

void Earth0b::DrawPosUpdate()
{
	drawPos = { int(hitbox.pos.x) - xOffset, int(hitbox.pos.y) - yOffset };
	curDrawFrame = int(curFireBaseEarth0bAnim * nSpritesEarth0b / maxFireTimeEarth0bAnim);
	drawDamaged = drawDamageTimeCur <= drawDamageTimeMax;
	drawIsDead = IsDead();
}

void Earth0b::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
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

void Earth0b::DrawPosBulletsUpdate()
{
	for (const auto& bct : bulletsCentETemp)
	{
		bulletsCentE.emplace_back(bct);
	}
	bulletsCentETemp.clear();
	for (const auto& bct : bulletsSideETemp)
	{
		bulletsSideE.emplace_back(bct);
	}
	bulletsSideETemp.clear();

	for (int i = 0; i < bulletsCentE.size(); ++i)
	{
		if (!bulletsCentE[i].GetActive())
		{
			std::swap(bulletsCentE[i], bulletsCentE.back());
			bulletsCentE.pop_back();
			--i;
		}
	}
	for (int i = 0; i < bulletsSideE.size(); ++i)
	{
		if (!bulletsSideE[i].GetActive())
		{
			std::swap(bulletsSideE[i], bulletsSideE.back());
			bulletsSideE.pop_back();
			--i;
		}
	}

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
	const std::vector<Surface>& spritesBulSideE, const RectI& curRect, Graphics& gfx) const
{
	for (const auto& bc : bulletsCentE)
	{
		bc.Draw(spritesBulCentE, curRect, gfx);
	}

	for (const auto& bs : bulletsSideE)
	{
		bs.Draw(spritesBulSideE, curRect, gfx);
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
	assert(active);
	drawPos = { int(hitbox.pos.x) - bulCentOff, int(hitbox.pos.y) - bulCentOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletCentE / maxAnimTime);
}

void Earth0b::BulletCentE::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

bool Earth0b::BulletCentE::GetActive() const
{
	return active;
}

void Earth0b::BulletCentE::Deactivate()
{
	active = false;
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
	assert(active);
	drawPos = { int(hitbox.pos.x) - bulSideOff, int(hitbox.pos.y) - bulSideOff };
	curDrawFrame = int(curAnimTime * nSpritesBulletSideE / maxAnimTime);
}

void Earth0b::BulletSideE::Draw(const std::vector<Surface>& sprites, const RectI& curRect, Graphics& gfx) const
{
	gfx.DrawSprite(drawPos.x, drawPos.y, sprites[curDrawFrame], curRect);
}

bool Earth0b::BulletSideE::GetActive() const
{
	return active;
}

void Earth0b::BulletSideE::Deactivate()
{
	active = false;
}
