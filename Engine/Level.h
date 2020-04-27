#pragma once

#include "Earth0a.h"
#include "Earth0b.h"

class Level
{
public:
	enum class LvlType
	{
		MainMenu,
		Earth0
	};
public:
	void StartEarth0();
	void SpawnEarth0(float dt);
	void UpdateEarth0(Player& player0, Player& player1, bool multiplayer, float dt);
	void DrawEarth0(Graphics& gfx) const;
	bool IsStarted() const;
	bool SetFailed(const Player& player0, const Player& player1, bool multiplayer);
	bool GetFailed() const;
private:
	void ad();
private:
	int curSpawn = 0;
	float spawnTimer = 0.0f;
	float timer = 0.0f;
	float score = 0.0f;
	LvlType curLvl = LvlType::MainMenu;
	bool started = false;
	bool failed = false;

	// Enemies

	// Earth

	// Earth0a stats
	std::vector<Earth0a> enEarth0a;
	std::vector<Surface> spritesEarth0a;
	const RectF movRegEarth0a{ float(-Earth0a::spriteEarth0aWidth), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteEarth0aHeight), float(Graphics::GameHeight) };
	std::vector<Surface> spritesEarth0aBullet;
	const RectF movRegEarth0aBullet{ float(-Earth0a::spriteBulletDim), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteBulletDim), float(Graphics::GameHeight) };

	// Earth0b stats
	std::vector<Earth0b> enEarth0b;
	std::vector<Surface> spritesEarth0b;
	const RectF movRegEarth0b{ float(-Earth0b::spriteEarth0bWidth), float(Graphics::ScreenWidth),
		float(-Earth0b::spriteEarth0bHeight), float(Graphics::GameHeight) };
	std::vector<Surface> spritesEarth0bBulletCent;
	const RectF movRegEarth0bBulletCent{ float(-Earth0b::spriteBulletCentEDim), float(Graphics::ScreenWidth),
		float(-Earth0b::spriteBulletCentEDim), float(Graphics::GameHeight) };
};