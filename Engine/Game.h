/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Player.h"
#include "HUD.h"
#include "Earth0a.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	HUD hud;
	Player player0;
	Player player1;
	// move to level
	std::vector<Earth0a> enemiesTest;
	std::vector<Surface> spritesEarth0a;
	const RectF movementRegionEarth0a{ float(-Earth0a::spriteEarth0aWidth), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteEarth0aHeight), float(Graphics::GameHeight) };
	std::vector<Surface> spritesBullet;
	const RectF movementRegionEarth0aBullet{ float(-Earth0a::spriteBulletDim), float(Graphics::ScreenWidth),
		float(-Earth0a::spriteBulletDim), float(Graphics::GameHeight) };
	// move end here
	bool multiplayer = true;
	int nSubrames = 12;
	/********************************/
};