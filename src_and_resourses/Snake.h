#ifndef SNAKE_H
#define SNAKE_H

#include "Globals.h"
#include "List.h"
#include "Fruit.h"

class Snake
{
private:
	sf::Sprite shead;
	int rhead; // 0-up 1-right 2-down 3-left
	int oldr;
	sf::Sprite stail;

	Coord pos;
	List<Coord> tail;
	int count;
public:
	Snake(sf::Sprite, sf::Sprite, int x = 0, int y = 0);
	void ChangeRotation(int);
	void ChangeRotationKeyboard();
	bool isTouchTail();
	bool isOutsideBox(int x1, int y1, int x2, int y2);
	bool isTouchFruit(Fruit&);
	bool stepWalls(Fruit &f, sf::Sound&);
	bool stepNoWalls(Fruit &f, sf::Sound&);

	void render(sf::RenderWindow&);
	Coord* getPos();
	List<Coord>* getTail();
	int getCount();
};

Snake::Snake(sf::Sprite h, sf::Sprite t, int x, int y)
{
	shead = h;
	stail = t;
	rhead = oldr = 0;
	this->pos.x = x;
	this->pos.y = y;
	count = 0;
}

void Snake::ChangeRotation(int r)
{
	//Check back rotation
	if (oldr == 0 && r == 2)
		return;
	if (oldr == 1 && r == 3)
		return;
	if (oldr == 2 && r == 0)
		return;
	if (oldr == 3 && r == 1)
		return;

	rhead = r;
}

void Snake::ChangeRotationKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		ChangeRotation(3);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		ChangeRotation(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		ChangeRotation(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		ChangeRotation(2);
	}
}

bool Snake::isTouchTail()
{
	if (tail.isInside(pos,
		[](Coord c1, Coord c2) -> bool
	{
		if (c1.x == c2.x && c1.y == c2.y)
			return true;
		else
			return false;
	}))
		return true;
	return false;
}
bool Snake::isOutsideBox(int x1, int y1, int x2, int y2)
{
	if (pos.x > x1 && pos.y > y1 &&
		pos.x < x2 && pos.y < y2)
		return false;
	return true;
}
bool Snake::isTouchFruit(Fruit &f)
{
	if (pos.x == f.getX() && pos.y == f.getY())
		return true;
	return false;
}
bool Snake::stepWalls(Fruit &f, sf::Sound &s)
{
	Coord old = pos;
	switch (rhead)
	{
	case 0: pos.y -= 20;
		break;
	case 1: pos.x += 20;
		break;
	case 2: pos.y += 20;
		break;
	case 3: pos.x -= 20;
		break;
	}
	oldr = rhead;
	tail.pushFront(old);
	if (isTouchTail())
	{
		return false; //Game Over
	}
	else if (isOutsideBox(19, 19, 579, 579))
	{
		return false; //Game Over
	}
	else if (isTouchFruit(f))
	{
		s.play();
		count++;
		f.spawn();
	}
	else
		tail.popBack();
	return true;
}

bool Snake::stepNoWalls(Fruit &f, sf::Sound &s)
{
	Coord old = pos;
	switch (rhead)
	{
	case 0: pos.y -= 20;
		break;
	case 1: pos.x += 20;
		break;
	case 2: pos.y += 20;
		break;
	case 3: pos.x -= 20;
		break;
	}
	oldr = rhead;
	tail.pushFront(old);

	if (pos.x < 19)
	{
		pos.x = 560;
	}
	else if (pos.y < 19)
	{
		pos.y = 560;
	}
	else if (pos.x > 579)
	{
		pos.x = 20;
	}
	else if (pos.y > 579)
	{
		pos.y = 20;;
	}

	if (isTouchTail())
	{
		return false; //Game Over
	}
	else if (isTouchFruit(f))
	{
		s.play();
		count++;
		f.spawn();
	}
	else
		tail.popBack();
	return true;
}

void Snake::render(sf::RenderWindow &window)
{
	Coord p;
	p.x = pos.x;
	p.y = pos.y;
	switch (rhead)
	{
	case 0: shead.setRotation(0.f);
		break;
	case 1: shead.setRotation(90.f);
		p.x += 20;
		break;
	case 2: shead.setRotation(180.f);
		p.x += 20;
		p.y += 20;
		break;
	case 3: shead.setRotation(270.f);
		p.y+= 20;
		break;
	}
	shead.setPosition(sf::Vector2f((float)p.x, (float)p.y));
	window.draw(shead);
	for (int i = 0; i < count; i++)
	{
		stail.setPosition(sf::Vector2f((float)tail.at(i).x, (float)tail.at(i).y));
		window.draw(stail);
	}
}

Coord* Snake::getPos()
{
	return &pos;
}
List<Coord>* Snake::getTail()
{
	return &tail;
}

int Snake::getCount()
{
	return count;
}

#endif // !SNAKE_H

