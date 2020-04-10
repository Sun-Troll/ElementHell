#include "HUD.h"

void HUD::Draw(float PlHpMax, float PlHpCur, Graphics& gfx) const
{
	gfx.DrawSpriteNonChroma(basePosX, basePosY, base);
	gfx.DrawHudBar(barPosX, hpBarPosY, int(hpCurWidth * PlHpCur / PlHpMax), hpCur);
}
