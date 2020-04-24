#include "Level.h"
#include <cassert>

void Level::StartEarth0()
{
	timer = 0.0f;
	score = 0.0f;
	spritesEarth0a.resize(Earth0a::nSpritesEarth0a);
	for (int i = 0; i < Earth0a::nSpritesEarth0a; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0a\\Earth0a" + std::to_string(i) + ".bmp";
		spritesEarth0a[i] = Surface(bitmapFile);
		assert(spritesEarth0a[i].GetWidth() == Earth0a::spriteEarth0aWidth
			&& spritesEarth0a[i].GetHeight() == Earth0a::spriteEarth0aHeight);
	}
	spritesBullet.resize(Earth0a::nSpritesBullet);
	for (int i = 0; i < Earth0a::nSpritesBullet; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0aBul\\Earth0aBul" + std::to_string(i) + ".bmp";
		spritesBullet[i] = Surface(bitmapFile);
		assert(spritesBullet[i].GetWidth() == Earth0a::spriteBulletDim
			&& spritesBullet[i].GetHeight() == Earth0a::spriteBulletDim);
	}
}

void Level::SpawnEarth0(float dt)
{
	spawnTimer += dt;
	switch (curSpawn)
	{
	case 0:
		if (spawnTimer > 6.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 1:
		if (spawnTimer > 3.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 150.0f }, { -10.0f, 10.0f } });
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 150.0f }, { 10.0f, 10.0f } });
		}
		break;
	case 2:
		if (spawnTimer > 4.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 3:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 150.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 4:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 200.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 5:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 250.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 6:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 300.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 7:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 350.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 8:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 400.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 9:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 450.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 10:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 500.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 11:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 500.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 12:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 450.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 13:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 400.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 14:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 350.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 15:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 300.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 16:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 250.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 17:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 200.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 18:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 150.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 19:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 20:
		if (spawnTimer > 14.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { 120.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.top }, { 0.0f, 10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 220.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.top }, { 0.0f, 10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 320.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.top }, { 0.0f, 10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 420.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.top }, { 0.0f, 10.0f } });
		}
		break;
	case 21:
		if (spawnTimer > 8.3f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { 120.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.bottom }, { 0.0f, -10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 220.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.bottom }, { 0.0f, -10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 320.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.bottom }, { 0.0f, -10.0f } });
			enEarth0a.emplace_back(Earth0a{ { 420.0f - float(Earth0a::spriteEarth0aWidth / 2), movRegEarth0a.bottom }, { 0.0f, -10.0f } });
		}
		break;
	default:
		break;
	}
}

void Level::UpdateEarth0(Player& player0, Player& player1, bool multiplayer, float dt)
{
	/* frame rate test
	if (dt > (1.0f / 56.0f) / 12.0f)
	{
		player0.Damaged(10);
	}*/
	timer += dt;
	for (auto& e : enEarth0a)
	{
		if (!e.IsDead())
		{
			e.Move(dt);
			e.Fire(dt);
			e.GetHit(player0, dt);
			if (multiplayer)
			{
				e.GetHit(player1, dt);
			}
		}
		e.UpdateBullets(movRegEarth0aBullet, dt);
		e.HitPlayer(player0);
		if (multiplayer)
		{
			e.HitPlayer(player1);
		}
	}
	for (int i = 0; i < enEarth0a.size(); ++i)
	{
		if (enEarth0a[i].IsDead() && enEarth0a[i].BulletsEmpty())
		{
			std::swap(enEarth0a[i], enEarth0a.back());
			enEarth0a.pop_back();
			--i;
		}
		else if (enEarth0a[i].Clamp(movRegEarth0a) && enEarth0a[i].BulletsEmpty())
		{
			std::swap(enEarth0a[i], enEarth0a.back());
			enEarth0a.pop_back();
			--i;
		}
	}
}

void Level::DrawEarth0(Graphics& gfx) const
{
	for (const auto& e : enEarth0a)
	{
		if (!e.IsDead())
		{
			e.Draw(spritesEarth0a, gfx);
		}
		e.DrawBullets(spritesBullet, gfx);
	}
}

void Level::ad()
{
	++curSpawn;
	spawnTimer = 0.0f;
}
