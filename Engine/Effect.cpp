#include "Effect.h"

Effect::Effect(float duration, const VecI& posDraw, EffectType effect)
	:
	curDur(duration),
	pos(posDraw),
	curEff(effect)
{
}

void Effect::Update(float dt)
{
	curDur -= dt;
}

bool Effect::Expired() const
{
	return curDur <= 0.0f;
}

int Effect::GetCurEffInt() const
{
	return int(curEff);
}

int Effect::GetPosX() const
{
	return pos.x;
}

int Effect::GetPosY() const
{
	return pos.y;
}
