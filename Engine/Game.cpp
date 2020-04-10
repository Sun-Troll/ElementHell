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
#include <cassert>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	player0({ 200.0f, 700.0f }),
	player1({ 300.0f, 700.0f })
{
	spritesEarth0a.resize(Earth0a::nSpritesEarth0a);
	for (int i = 0; i < Earth0a::nSpritesEarth0a; ++i)
	{
		const std::string bitmapFile = "Sprites\\Enemies\\Earth0a\\Earth0a" + std::to_string(i) + ".bmp";
		spritesEarth0a[i] = Surface(bitmapFile);
		assert(spritesEarth0a[i].GetWidth() == Earth0a::spriteEarth0aWidth
			&& spritesEarth0a[i].GetHeight() == Earth0a::spriteEarth0aHeight);
	}
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
	const float FrameTime = ft.FrameDur();
	float dt = FrameTime / nSubrames;

	for (int n = 0; n < nSubrames; ++n)
	{
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
		player0.UpdateBullets(dt);

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
			player1.UpdateBullets(dt);
		}
		// move enemy updates to level
		if (enemiesTest.empty())
		{
			enemiesTest.emplace_back(Earth0a{ { movementRegionEarth0a.right, 100.0f }, { -2.0f, 1.0f } });
		}
		else
		{
			for (auto& e : enemiesTest)
			{
				e.Move(dt);
				e.Fire(dt);
			}
			for (int i = 0; i < enemiesTest.size(); ++i)
			{
				if (enemiesTest[i].Clamp(movementRegionEarth0a))
				{
					std::swap(enemiesTest[i], enemiesTest.back());
					enemiesTest.pop_back();
					--i;
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	hud.Draw(player0.GetHpMax(), player0.GetHpCur(), gfx);
	player0.DrawBullets(gfx);
	player0.Draw(gfx);
	if (multiplayer)
	{
		player1.DrawBullets(gfx);
		player1.Draw(gfx);
	}
	for (const auto& e : enemiesTest)
	{
		e.Draw(spritesEarth0a, gfx);
	}
}
