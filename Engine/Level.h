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
	void PrepareDrawEarth0();
	void DrawEarth0(Graphics& gfx) const;
	bool IsStarted() const;
	bool SetFailed(const Player& player0, const Player& player1, bool multiplayer);
	bool GetFailed() const;
private:
	void ad();
private:
	int curSpawn = 0;
	float spawnTimer = 5.0f;
	float timer = 0.0f;
	float score = 0.0f;
	LvlType curLvl = LvlType::MainMenu;
	bool started = false;
	bool failed = false;

	// Enemies

	// Earth

	// Earth0a stats
	std::vector<Earth0a> enEarth0a;
	std::vector<Earth0a> enEarth0aTemp;
	std::vector<Surface> spritesEarth0a;
	const RectF movRegEarth0a{ float(-Earth0a::xOffset), float(Graphics::ScreenWidth + Earth0a::xOffset),
		float(Earth0a::yOffset - Earth0a::spriteEarth0aHeight), float(Graphics::GameHeight + Earth0a::yOffset) };
	std::vector<Surface> spritesEarth0aBullet;
	const RectF movRegEarth0aBullet{ float(-Earth0a::bulOffset), float(Graphics::ScreenWidth + Earth0a::bulOffset),
		float(-Earth0a::bulOffset), float(Graphics::GameHeight + Earth0a::bulOffset) };

	// Earth0b stats
	std::vector<Earth0b> enEarth0b;
	std::vector<Earth0b> enEarth0bTemp;
	std::vector<Surface> spritesEarth0b;
	const RectF movRegEarth0b{ float(-Earth0b::xOffset), float(Graphics::ScreenWidth + Earth0b::xOffset),
		float(-Earth0b::yOffset), float(Graphics::GameHeight + Earth0b::yOffset) };
	std::vector<Surface> spritesEarth0bBulletCent;
	const RectF movRegEarth0bBulletCent{ float(-Earth0b::bulCentOff), float(Graphics::ScreenWidth + Earth0b::bulCentOff),
		float(-Earth0b::bulCentOff), float(Graphics::GameHeight + Earth0b::bulCentOff) };
	std::vector<Surface> spritesEarth0bBulletSide;
	const RectF movRegEarth0bBulletSide{ float(-Earth0b::bulSideOff), float(Graphics::ScreenWidth + Earth0b::bulSideOff),
		float(-Earth0b::bulSideOff), float(Graphics::GameHeight + Earth0b::bulSideOff) };
};