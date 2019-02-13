#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Snake.h"
#include "Settings.h"
#include "Walls.h"

//Name and version
#define NAME L"Змейка v1.7"

//true - play
//false - exit
bool menu(sf::RenderWindow &window, Settings& settings)
{
	sf::RectangleShape wall(sf::Vector2f(600.f, 650.f));
	wall.setFillColor(sf::Color::Cyan);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
		cerr << "Error : not founded \"arial.ttf\"";
		return 1;
	}

	struct Button
	{
		sf::RectangleShape body;
		sf::Text text;
		sf::Font font;
		Button(sf::Vector2f v, sf::Color c, const sf::String s, sf::Color tc, int size, sf::Font& font)
		{
			this->font = font;
			body.setSize(v);
			body.setFillColor(c);
			text.setFont(font);
			text.setString(s);
			text.setFillColor(tc);
			text.setCharacterSize(size);
		}
		void SetPos(sf::Vector2f vb, sf::Vector2f vt)
		{
			body.setPosition(vb);
			text.setPosition(vt);
		}
		void SetPos(sf::Vector2f vb)
		{
			body.setPosition(vb);
			sf::FloatRect temp = text.getLocalBounds();
			float h = temp.height; // |
			float w = temp.width;  // -
			sf::Vector2f point1 = body.getPosition();
			sf::Vector2f point2 = body.getPosition() + body.getSize();
			float hb = point2.y - point1.y;
			float wb = point2.x - point1.x;
			float moveX = (wb - w) / 3;
			float moveY = (hb - h) / 3;
			text.setPosition(sf::Vector2f(moveX + vb.x, moveY + vb.y));
		}
		void render(sf::RenderWindow &window)
		{
			window.draw(body);
			window.draw(text);
		}
		bool isMouseOn(sf::RenderWindow &window)
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(window);

			sf::Vector2f point1 = body.getPosition();
			sf::Vector2f point2 = body.getPosition() + body.getSize();

			if (mouse.x >= point1.x && mouse.y >= point1.y &&
				mouse.x <= point2.x && mouse.y <= point2.y)
				return true;
			return false;
		}
		bool isMousePressed(sf::RenderWindow &window)
		{
			if (isMouseOn(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return true;
			return false;
		}
	};

	//Main menu
	Button play(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Играть", sf::Color::White, 62, font);
	play.SetPos(sf::Vector2f(200.f, 200.f));

	Button sett(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Настройки", sf::Color::White, 40, font);
	sett.SetPos(sf::Vector2f(200.f, 350.f));

	Button exit(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Выход", sf::Color::White, 62, font);
	exit.SetPos(sf::Vector2f(200.f, 480.f));

	Button record(sf::Vector2f(150.f, 100.f), sf::Color::Black, L"Рекорды", sf::Color::White, 35, font);
	record.SetPos(sf::Vector2f(425.f, 350.f));

	sf::Text title;
	// select the font
	title.setFont(font); // font is a sf::Font
	// set the string to display
	title.setString(NAME);
	// set the character size
	title.setCharacterSize(80); // in pixels, not points!
	// set the color
	title.setFillColor(sf::Color::Black);
	// set the text style
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title.setPosition(sf::Vector2f(80.f, 2.f));
	//!Main menu

	//Settings
	Button easy(sf::Vector2f(100.f, 100.f), sf::Color::Black, L"Легко", sf::Color::White, 20, font);
	easy.SetPos(sf::Vector2f(50.f, 140.f));

	Button medium(sf::Vector2f(100.f, 100.f), sf::Color::Black, L"Средне", sf::Color::Green, 20, font);
	medium.SetPos(sf::Vector2f(250.f, 140.f));

	Button hard(sf::Vector2f(100.f, 100.f), sf::Color::Black, L"Тяжело", sf::Color::White, 20, font);
	hard.SetPos(sf::Vector2f(450.f, 140.f));


	Button walls(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Стены убивают", sf::Color::Green, 20, font);
	walls.SetPos(sf::Vector2f(50.f, 350.f));

	Button nowalls(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Стены не убивают", sf::Color::White, 20, font);
	nowalls.SetPos(sf::Vector2f(350.f, 350.f));

	Button back_sett(sf::Vector2f(200.f, 100.f), sf::Color::Black, L"Назад", sf::Color::White, 62, font);
	back_sett.SetPos(sf::Vector2f(200.f, 480.f));

	sf::Text title_sett;
	// select the font
	title_sett.setFont(font); // font is a sf::Font
	// set the string to display
	title_sett.setString(L"Настройки");
	// set the character size
	title_sett.setCharacterSize(80); // in pixels, not points!
	// set the color
	title_sett.setFillColor(sf::Color::Black);
	// set the text style
	title_sett.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title_sett.setPosition(sf::Vector2f(80.f, 2.f));
	//!Settings


	//Records
	sf::Text title_rec;
	title_rec.setFont(font);
	title_rec.setString(L"Рекорды");
	title_rec.setCharacterSize(80);
	title_rec.setFillColor(sf::Color::Black);
	title_rec.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title_rec.setPosition(sf::Vector2f(110.f, 2.f));

	sf::Text wall_rec;
	wall_rec.setFont(font);
	wall_rec.setString(L"Стены убивают|");
	wall_rec.setCharacterSize(35);
	wall_rec.setFillColor(sf::Color::Black);
	wall_rec.setStyle(sf::Text::Bold);
	wall_rec.setPosition(sf::Vector2f(15.f, 100.f));

	sf::Text nowall_rec;
	nowall_rec.setFont(font);
	nowall_rec.setString(L"Стены безвредны");
	nowall_rec.setCharacterSize(35);
	nowall_rec.setFillColor(sf::Color::Black);
	nowall_rec.setStyle(sf::Text::Bold);
	nowall_rec.setPosition(sf::Vector2f(290.f, 100.f));

	sf::Text easy_rec;
	easy_rec.setFont(font);
	easy_rec.setString(L":Легко:");
	easy_rec.setCharacterSize(35);
	easy_rec.setFillColor(sf::Color::Black);
	easy_rec.setStyle(sf::Text::Bold);
	easy_rec.setPosition(sf::Vector2f(220.f, 150.f));

	sf::Text medium_rec;
	medium_rec.setFont(font);
	medium_rec.setString(L":Средне:");
	medium_rec.setCharacterSize(35);
	medium_rec.setFillColor(sf::Color::Black);
	medium_rec.setStyle(sf::Text::Bold);
	medium_rec.setPosition(sf::Vector2f(210.f, 200.f));

	sf::Text hard_rec;
	hard_rec.setFont(font);
	hard_rec.setString(L":Тяжело:");
	hard_rec.setCharacterSize(35);
	hard_rec.setFillColor(sf::Color::Black);
	hard_rec.setStyle(sf::Text::Bold);
	hard_rec.setPosition(sf::Vector2f(210.f, 250.f));

	sf::Text scorec;
	scorec.setFont(font);
	scorec.setString("0");
	scorec.setCharacterSize(35);
	scorec.setFillColor(sf::Color::Black);
	scorec.setStyle(sf::Text::Bold);
	scorec.setPosition(sf::Vector2f(20.f, 150.f));
	//!Records

	int opened_menu = 0; //0 - main 1 - settings 2 - records
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				return 0;
			}
		}
		window.clear();
		window.draw(wall);
		if (opened_menu == 0) // Main menu
		{
			if (play.isMouseOn(window))
			{
				play.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					return 1;
			}
			else
				play.body.setFillColor(sf::Color::Black);

			if (sett.isMouseOn(window))
			{
				sett.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					opened_menu = 1;
					Sleep(200);
				}
			}
			else
				sett.body.setFillColor(sf::Color::Black);

			if (exit.isMouseOn(window))
			{
				exit.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					return 0;
			}
			else
				exit.body.setFillColor(sf::Color::Black);

			if (record.isMouseOn(window))
			{
				record.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					opened_menu = 2;
					Sleep(200);
				}
			}
			else
				record.body.setFillColor(sf::Color::Black);

			window.draw(title);
			play.render(window);
			sett.render(window);
			exit.render(window);
			record.render(window);
		}
		else if (opened_menu == 1) // Settings
		{
			easy.text.setFillColor(sf::Color::White);
			medium.text.setFillColor(sf::Color::White);
			hard.text.setFillColor(sf::Color::White);
			walls.text.setFillColor(sf::Color::White);
			nowalls.text.setFillColor(sf::Color::White);

			if (settings.getTime() == 100)
				easy.text.setFillColor(sf::Color::Green);
			else if (settings.getTime() == 70)
				medium.text.setFillColor(sf::Color::Green);
			else if (settings.getTime() == 40)
				hard.text.setFillColor(sf::Color::Green);

			if (settings.getGameType() == 0)
				walls.text.setFillColor(sf::Color::Green);
			else if (settings.getGameType() == 1)
				nowalls.text.setFillColor(sf::Color::Green);

			if (easy.isMouseOn(window))
			{
				easy.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					settings.setTime(100);
			}
			else
				easy.body.setFillColor(sf::Color::Black);

			if (medium.isMouseOn(window))
			{
				medium.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					settings.setTime(70);
			}
			else
				medium.body.setFillColor(sf::Color::Black);

			if (hard.isMouseOn(window))
			{
				hard.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					settings.setTime(40);
			}
			else
				hard.body.setFillColor(sf::Color::Black);

			if (walls.isMouseOn(window))
			{
				walls.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					settings.setGameType(0);
			}
			else
				walls.body.setFillColor(sf::Color::Black);

			if (nowalls.isMouseOn(window))
			{
				nowalls.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					settings.setGameType(1);
			}
			else
				nowalls.body.setFillColor(sf::Color::Black);

			if (back_sett.isMouseOn(window))
			{
				back_sett.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					opened_menu = 0;
					Sleep(200);
				}
			}
			else
				back_sett.body.setFillColor(sf::Color::Black);

			window.draw(title_sett);
			easy.render(window);  
			medium.render(window);
			hard.render(window);
			walls.render(window);
			nowalls.render(window);
			back_sett.render(window);
		}
		else if (opened_menu == 2) // Records
		{
			if (back_sett.isMouseOn(window))
			{
				back_sett.body.setFillColor(sf::Color::Magenta);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					opened_menu = 0;
					Sleep(200);
				}
			}
			else
			back_sett.body.setFillColor(sf::Color::Black);

			char temp[17];
			//0
			scorec.setPosition(sf::Vector2f(20.f, 150.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(0), temp, 10));
			window.draw(scorec);
			//1
			scorec.setPosition(sf::Vector2f(20.f, 200.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(1), temp, 10));
			window.draw(scorec);
			//2
			scorec.setPosition(sf::Vector2f(20.f, 250.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(2), temp, 10));
			window.draw(scorec);

			//3
			scorec.setPosition(sf::Vector2f(410.f, 150.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(3), temp, 10));
			window.draw(scorec);
			//4
			scorec.setPosition(sf::Vector2f(410.f, 200.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(4), temp, 10));
			window.draw(scorec);
			//5
			scorec.setPosition(sf::Vector2f(410.f, 250.f));
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(settings.getScore(5), temp, 10));
			window.draw(scorec);

			
			

			window.draw(title_rec);
			window.draw(wall_rec);
			window.draw(nowall_rec);
			window.draw(easy_rec);
			window.draw(medium_rec);
			window.draw(hard_rec);
			back_sett.render(window);
		}
		else
			return false;
		window.display();
	}
	return true;
}

