#ifndef SETTINGS_H
#define SETTINGS_H

#include "Globals.h"

class Settings
{
private:
	int time;
	int volume;
	int GameType;
public:
	Settings()
	{
		time = 70;
		volume = 100;
		GameType = 0;
	}
	Settings(int t);

	int getTime();
	int getVolume();
	int getGameType();

	void setTime(int a);
	void setVolume(int a);
	void setGameType(int a);
};

Settings::Settings(int t)
{
	time = t;
	volume = 100;
	GameType = 0;
}

int Settings::getTime()
{
	return time;
}

int Settings::getVolume()
{
	return volume;
}

int Settings::getGameType()
{
	return GameType;
}

void Settings::setTime(int a)
{
	time = a;
}
void Settings::setVolume(int a)
{
	volume = a;
}
void Settings::setGameType(int a)
{
	GameType = a;
}

#endif