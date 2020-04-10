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

void Earth0a::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[0], gfx.GetGameRect());
}