//return 1 - error
//return 0 - exit GO
int game(sf::RenderWindow &window, Settings& settings)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
		cerr << "Error : not founded \"arial.ttf\"";
		return 1;
	}

	//LOAD TEXTURES AND SPRITES
	sf::Texture thead;
	if (!thead.loadFromFile("thead.png"))
	{
		// error...
		cerr << "Error : not founded \"thead.png\"";
		return 1;
	}
	sf::Sprite shead;
	shead.setTexture(thead);

	sf::Texture ttail;
	if (!ttail.loadFromFile("ttail.png"))
	{
		// error...
		cerr << "Error : not founded \"ttail.png\"";
		return 1;
	}
	sf::Sprite stail;
	stail.setTexture(ttail);

	sf::Texture twall;
	if (!twall.loadFromFile("twall.png"))
	{
		// error...
		cerr << "Error : not founded \"twall.png\"";
		return 1;
	}
	sf::Sprite swall;
	swall.setTexture(twall);

	sf::Texture tfruit;
	if (!tfruit.loadFromFile("tfruit.png"))
	{
		// error...
		cerr << "Error : not founded \"tfruit.png\"";
		return 1;
	}
	sf::Sprite sfruit;
	sfruit.setTexture(tfruit);
	//!LOAD TEXTURES AND SPRITES

	//LOAD SOUND
	sf::SoundBuffer bfruit;
	if (!bfruit.loadFromFile("bfruit.wav"))
	{
		// error...
		cerr << "Error : not founded \"bfruit.wav\"";
	}
	sf::Sound sound_fruit;
	sound_fruit.setBuffer(bfruit);

	sf::SoundBuffer bGO;
	if (!bGO.loadFromFile("bgameover.wav"))
	{
		// error...
		cerr << "Error : not founded \"bgameover.wav\"";
	}
	sf::Sound sound_GO;
	sound_GO.setBuffer(bGO);
	//!LOAD SOUND

	Snake player(shead, stail, 260, 260);
	Coord *head = player.getPos();
	List<Coord> *tail = player.getTail();
	Walls walls(swall);
	Fruit fruit(sfruit, head, tail);

	///Delete sound error
	SetCursor(0, 4);
	for (int i = 0; i < 110; i++)
		cout << ' ';
	SetCursor(0, 5);
	///Delete sound error

	//Score:
	sf::Text score;
	score.setFont(font);
	score.setString(L"Количество очков:");
	score.setCharacterSize(40);
	score.setFillColor(sf::Color::White);
	score.setStyle(sf::Text::Bold);
	score.setPosition(sf::Vector2f(2.f, 600.f));

	sf::Text scorec;
	scorec.setFont(font);
	scorec.setString("0");
	scorec.setCharacterSize(40);
	scorec.setFillColor(sf::Color::White);
	scorec.setStyle(sf::Text::Bold);
	scorec.setPosition(sf::Vector2f(375.f, 600.f));
	//!Score

	bool isGO = false; //isGameOver?
	sf::Clock clock; // starts the clock
	while (window.isOpen() && !isGO)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{	
				Sleep(400);
				return 0;
			}
		}

		sf::Time timePassed = clock.getElapsedTime();

		player.ChangeRotationKeyboard();

		if (timePassed.asMilliseconds() > settings.getTime())
		{
			if (settings.getGameType() == 0)
				isGO = !player.stepWalls(fruit, sound_fruit);
			else if (settings.getGameType() == 1)
				isGO = !player.stepNoWalls(fruit, sound_fruit);

			char temp[17];
			#pragma warning(suppress : 4996)
			scorec.setString((sf::String)itoa(player.getCount(), temp, 10));

			clock.restart();
		}

		window.clear();
		player.render(window);
		walls.render(window);
		fruit.render(window);
		window.draw(score);
		window.draw(scorec);
		window.display();
	}

	//Save score
	int type_score;
	if (settings.getGameType() == 0)
	{
		if (settings.getTime() == 100)
		{
			type_score = 0;
		}
		else if (settings.getTime() == 70)
		{
			type_score = 1;
		}
		else if (settings.getTime() == 40)
		{
			type_score = 2;
		}
	}
	else if (settings.getGameType() == 1)
	{
		if (settings.getTime() == 100)
		{
			type_score = 3;
		}
		else if (settings.getTime() == 70)
		{
			type_score = 4;
		}
		else if (settings.getTime() == 40)
		{
			type_score = 5;
		}
	}
	settings.updateScore(player.getCount(), type_score);
	//!Save score

	//Game over text
	sf::Text go_text;
	go_text.setFont(font);
	go_text.setString(L"Game Over");
	go_text.setCharacterSize(70);
	go_text.setStyle(sf::Text::Bold);
	go_text.setPosition(sf::Vector2f(100.f, 240.f));
	go_text.setFillColor(sf::Color(255, 255, 255, 128));
	int counter = 0;
	//!Game over text

	sound_GO.play();
	clock.restart();
	while (window.isOpen() && !(clock.getElapsedTime().asSeconds() > 7))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Sleep(400);
				return 0;
			}
		}

		if (clock.getElapsedTime().asSeconds() <= 3)
			go_text.setFillColor(sf::Color(255, 255, 255, clock.getElapsedTime().asSeconds() * 85));

		window.clear();
		player.render(window);
		walls.render(window);
		fruit.render(window);
		window.draw(score);
		window.draw(scorec);
		window.draw(go_text);
		window.display();
	}

	return 0;
}

#endif