#include "Earth0a.h"
#include <cassert>

Earth0a::Earth0a(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel)
{
	spritesEarth0a.resize(nSpritesEarth0a);
	for (int i = 0; i < nSpritesEarth0a; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0a\\Earth0a" + std::to_string(i) + ".bmp";
		spritesEarth0a[i] = Surface(bitmapFile);
		assert(spritesEarth0a[i].GetWidth() == spriteEarth0aWidth
			&& spritesEarth0a[i].GetHeight() == spriteEarth0aHeight);
	}
}

void Earth0a::Draw(Graphics& gfx) const
{
	gfx.DrawSprite(int(pos.x), int(pos.y), spritesEarth0a[0], gfx.GetGameRect());
}
