#ifndef SETTINGS_H
#define SETTINGS_H

#include "Globals.h"

class Settings
{
private:
	int time;
	int volume;
	int GameType;
	fstream save;
	/* Walls
	** 0 - easy
	** 1 - middle
	** 2 - hard
	** NoWalls
	** 3 - easy
	** 4 - middle
	** 5 - hard */
	int records[6];
public:
	Settings();
	Settings(int t);

	int getTime();
	int getVolume();
	int getGameType();

	void setTime(int a);
	void setVolume(int a);
	void setGameType(int a);

	void saveScores();
	void updateScore(int score, int type);
	int getScore(int type);
};

Settings::Settings()
{
	//SaveFile
	save.open("save.data", ios::binary | ios::in | ios::out);
	if (!save)
		cerr << "ERROR save.data!";
	int temp;
	int i;
	int size = sizeof(int);
	for (i = 0; i < 6 && !save.eof(); i++)
	{
		save.read((char*)&temp, size);
		records[i] = temp;
	}
	if (--i != 5)
	{
		temp = 0;
		save.seekp(size*i, ios::beg);
		save.seekg(size*i, ios::beg);
		for (; i < 6 && !save.eof(); i++)
		{
			save.write((char*)&temp, size);
			records[i] = temp;
		}
	}
	save.seekp(0, ios::beg);
	save.seekg(0, ios::beg);
	save.close();
	//!SaveFile

	time = 70;

	volume = 100;
	GameType = 0;
}

Settings::Settings(int t)
{
	//SaveFile
	save.open("save.data", ios::binary | ios::in | ios::out);
	if (!save)
		cerr << "ERROR save.data!";
	int temp;
	int i;
	int size = sizeof(int);
	for (i = 0; i < 6 && !save.eof(); i++)
	{
		save.read((char*)&temp, size);
		records[i] = temp;
	}
	if (--i != 5)
	{
		temp = 0;
		save.seekp(size*i, ios::beg);
		save.seekg(size*i, ios::beg);
		for (; i < 6 && !save.eof(); i++)
		{
			save.write((char*)&temp, size);
			records[i] = temp;
		}
	}
	save.seekp(0, ios::beg);
	save.seekg(0, ios::beg);
	save.close();
	//!SaveFile

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

void Settings::saveScores()
{
	save.open("save.data", ios::binary | ios::out);
	int temp;
	int size = sizeof(int);
	for (int i = 0; i < 6 && !save.eof(); i++)
	{
		temp = records[i];
		save.write((char*)&temp, size);
	}
	save.close();
}
void Settings::updateScore(int score, int type)
{
	if (records[type] < score)
		records[type] = score;
	saveScores();
}

int Settings::getScore(int type)
{
	return records[type];
}

#endif