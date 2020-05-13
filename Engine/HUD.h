#pragma once

#include "Player.h"

class HUD
{
public:
	void Draw(float PlHpMax, float PlHpCur, int PlSideBulsN, Graphics& gfx) const;
private:
	Surface base = Surface("Sprites\\HUD\\HUDbase.bmp");
	static constexpr int basePosX = 0;
	static constexpr int basePosY = 900;
	static constexpr int barPosX = basePosX + 119;
	Surface hpCur = Surface("Sprites\\HUD\\HPCur.bmp");
	const float hpCurWidth = float(hpCur.GetWidth());
	static constexpr int hpBarPosY = basePosY + 8;
	Surface sideBullets = Surface("Sprites\\HUD\\SideBullets.bmp");
	const int sideBulletsWidth = sideBullets.GetWidth();
	static constexpr int sideBulletsPosY = hpBarPosY + 18 + 8;
	static constexpr int sideBulletsNFull = 1000;
};