#include "HUD.h"
#include <algorithm>

void HUD::Draw(float PlHpMax, float PlHpCur, int PlSideBulsN, Graphics& gfx) const
{
	gfx.DrawSpriteNonChroma(basePosX, basePosY, base);
	gfx.DrawHudBar(barPosX, hpBarPosY, int(hpCurWidth * PlHpCur / PlHpMax), hpCur);
	gfx.DrawHudBar(barPosX, sideBulletsPosY,
		std::min(sideBulletsWidth * PlSideBulsN / sideBulletsNFull, sideBulletsWidth), sideBullets);
}
