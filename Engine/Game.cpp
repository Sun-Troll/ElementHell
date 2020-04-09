/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	player0({ 200.0f, 700.0f }),
	player1({ 300.0f, 700.0f })
{
	ft.FrameDur();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = ft.FrameDur();

	bool left0 = false;
	bool right0 = false;
	bool up0 = false;
	bool down0 = false;
	if (wnd.kbd.KeyIsPressed('A'))
	{
		left0 = true;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		right0 = true;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		up0 = true;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		down0 = true;
	}
	player0.Move(left0, right0, up0, down0, dt);
	player0.Clamp();
	player0.Fire(dt);
	player0.UpdateCenterBullets(dt);

	if (multiplayer)
	{
		bool left1 = false;
		bool right1 = false;
		bool up1 = false;
		bool down1 = false;
		if (wnd.kbd.KeyIsPressed(VK_NUMPAD4))
		{
			left1 = true;
		}
		if (wnd.kbd.KeyIsPressed(VK_NUMPAD6))
		{
			right1 = true;
		}
		if (wnd.kbd.KeyIsPressed(VK_NUMPAD8))
		{
			up1 = true;
		}
		if (wnd.kbd.KeyIsPressed(VK_NUMPAD5))
		{
			down1 = true;
		}
		player1.Move(left1, right1, up1, down1, dt);
		player1.Clamp();
		player1.Fire(dt);
		player1.UpdateCenterBullets(dt);
	}
}

void Game::ComposeFrame()
{
	player0.DrawBulletsCenter(gfx);
	player0.Draw(gfx);
	if (multiplayer)
	{
		player1.DrawBulletsCenter(gfx);
		player1.Draw(gfx);
	}
}
