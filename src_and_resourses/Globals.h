#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
#include <tchar.h>
#include <ctime>
#include <conio.h>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Hide console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//#include <sstream>

//#define tic 100

using namespace std;

struct Coord
{
	int x;
	int y;
};

const bool operator == (const Coord &v1, const Coord &v2);
const bool operator != (const Coord &v1, const Coord &v2);

/*Check pressing button
return 1 - if pressed
return 0 - if not*/
bool keydown(int);

/*Show cursor
input true - show
input false - hide*/
BOOL ShowConsoleCursor(BOOL);

/*Set char color:
black,
dark_blue,
dark_green,
cyan,
dark_red,
purple,
dark_yellow,
white,
grey,
blue,
green*/
int Color(string);

/*Set cursor position X, Y*/
void SetCursor(int, int);

/*Get cursor coords
Coord = 'X' or 'Y'*/
int GetCursor(char Coord);

/*Randomize random function
use only ones*/
void randomize();

/*Return random number from 1,
to input*/
unsigned short int random(unsigned short int);

/*Selectable menu, from vector <string>
on position on screen int, int,
unsigned short int - already selected
return -1 - Escape
return int - index vector <sting>*/
int ChooseVertical(vector <string>, int, int, unsigned short int, bool);

/*Selectable menu, from vector <string>
on position on screen int, int,
unsigned short int - already selected
return int - index vector <sting>*/
int ChooseVerticalNoEscape(vector <string>, int, int, unsigned short int, bool);

/*Render already selected ChooseVerical(...)
if last int = -1 No selected*/
void ChooseVerticalRender(vector <string>, int, int, int);

#endif