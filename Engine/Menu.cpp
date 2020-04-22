#include "Menu.h"

void Menu::Select(bool up, bool down, bool left, bool right, bool confirm)
{
	if (curState == State::Main)
	{
		if (up)
		{
			int temp = int(curSelectMain);
			--temp;
			if (temp < 0)
			{
				temp = int(SelectionMain::End) - 1;
			}
			curSelectMain = SelectionMain(temp);
		}
		if (down)
		{
			int temp = int(curSelectMain);
			++temp;
			if (temp >= int(SelectionMain::End))
			{
				temp = 0;
			}
			curSelectMain = SelectionMain(temp);
		}
		if (confirm)
		{
			if (curSelectMain == SelectionMain::NewGame)
			{
				curState = State::Hub;
			}
		}
	}
	else if (curState == State::Hub)
	{
		if (up)
		{
			int temp = int(curSelectHub);
			--temp;
			if (temp < 0)
			{
				temp = int(SelectionHub::End) - 1;
			}
			curSelectHub = SelectionHub(temp);
		}
		if (down)
		{
			int temp = int(curSelectHub);
			++temp;
			if (temp >= int(SelectionHub::End))
			{
				temp = 0;
			}
			curSelectHub = SelectionHub(temp);
		}
		if (left)
		{
			int temp = int(curSelectHub);
			temp -= int(SelectionHub::Stats);
			if (temp < 0)
			{
				temp = 0;
			}
			curSelectHub = SelectionHub(temp);
		}
		if (right)
		{
			int temp = int(curSelectHub);
			temp += int(SelectionHub::Stats);
			if (temp >= int(SelectionHub::End))
			{
				temp = int(SelectionHub::End) - 1;
			}
			curSelectHub = SelectionHub(temp);
		}
		if (confirm)
		{
			if (curSelectHub == SelectionHub::Earth)
			{
				curState = State::Level;
			}
		}
	}
}

Menu::State Menu::GetState() const
{
	return curState;
}

void Menu::Draw(Graphics& gfx) const
{
	if (curState == State::Main)
	{
		gfx.DrawSpriteNonChroma(0, 0, mainBack);
		gfx.DrawSprite(100, 230 + int(curSelectMain) * 200, mainHigh);
	}
	if (curState == State::Hub)
	{
		gfx.DrawSpriteNonChroma(0, 0, hubBack);
		gfx.DrawSprite(20 + int(curSelectHub) / int(SelectionHub::Stats) * 300,
			30 + int(curSelectHub) % int(SelectionHub::Stats) * 100, hubHigh);
	}
}
