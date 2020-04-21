#pragma once

#include "Graphics.h"

class Menu
{
public:
	enum class State
	{
		Main,
		Hub,
		Level
	};
	enum class SelectionMain
	{
		NewGame,
		LoadGame,
		QuitGame,
		End
	};
public:
	void Select(bool up, bool down, bool confirm);
	State GetState() const;
	void Draw(Graphics& gfx) const;
private:
	const Surface back = Surface("Sprites\\Menus\\MainMenu\\MainMenuBack.bmp");
	const Surface high = Surface("Sprites\\Menus\\MainMenu\\MainMenuHigh.bmp");
	State curState = State::Main;
	SelectionMain curSelectMain = SelectionMain::NewGame;
};