#pragma once

#include "Earth0a.h"

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
	void UpdateEarth0(Player& player0, Player& player1, bool multiplayer, float dt);
	void DrawEarth0(Graphics& gfx) const;
private:
	float timer = 0.0f;
	int curSpawn = 0;
	float spawnTimer = 0.0f;
	float score = 0.0f;
	LvlType curLvl = LvlType::MainMenu;

	// Enemies

	//Earth

	//Earth0A stats
	std::vector<Earth0a> enemiesEarth0a;
	std::vector<Surface> spritesEarth0a;
	const RectF movementRegionEarth0a{ float(-Earth0a::spriteEarth0aWidth), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteEarth0aHeight), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBullet;
	const RectF movementRegionEarth0aBullet{ float(-Earth0a::spriteBulletDim), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteBulletDim), float(Graphics::GameHeight) };
};