#include "Menu.h"
#include <fstream>

void Menu::Select(bool up, bool down, bool left, bool right, bool confirm, bool back)
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
			else if (curSelectMain == SelectionMain::LoadGame)
			{
				curState = State::Load;
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
			else if (curSelectHub == SelectionHub::Stats)
			{
				curState = State::StatsUp;
			}
			else if (curSelectHub == SelectionHub::Save)
			{
				curState = State::Save;
			}
		}
	}
	else if (curState == State::StatsUp)
	{
		if (up)
		{
			int temp = int(curSelectStats);
			--temp;
			if (temp < 0)
			{
				temp = int(SelectionStats::End) - 1;
			}
			curSelectStats = SelectionStats(temp);
		}
		if (down)
		{
			int temp = int(curSelectStats);
			++temp;
			if (temp >= int(SelectionStats::End))
			{
				temp = 0;
			}
			curSelectStats = SelectionStats(temp);
		}
		if (left)
		{
			if (stats0.points < 24)
			{
				switch (curSelectStats)
				{
				case Menu::SelectionStats::Hp:
					if (stats0.hp > 0)
					{
						--stats0.hp;
						++stats0.points;
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (stats0.rpm > 0)
					{
						--stats0.rpm;
						++stats0.points;
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (stats0.dmgCent > 0)
					{
						--stats0.dmgCent;
						++stats0.points;
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (stats0.dmgSide > 0)
					{
						--stats0.dmgSide;
						++stats0.points;
					}
					break;
				default:
					break;
				}
			}
		}
		if (right)
		{
			if (stats0.points > 0)
			{
				switch (curSelectStats)
				{
				case Menu::SelectionStats::Hp:
					if (stats0.hp < 5)
					{
						++stats0.hp;
						--stats0.points;
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (stats0.rpm < 5)
					{
						++stats0.rpm;
						--stats0.points;
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (stats0.dmgCent < 5)
					{
						++stats0.dmgCent;
						--stats0.points;
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (stats0.dmgSide < 5)
					{
						++stats0.dmgSide;
						--stats0.points;
					}
					break;
				default:
					break;
				}
			}
		}
		if (back)
		{
			curState = State::Hub;
		}
	}
	else if (curState == State::Save || curState == State::Load)
	{
		int x = 4;
		if (up)
		{
			int temp = int(curSelectSaveLoad);
			--temp;
			if (temp < 0)
			{
				temp = int(SelectionSaveLoad::End) - 1;
			}
			curSelectSaveLoad = SelectionSaveLoad(temp);
		}
		if (down)
		{
			int temp = int(curSelectSaveLoad);
			++temp;
			if (temp >= int(SelectionSaveLoad::End))
			{
				temp = 0;
			}
			curSelectSaveLoad = SelectionSaveLoad(temp);
		}
		if (back)
		{
			if (curState == State::Save)
			{
				curState = State::Hub;
			}
			else if (curState == State::Load)
			{
				curState = State::Main;
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
		gfx.DrawSprite(100, 230 + int(curSelectMain) * 200, HighL);
	}
	else if (curState == State::Hub)
	{
		gfx.DrawSpriteNonChroma(0, 0, hubBack);
		gfx.DrawSprite(20 + int(curSelectHub) / int(SelectionHub::Stats) * 300,
			30 + int(curSelectHub) % int(SelectionHub::Stats) * 100, HighS);
	}
	else if (curState == State::StatsUp)
	{
		gfx.DrawSpriteNonChroma(0, 0, statsBack);
		gfx.DrawSprite(20, 130 + int(curSelectStats) * 100, HighS);
		for (int n = 0; n < stats0.points; ++n)
		{
			gfx.DrawSpriteNonChroma(225 + n % 12 * 25, 30 + n / 12 * 30, statsPoint);
		}
		for (int n = 0; n < stats0.hp; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 130, statsUpgr);
		}
		for (int n = 0; n < stats0.rpm; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 230, statsUpgr);
		}
		for (int n = 0; n < stats0.dmgCent; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 330, statsUpgr);
		}
		for (int n = 0; n < stats0.dmgSide; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 430, statsUpgr);
		}
	}
	else if (curState == State::Save || curState == State::Load)
	{
		if (curState == State::Save)
		{
			gfx.DrawSpriteNonChroma(0, 0, safeBack);
		}
		else if (curState == State::Load)
		{
			gfx.DrawSpriteNonChroma(0, 0, loadBack);
		}
		gfx.DrawSprite(100, 130 + int(curSelectSaveLoad) * 200, HighL);
	}
}
