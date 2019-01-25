#ifndef FRUIT_H
#define FRUIT_H

#include "Globals.h"
#include "List.h"

class Fruit
{
private:
	sf::Sprite fruit;
	Coord pos;
	Coord *head;
	List<Coord> *tail;
public:
	Fruit(sf::Sprite, Coord*, List<Coord>*);
	void spawn();
	void render(sf::RenderWindow&);
	int getX();
	int getY();
};

Fruit::Fruit(sf::Sprite w, Coord *h, List<Coord> *t)
{
	fruit = w;
	head = h;
	tail = t;
	spawn();
}

void Fruit::spawn()
{
	do
	{
		pos.x = random(28) * 20;
		pos.y = random(28) * 20;
	} while (*head == pos || tail->isInside(pos, [](Coord c1, Coord c2) -> bool
	{
		if (c1.x == c2.x && c1.y == c2.y)
			return true;
		else
			return false;
	}));
}

void Fruit::render(sf::RenderWindow &window)
{
	fruit.setPosition(sf::Vector2f((float)pos.x, float(pos.y)));
	window.draw(fruit);
}

int Fruit::getX()
{
	return pos.x;
}

int Fruit::getY()
{
	return pos.y;
}

#endif

