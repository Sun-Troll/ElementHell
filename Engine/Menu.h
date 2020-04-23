#pragma once

#include "Graphics.h"
#include "Stats.h"

class Menu
{
public:
	enum class State
	{
		Main,
		Hub,
		StatsUp,
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
		Rpm,
		DmgCent,
		DmgSide,
		End
	};
public:
	void Select(bool up, bool down, bool left, bool right, bool confirm);
	State GetState() const;
	void Draw(Graphics& gfx) const;
private:
	const Surface mainBack = Surface("Sprites\\Menus\\MainMenu\\MainMenuBack.bmp");
	const Surface mainHigh = Surface("Sprites\\Menus\\MainMenu\\MainMenuHigh.bmp");
	const Surface hubBack = Surface("Sprites\\Menus\\HubMenu\\HubMenuBack.bmp");
	const Surface hubHigh = Surface("Sprites\\Menus\\HubMenu\\HubMenuHigh.bmp");
	const Surface statsBack = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuBack.bmp");
	const Surface statsHigh = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuHigh.bmp");
	const Surface statsUpgr = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuUpgr.bmp");
	const Surface statsPoint = Surface("Sprites\\Menus\\StatsMenu\\StatsMenuPoint.bmp");
	State curState = State::Main;
	SelectionMain curSelectMain = SelectionMain::NewGame;
	SelectionHub curSelectHub = SelectionHub::Earth;
	SelectionStats curSelectStats = SelectionStats::Hp;
	Stats stats0;
	Stats stats1;
};