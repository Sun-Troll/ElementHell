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

void Earth0a::Fire(float dt)
{
	if (RectF(pos, spriteEarth0aWidth, spriteEarth0aHeight).isContained(Graphics::GetGameRectF()))
	{
		const VecF earth0aCenter{ pos.x + float(spriteEarth0aWidth) / 2.0f, pos.y + float(spriteEarth0aHeight) / 2.0f };
		curFireBaseEarth0aAnim += dt;
		while (curFireBaseEarth0aAnim >= maxFireTimeEarth0aAnim)
		{
			curFireBaseEarth0aAnim -= maxFireTimeEarth0aAnim;
			/*bulletsCenter.emplace_back(BulletCenter{
				{ playerCenter.x - float(spriteBulletCenterDim) / 2.0f, playerCenter.y - float(spriteBulletCenterDim) / 2.0f },
				{ (target - playerCenter).GetNormalized() * bulletCenterSpeed } });

			const VecF bulSideBasePos{ playerCenter.x - float(spriteBulletSideDim) / 2.0f,
				playerCenter.y - float(spriteBulletSideDim) / 2.0f };
			for (int i = 0; i < nBulletsSideFired; ++i)
			{
				bulletsSide.emplace_back(BulletSide{
					{ bulSideBasePos.x + bulletSidePosVel[i].x * bulletSideSpawnDist,
					bulSideBasePos.y + bulletSidePosVel[i].y * bulletSideSpawnDist },
					{ bulletSidePosVel[i].x * bulletSideSpeed, bulletSidePosVel[i].y * bulletSideSpeed } });
			}*/
		}
	}
	else
	{
		curFireBaseEarth0aAnim = 0.0f;
	}
}

void Earth0a::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iEarth0a = int(curFireBaseEarth0aAnim * nSpritesEarth0a / maxFireTimeEarth0aAnim);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iEarth0a], gfx.GetGameRect());
}
