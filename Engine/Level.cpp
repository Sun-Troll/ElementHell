#include "Level.h"
#include <cassert>

void Level::StartEarth0()
{
	assert(!started);
	assert(!failed);
	timer = 0.0f;
	score = 0.0f;

	// Earth0a
	spritesEarth0a.resize(Earth0a::nSpritesEarth0a);
	for (int i = 0; i < Earth0a::nSpritesEarth0a; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0a\\Earth0a" + std::to_string(i) + ".bmp";
		spritesEarth0a[i] = Surface(bitmapFile);
		assert(spritesEarth0a[i].GetWidth() == Earth0a::spriteEarth0aWidth
			&& spritesEarth0a[i].GetHeight() == Earth0a::spriteEarth0aHeight);
	}
	spritesEarth0aBullet.resize(Earth0a::nSpritesBullet);
	for (int i = 0; i < Earth0a::nSpritesBullet; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0aBul\\Earth0aBul" + std::to_string(i) + ".bmp";
		spritesEarth0aBullet[i] = Surface(bitmapFile);
		assert(spritesEarth0aBullet[i].GetWidth() == Earth0a::spriteBulletDim
			&& spritesEarth0aBullet[i].GetHeight() == Earth0a::spriteBulletDim);
	}

	// Earth0b
	spritesEarth0b.resize(Earth0b::nSpritesEarth0b);
	for (int i = 0; i < Earth0b::nSpritesEarth0b; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0b\\Earth0b" + std::to_string(i) + ".bmp";
		spritesEarth0b[i] = Surface(bitmapFile);
		assert(spritesEarth0b[i].GetWidth() == Earth0b::spriteEarth0bWidth
			&& spritesEarth0b[i].GetHeight() == Earth0b::spriteEarth0bHeight);
	}
	spritesEarth0bBulletCent.resize(Earth0b::nSpritesBulletCentE);
	for (int i = 0; i < Earth0b::nSpritesBulletCentE; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0bBul\\Earth0bBulL" + std::to_string(i) + ".bmp";
		spritesEarth0bBulletCent[i] = Surface(bitmapFile);
		assert(spritesEarth0bBulletCent[i].GetWidth() == Earth0b::spriteBulletCentEDim
			&& spritesEarth0bBulletCent[i].GetHeight() == Earth0b::spriteBulletCentEDim);
	}
	spritesEarth0bBulletSide.resize(Earth0b::nSpritesBulletSideE);
	for (int i = 0; i < Earth0b::nSpritesBulletSideE; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0bBul\\Earth0bBulS" + std::to_string(i) + ".bmp";
		spritesEarth0bBulletSide[i] = Surface(bitmapFile);
		assert(spritesEarth0bBulletSide[i].GetWidth() == Earth0b::spriteBulletSideEDim
			&& spritesEarth0bBulletSide[i].GetHeight() == Earth0b::spriteBulletSideEDim);
	}

	started = true;
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
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 150.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 4:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 200.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 5:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 250.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 6:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 300.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 7:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 350.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 8:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 400.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 9:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 450.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 10:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 500.0f }, { -10.0f, 0.0f } });
		}
		break;
	case 11:
		if (spawnTimer > 3.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 500.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 12:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 450.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 13:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 400.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 14:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 350.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 15:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 300.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 16:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 250.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 17:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 200.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 18:
		if (spawnTimer > 2.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 150.0f }, { 10.0f, 0.0f } });
		}
		break;
	case 19:
		if (spawnTimer > 2.5f)
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
	case 22:
		if (spawnTimer > 9.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { movRegEarth0b.left,  movRegEarth0b.top }, { 10.0f, 20.0f } });
		}
		break;
	case 23:
		if (spawnTimer > 5.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { movRegEarth0b.right,  movRegEarth0b.top }, { -10.0f, 20.0f } });
		}
		break;
	case 24:
		if (spawnTimer > 15.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { movRegEarth0b.left,  movRegEarth0b.top }, { 20.0f, 30.0f } });
			enEarth0b.emplace_back(Earth0b{ { movRegEarth0b.right,  movRegEarth0b.top }, { -20.0f, 30.0f } });
		}
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
	// Earth0a
	for (auto& e : enEarth0a)
	{
		if (!e.IsDead())
		{
			e.Move(dt);
			e.Fire(player0, player1, multiplayer, dt);
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

	// Earth0b
	for (auto& e : enEarth0b)
	{
		if (!e.IsDead())
		{
			e.Move(dt);
			e.Fire(player0, player1, multiplayer, dt);
			e.GetHit(player0, dt);
			if (multiplayer)
			{
				e.GetHit(player1, dt);
			}
		}
		e.UpdateBullets(movRegEarth0bBulletCent, movRegEarth0bBulletSide, dt);
		e.HitPlayer(player0);
		if (multiplayer)
		{
			e.HitPlayer(player1);
		}
	}
	for (int i = 0; i < enEarth0b.size(); ++i)
	{
		if (enEarth0b[i].IsDead() && enEarth0b[i].BulletsEmpty())
		{
			std::swap(enEarth0b[i], enEarth0b.back());
			enEarth0b.pop_back();
			--i;
		}
		else if (enEarth0b[i].Clamp(movRegEarth0b) && enEarth0b[i].BulletsEmpty())
		{
			std::swap(enEarth0b[i], enEarth0b.back());
			enEarth0b.pop_back();
			--i;
		}
	}
}

void Level::DrawEarth0(Graphics& gfx) const
{
	// Earth0a
	for (const auto& e : enEarth0a)
	{
		if (!e.IsDead())
		{
			e.Draw(spritesEarth0a, gfx);
		}
		e.DrawBullets(spritesEarth0aBullet, gfx);
	}

	// Earth0b
	for (const auto& e : enEarth0b)
	{
		if (!e.IsDead())
		{
			e.Draw(spritesEarth0b, gfx);
		}
		e.DrawBullets(spritesEarth0bBulletCent, spritesEarth0bBulletSide, gfx);
	}
}

bool Level::IsStarted() const
{
	return started;
}

bool Level::SetFailed(const Player& player0, const Player& player1, bool multiplayer)
{
	if (multiplayer)
	{
		failed = player0.GetHpCur() <= 0.0f && player1.GetHpCur() <= 0.0f;
	}
	else
	{
		failed = player0.GetHpCur() <= 0.0f;
	}
	return failed;
}

bool Level::GetFailed() const
{
	return failed;
}

void Level::ad()
{
	++curSpawn;
	spawnTimer = 0.0f;
}
