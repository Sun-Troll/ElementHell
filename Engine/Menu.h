#pragma once

#include "Graphics.h"
#include "Stats.h"
#include "SoundEffect.h"

class Menu
{
public:
	enum class State
	{
		Main,
		Hub,
		StatsUp,
		Save,
		Load,
		Level
	};
	enum class SelectionMain
	{
		NewGame,
		LoadGame,
		QuitGame,
		End
	};
	enum class SelectionHub
	{
		Earth,
		Ice,
		TestBullshit00,
		TestBullshit01,
		TestBullshit02,
		Stats,
		Save,
		TestBullshit10,
		End
	};
	enum class SelectionStats
	{
		Hp,
		LifeSteal,
		Rpm,
		DmgCent,
		DmgSide,
		RapidFire,
		Temp,
		PierceShot,
		End
	};
	enum class SelectionSaveLoad
	{
		Slot1,
		Slot2,
		Slot3,
		Slot4,
		End
	};
public:
	void Select(bool up, bool down, bool left, bool right, bool confirm, bool back);
	void SelectMultiplayer(bool up, bool down, bool left, bool right, bool confirm, bool back);
	void LvlQuit();
	State GetState() const;
	void Draw(Graphics& gfx) const;
	const Stats& GetStats(bool secondP) const;
private:
	const Surface HighL = Surface("Sprites\\Menus\\HighMenu\\MenuHighL.bmp");
	const Surface HighS = Surface("Sprites\\Menus\\HighMenu\\MenuHighS.bmp");
	const Surface mainBack = Surface("Sprites\\Menus\\MainMenu\\MainMenuBack.bmp");
	const Surface hubBack = Surface("Sprites\\Menus\\HubMenu\\HubMenuBack.bmp");
	const Surface statsBack = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuBack.bmp");
	const Surface statsUpgr = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuUpgr.bmp");
	const Surface statsPoint = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuPoint.bmp");
	const Surface safeBack = Surface("Sprites\\Menus\\SaveMenu\\SaveMenuBack.bmp");
	const Surface loadBack = Surface("Sprites\\Menus\\LoadMenu\\LoadMenuBack.bmp");
	Sound statUp = Sound(L"Sounds\\Menu\\StatUp.wav");
	Sound statDown = Sound(L"Sounds\\Menu\\StatDown.wav");
	Sound upDown = Sound(L"Sounds\\Menu\\UpDown.wav");
	Sound loadFail = Sound(L"Sounds\\Menu\\LoadFail.wav");
	Sound confirmS = Sound(L"Sounds\\Menu\\Confirm.wav");
	Sound cancel = Sound(L"Sounds\\Menu\\Cancel.wav");
	Sound startGame = Sound(L"Sounds\\Menu\\StartGame.wav");
	Sound startLevel = Sound(L"Sounds\\Menu\\StartLevel.wav");
	State curState = State::Main;
	SelectionMain curSelectMain = SelectionMain::NewGame;
	SelectionHub curSelectHub = SelectionHub::Earth;
	SelectionStats curSelectStats = SelectionStats::Hp;
	SelectionSaveLoad curSelectSaveLoad = SelectionSaveLoad::Slot1;
	bool secondStatsUp = false;
	Stats stats0;
	Stats stats1;
	Stats statsTemp;
};