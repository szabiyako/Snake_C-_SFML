#include "Globals.h"
#include "Game.h"
#include "Settings.h"


int main()
{
	setlocale(LC_ALL, "Russian");

	randomize();
	
	Settings settings;

	//Create window
	sf::RenderWindow window(sf::VideoMode(600, 650), "Snake");

	while (menu(window, settings) != 0)
	{
		if (game(window, settings) == 1)
			return 1;
	}
	
	return 0;
}