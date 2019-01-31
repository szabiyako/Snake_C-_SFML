#ifndef WALLS_H
#define WALLS_H

#include "Globals.h"

class Walls
{
private:
	sf::Sprite wall;
public:
	Walls(sf::Sprite);
	void render(sf::RenderWindow&);
};

Walls::Walls(sf::Sprite w)
{
	wall = w;
}


void Walls::render(sf::RenderWindow &window)
{
	wall.setPosition(sf::Vector2f(0.f, 0.f));
	wall.setRotation(0.f);
	window.draw(wall);

	wall.setPosition(sf::Vector2f(600.f, 0.f));
	wall.setRotation(90.f);
	window.draw(wall);

	wall.setPosition(sf::Vector2f(600.f, 600.f));
	wall.setRotation(180.f);
	window.draw(wall);

	wall.setPosition(sf::Vector2f(0.f, 600.f));
	wall.setRotation(270.f);
	window.draw(wall);
}

#endif

