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
			enEarth0b.emplace_back(Earth0b{ { 250.0f,  movRegEarth0b.bottom }, { 0.0f, -10.0f } });
		}
		break;
	case 1:
		if (spawnTimer > 40.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 2:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 3:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 4:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 5:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 6:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 7:
		if (spawnTimer > 1.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 8:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 9:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 10:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 11:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 12:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 13:
		if (spawnTimer > 1.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 14:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 15:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 16:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 17:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 18:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 19:
		if (spawnTimer > 1.5f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 20:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 21:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 22:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 23:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 24:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 25:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 26:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 27:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 28:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 29:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 30:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 31:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 32:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 33:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 34:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 35:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 36:
		if (spawnTimer > 0.6f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 37:
		if (spawnTimer > 2.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 2 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
		}
		break;
	case 38:
		if (spawnTimer > 4.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 4 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 4 * 3 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
		}
		break;
	case 39:
		if (spawnTimer > 6.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 2 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
		}
		break;
	case 40:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 41:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 42:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 43:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 44:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 45:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 46:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -20.0f, 10.0f } });
		}
		break;
	case 47:
		if (spawnTimer > 5.0f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 2 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
		}
		break;
	case 48:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 49:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 50:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 51:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 52:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 53:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 54:
		if (spawnTimer > 0.4f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 20.0f, 10.0f } });
		}
		break;
	case 55:
		if (spawnTimer > 5.0f)
		{
			ad();
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 2 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.top }, { 0.0f, 10.0f } });
			enEarth0b.emplace_back(Earth0b{ { Graphics::ScreenWidth / 2 - Earth0b::spriteEarth0bWidth / 2, movRegEarth0b.bottom }, { 0.0f, -10.0f } });
		}
		break;
	case 56:
		if (spawnTimer > 0.8f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -10.0f, 20.0f } });
		}
		break;
	case 57:
		if (spawnTimer > 0.2f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 10.0f, 20.0f } });
		}
		break;
	case 58:
		if (spawnTimer > 0.8f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -10.0f, 20.0f } });
		}
		break;
	case 59:
		if (spawnTimer > 0.2f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 10.0f, 20.0f } });
		}
		break;
	case 60:
		if (spawnTimer > 0.8f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -10.0f, 20.0f } });
		}
		break;
	case 61:
		if (spawnTimer > 0.2f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 10.0f, 20.0f } });
		}
		break;
	case 62:
		if (spawnTimer > 0.8f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.right, 100.0f }, { -10.0f, 20.0f } });
		}
		break;
	case 63:
		if (spawnTimer > 0.2f)
		{
			ad();
			enEarth0a.emplace_back(Earth0a{ { movRegEarth0a.left, 100.0f }, { 10.0f, 20.0f } });
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

void Level::PrepareDrawEarth0()
{
	for (auto& e : enEarth0a)
	{
		e.DrawPosUpdate();
		e.DrawPosBulletsUpdate();
	}
	for (auto& e : enEarth0b)
	{
		e.DrawPosUpdate();
		e.DrawPosBulletsUpdate();
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
