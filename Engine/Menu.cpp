#include "Menu.h"
#include <cassert>
#include <fstream>

void Menu::Select(bool up, bool down, bool left, bool right, bool confirm, bool back)
{
	if ((up || down) && !secondStatsUp)
	{
		upDown.Play();
	}
	if (curState == State::Main)
	{
		assert(!secondStatsUp);
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
				startGame.Play();
			}
			else if (curSelectMain == SelectionMain::LoadGame)
			{
				curState = State::Load;
				confirmS.Play();
			}
		}
	}
	else if (curState == State::Hub)
	{
		assert(!secondStatsUp);
		if (left || right)
		{
			upDown.Play();
		}
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
				startLevel.Play();
			}
			else if (curSelectHub == SelectionHub::Stats)
			{
				statsTemp = stats0;
				curState = State::StatsUp;
				confirmS.Play();
			}
			else if (curSelectHub == SelectionHub::Save)
			{
				curState = State::Save;
				confirmS.Play();
			}
		}
	}
	else if (curState == State::StatsUp && !secondStatsUp)
	{
		assert(!secondStatsUp);
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
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::LifeSteal:
					if (statsTemp.lifeSteal > 0)
					{
						--statsTemp.lifeSteal;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm > 0)
					{
						--statsTemp.rpm;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent > 0)
					{
						--statsTemp.dmgCent;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide > 0)
					{
						--statsTemp.dmgSide;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::RapidFire:
					if (statsTemp.rapidFire > 0)
					{
						--statsTemp.rapidFire;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::PierceShot:
					if (statsTemp.pierceShot > 0)
					{
						--statsTemp.pierceShot;
						++statsTemp.points;
						statDown.Play();
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
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::LifeSteal:
					if (statsTemp.lifeSteal < 5)
					{
						++statsTemp.lifeSteal;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm < 5)
					{
						++statsTemp.rpm;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent < 5)
					{
						++statsTemp.dmgCent;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide < 5)
					{
						++statsTemp.dmgSide;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::RapidFire:
					if (statsTemp.rapidFire < 5)
					{
						++statsTemp.rapidFire;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::PierceShot:
					if (statsTemp.pierceShot < 5)
					{
						++statsTemp.pierceShot;
						--statsTemp.points;
						statUp.Play();
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
			cancel.Play();
		}
		if (confirm)
		{
			stats0 = statsTemp;
			curState = State::Hub;
			confirmS.Play();
		}
	}
	else if (curState == State::Save || curState == State::Load)
	{
		assert(!secondStatsUp);
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
			cancel.Play();
		}
		if (confirm)
		{
			if (curState == State::Save)
			{
				const std::string filename = "Saves\\save" + std::to_string(int(curSelectSaveLoad)) + ".dat";
				std::ofstream saveFile(filename, std::ios::binary);
				saveFile.write(reinterpret_cast<char*>(&stats0), sizeof(stats0));
				saveFile.write(reinterpret_cast<char*>(&stats1), sizeof(stats1));
				curState = State::Hub;
				confirmS.Play();
			}
			else if (curState == State::Load)
			{
				const std::string filename = "Saves\\save" + std::to_string(int(curSelectSaveLoad)) + ".dat";
				std::ifstream loadFile(filename, std::ios::binary);
				if (loadFile)
				{
					loadFile.read(reinterpret_cast<char*>(&stats0), sizeof(stats0));
					loadFile.read(reinterpret_cast<char*>(&stats1), sizeof(stats1));
					curState = State::Hub;
					startGame.Play();
				}
				else
				{
					loadFail.Play();
				}
			}
		}
	}
}

void Menu::SelectMultiplayer(bool up, bool down, bool left, bool right, bool confirm, bool back)
{
	if ((up || down) && secondStatsUp)
	{
		upDown.Play();
	}
	if (curState == State::Hub)
	{
		assert(!secondStatsUp);
		if (confirm && curSelectHub == SelectionHub::Stats)
		{
			secondStatsUp = true;
			statsTemp = stats1;
			curState = State::StatsUp;
			confirmS.Play();
		}
	}
	else if (secondStatsUp)
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
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::LifeSteal:
					if (statsTemp.lifeSteal > 0)
					{
						--statsTemp.lifeSteal;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm > 0)
					{
						--statsTemp.rpm;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent > 0)
					{
						--statsTemp.dmgCent;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide > 0)
					{
						--statsTemp.dmgSide;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::RapidFire:
					if (statsTemp.rapidFire > 0)
					{
						--statsTemp.rapidFire;
						++statsTemp.points;
						statDown.Play();
					}
					break;
				case Menu::SelectionStats::PierceShot:
					if (statsTemp.pierceShot > 0)
					{
						--statsTemp.pierceShot;
						++statsTemp.points;
						statDown.Play();
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
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::LifeSteal:
					if (statsTemp.lifeSteal < 5)
					{
						++statsTemp.lifeSteal;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::Rpm:
					if (statsTemp.rpm < 5)
					{
						++statsTemp.rpm;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::DmgCent:
					if (statsTemp.dmgCent < 5)
					{
						++statsTemp.dmgCent;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::DmgSide:
					if (statsTemp.dmgSide < 5)
					{
						++statsTemp.dmgSide;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::RapidFire:
					if (statsTemp.rapidFire < 5)
					{
						++statsTemp.rapidFire;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				case Menu::SelectionStats::PierceShot:
					if (statsTemp.pierceShot < 5)
					{
						++statsTemp.pierceShot;
						--statsTemp.points;
						statUp.Play();
					}
					break;
				default:
					break;
				}
			}
		}
		if (back)
		{
			secondStatsUp = false;
			curState = State::Hub;
			cancel.Play();
		}
		if (confirm)
		{
			secondStatsUp = false;
			stats1 = statsTemp;
			curState = State::Hub;
			confirmS.Play();
		}
	}
}

void Menu::LvlQuit()
{
	assert(curState == State::Level);
	curState = State::Hub;
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
		for (int n = 0; n < statsTemp.lifeSteal; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 230, statsUpgr);
		}
		for (int n = 0; n < statsTemp.rpm; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 330, statsUpgr);
		}
		for (int n = 0; n < statsTemp.dmgCent; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 430, statsUpgr);
		}
		for (int n = 0; n < statsTemp.dmgSide; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 530, statsUpgr);
		}
		for (int n = 0; n < statsTemp.rapidFire; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 630, statsUpgr);
		}
		for (int n = 0; n < statsTemp.pierceShot; ++n)
		{
			gfx.DrawSpriteNonChroma(230 + n * 60, 830, statsUpgr);
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

const Stats& Menu::GetStats(bool secondP) const
{
	if (secondP)
	{
		return stats1;
	}
	else
	{
		return stats0;
	}
}
