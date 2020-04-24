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
				statsTemp = stats0;
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
			if (statsTemp.points < 24)
			{
				switch (curSelectStats)
				{
				case Menu::SelectionStats::Hp:
					if (statsTemp.hp > 0)
					{
						--statsTemp.hp;
						++statsTemp.points;
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm > 0)
					{
						--statsTemp.rpm;
						++statsTemp.points;
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent > 0)
					{
						--statsTemp.dmgCent;
						++statsTemp.points;
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide > 0)
					{
						--statsTemp.dmgSide;
						++statsTemp.points;
					}
					break;
				default:
					break;
				}
			}
		}
		if (right)
		{
			if (statsTemp.points > 0)
			{
				switch (curSelectStats)
				{
				case Menu::SelectionStats::Hp:
					if (statsTemp.hp < 5)
					{
						++statsTemp.hp;
						--statsTemp.points;
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm < 5)
					{
						++statsTemp.rpm;
						--statsTemp.points;
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent < 5)
					{
						++statsTemp.dmgCent;
						--statsTemp.points;
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide < 5)
					{
						++statsTemp.dmgSide;
						--statsTemp.points;
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
		if (confirm)
		{
			stats0 = statsTemp;
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
		if (confirm)
		{
			if (curState == State::Save)
			{
				const std::string filename = "Saves\\save" + std::to_string(int(curSelectSaveLoad)) + ".dat";
				std::ofstream saveFile(filename, std::ios::binary);
				saveFile.write(reinterpret_cast<char*>(&stats0), sizeof(stats0));
				curState = State::Hub;
			}
			else if (curState == State::Load)
			{
				const std::string filename = "Saves\\save" + std::to_string(int(curSelectSaveLoad)) + ".dat";
				std::ifstream loadFile(filename, std::ios::binary);
				loadFile.read(reinterpret_cast<char*>(&stats0), sizeof(stats0));
				curState = State::Hub;
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
		for (int n = 0; n < statsTemp.points; ++n)
		{
			gfx.DrawSpriteNonChroma(225 + n % 12 * 25, 30 + n / 12 * 30, statsPoint);
		}
		for (int n = 0; n < statsTemp.hp; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 130, statsUpgr);
		}
		for (int n = 0; n < statsTemp.rpm; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 230, statsUpgr);
		}
		for (int n = 0; n < statsTemp.dmgCent; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 330, statsUpgr);
		}
		for (int n = 0; n < statsTemp.dmgSide; ++n)
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
