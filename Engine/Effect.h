#pragma once

#include "Graphics.h"
#include "Rect.h"
#include <vector>

class Effect
{
public:
	enum class EffectType
	{
		PlayerBulCent,
		PlayerBulSide,
		PlayerBulAim,
		PlayerBulPier
	};
public:
	Effect(float duration, const VecI& posDraw, EffectType effect);
	void Update(float dt);
	bool Expired() const;
	int GetCurEffInt() const;
	int GetPosX() const;
	int GetPosY() const;
private:
	float curDur;
	VecI pos;
	EffectType curEff;
};