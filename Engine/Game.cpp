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
	player0(spawnPosP0),
	player1(spawnPosP1)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	PrepareFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (menu.GetState() == Menu::State::Level)
	{
		const float frameTime = ft.FrameDur();
		float dt = frameTime / nSubrames;

		if (level.empty()) // change based on cur lvl
		{
			assert(level.empty());
			player0.Respawn(spawnPosP0, menu.GetStats(false));
			player1.Respawn(spawnPosP1, menu.GetStats(true));
			level.push_back(Level());
			level.front().StartEarth0();
		}

		else if (!level.front().GetFailed())
		{
			assert(level.size() == 1);
			for (int n = 0; n < nSubrames; ++n)
			{
				bool left0 = false;
				bool right0 = false;
				bool up0 = false;
				bool down0 = false;
				bool slow0 = false;
				if (wnd.kbd.KeyIsPressed('A') || wnd.kbd.KeyIsPressed(VK_LEFT))
				{
					left0 = true;
				}
				if (wnd.kbd.KeyIsPressed('D') || wnd.kbd.KeyIsPressed(VK_RIGHT))
				{
					right0 = true;
				}
				if (wnd.kbd.KeyIsPressed('W') || wnd.kbd.KeyIsPressed(VK_UP))
				{
					up0 = true;
				}
				if (wnd.kbd.KeyIsPressed('S') || wnd.kbd.KeyIsPressed(VK_DOWN))
				{
					down0 = true;
				}
				if (wnd.kbd.KeyIsPressed(VK_SHIFT))
				{
					slow0 = true;
				}
				player0.Move(left0, right0, up0, down0, slow0, dt);
				player0.Clamp();
				player0.Fire(dt);
				player0.UpdateBullets(dt);

				if (multiplayer)
				{
					bool left1 = false;
					bool right1 = false;
					bool up1 = false;
					bool down1 = false;
					bool slow1 = false;
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
					if (wnd.kbd.KeyIsPressed(VK_NUMPAD0))
					{
						slow1 = true;
					}
					player1.Move(left1, right1, up1, down1, slow1, dt);
					player1.Clamp();
					player1.Fire(dt);
					player1.UpdateBullets(dt);
				}

				if (true) // change based on cur lvl
				{
					level.front().SpawnEarth0(dt);
					level.front().UpdateEarth0(player0, player1, multiplayer, dt);
				}
				if (level.front().SetFailed(player0, player1, multiplayer))
				{
					break;
				}
			}
		}
		else
		{
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE) || wnd.kbd.KeyIsPressed(VK_BACK))
			{
				level.pop_back();
				assert(level.empty());
				menu.LvlQuit();
				wnd.kbd.Flush();
			}
		}
	}
	else
	{
		bool up0 = false;
		bool down0 = false;
		bool left0 = false;
		bool right0 = false;
		bool confirm0 = false;
		bool back0 = false;
		bool up1 = false;
		bool down1 = false;
		bool left1 = false;
		bool right1 = false;
		bool confirm1 = false;
		bool back1 = false;
		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsRelease())
			{
				if (e.GetCode() == 'W' || e.GetCode() == VK_UP)
				{
					up0 = true;
				}
				if (e.GetCode() == 'S' || e.GetCode() == VK_DOWN)
				{
					down0 = true;
				}
				if (e.GetCode() == 'A' || e.GetCode() == VK_LEFT)
				{
					left0 = true;
				}
				if (e.GetCode() == 'D' || e.GetCode() == VK_RIGHT)
				{
					right0 = true;
				}
				if (e.GetCode() == VK_SPACE || e.GetCode() == VK_RETURN)
				{
					confirm0 = true;
				}
				if (e.GetCode() == 'Q' || e.GetCode() == VK_ESCAPE || e.GetCode() == VK_BACK)
				{
					back0 = true;
				}
				if (multiplayer)
				{
					if (e.GetCode() == VK_NUMPAD8)
					{
						up1 = true;
					}
					if (e.GetCode() == VK_NUMPAD5)
					{
						down1 = true;
					}
					if (e.GetCode() == VK_NUMPAD4)
					{
						left1 = true;
					}
					if (e.GetCode() == VK_NUMPAD6)
					{
						right1 = true;
					}
					if (e.GetCode() == VK_NUMPAD0)
					{
						confirm1 = true;
					}
					if (e.GetCode() == VK_NUMPAD7)
					{
						back1 = true;
					}
				}
			}
		}
		menu.Select(up0, down0, left0, right0, confirm0, back0);
		if (multiplayer)
		{
			menu.SelectMultiplayer(up1, down1, left1, right1, confirm1, back1);
		}
	}
}

void Game::PrepareFrame()
{
	if (menu.GetState() == Menu::State::Level)
	{
		if (!level.empty()) // change based on cur lvl
		{
			assert(level.size() == 1);
			level.front().PrepareDrawEarth0();
		}
	}
}

void Game::ComposeFrame()
{
	if (menu.GetState() == Menu::State::Level)
	{
		hud.Draw(player0.GetHpMax(), player0.GetHpCur(), gfx);
		player0.DrawBullets(gfx);
		player0.Draw(gfx);
		if (multiplayer)
		{
			player1.DrawBullets(gfx);
			player1.Draw(gfx);
		}
		if (!level.empty()) // change based on cur lvl
		{
			assert(level.size() == 1);
			level.front().DrawEarth0(gfx);
		}
	}
	else
	{
		menu.Draw(gfx);
	}
}
