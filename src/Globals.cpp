#include "Globals.h"

const bool operator == (const Coord &v1, const Coord &v2)
{
	if ((v1.x == v2.x) && (v1.y == v2.y))
		return true;
	return false;
}
const bool operator != (const Coord &v1, const Coord &v2)
{
	if (!(v1 == v2))
		return true;
	return false;
}

/*Check pressing button
return 1 - if pressed
return 0 - if not*/
bool keydown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

/*Show cursor
input true - show
input false - hide*/
BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

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
int Color(string c)
{
	enum ConsoleColor
	{
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
		green
	};
	if (c == "black")
	{
		HANDLE hStdOut0 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut0, (WORD)black);
		return black;
	}
	else if (c == "dark_blue")
	{
		HANDLE hStdOut1 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut1, (WORD)dark_blue);
		return dark_blue;
	}
	else if (c == "dark_green")
	{
		HANDLE hStdOut2 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut2, (WORD)dark_green);
		return dark_green;
	}
	else if (c == "cyan")
	{
		HANDLE hStdOut3 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut3, (WORD)cyan);
		return cyan;
	}
	else if (c == "dark_red")
	{
		HANDLE hStdOut4 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut4, (WORD)dark_red);
		return dark_red;
	}
	else if (c == "purple")
	{
		HANDLE hStdOut5 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut5, (WORD)purple);
		return purple;
	}
	else if (c == "dark_yellow")
	{
		HANDLE hStdOut6 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut6, (WORD)dark_yellow);
		return dark_yellow;
	}
	else if (c == "white")
	{
		HANDLE hStdOut7 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut7, (WORD)white);
		return white;
	}
	else if (c == "grey")
	{
		HANDLE hStdOut8 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut8, (WORD)grey);
		return grey;
	}
	else if (c == "blue")
	{
		HANDLE hStdOut9 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut9, (WORD)blue);
		return blue;
	}
	else if (c == "green")
	{
		HANDLE hStdOut10 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut10, (WORD)green);
		return green;
	}
	else
	{
		cerr << endl << "ERROR:WRONG COLOR INPUT!";
		assert(false);
	}
	return white;

	//test
	if (c == "test")
	{
		HANDLE hStdOut6 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut6, 3);
	}
}

/*Set cursor position X, Y*/
void SetCursor(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
}

/*Get cursor coords
Coord = 'X' or 'Y'*/
int GetCursor(char Coord)
{
	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
	if (Coord == 'X' || Coord == 'x')
		return bi.dwCursorPosition.X;
	else if (Coord == 'Y' || Coord == 'y')
		return bi.dwCursorPosition.Y;
	cerr << "GetCursor ERROR! Coord is incorrect!";
	assert(false);
	return 0;
}

/*Randomize random function
use only ones*/
void randomize()
{
	srand(time(0));
}

/*Return random number from 1,
to input*/
unsigned short int random(unsigned short int c)
{
	return 1 + rand() % c;
}

/*Selectable menu, from vector <string>
on position on screen int, int,
unsigned short int - already selected
return -1 - Escape
return int - index vector <sting>*/
int ChooseVertical(vector <string> v, int x, int y, unsigned short int wasChosen, bool includeArrows)
{
	int cy = wasChosen;
	ShowConsoleCursor(false);
	for (int i = 0; i < v.size(); i++)
	{
		SetCursor(x + 2, y + i);
		cout << v[i];
	}
	SetCursor(x, cy + y);
	cout << '>';
	while (true)
	{
		int key;
		key = _getch();
		if (key == VK_RETURN || (key == 77 && includeArrows))
		{
			ShowConsoleCursor(true);
			return cy;
		}
		else if (key == VK_ESCAPE || (key == 75 && includeArrows))
		{
			ShowConsoleCursor(true);
			return -1;
		}
		else
		{
			switch (key)
			{
			case 72:
				if (cy > 0)
				{
					cout << "\b ";
					cy--;
				}
				else
				{
					cout << "\b ";
					cy = v.size() - 1;
				}
				break; //UP

			case 80:
				if (cy < v.size() - 1)
				{
					cout << "\b ";
					cy++;
				}
				else
				{
					cout << "\b ";
					cy = 0;
				}
				break; //DOWN
			}
			SetCursor(x, cy + y);
			cout << '>';
		}
	}
	//if error return -10
	return -10;
}

/*Selectable menu, from vector <string>
on position on screen int, int,
unsigned short int - already selected
return int - index vector <sting>*/
int ChooseVerticalNoEscape(vector <string> v, int x, int y, unsigned short int wasChosen, bool includeArrows)
{
	int cy = wasChosen;
	ShowConsoleCursor(false);
	for (int i = 0; i < v.size(); i++)
	{
		SetCursor(x + 2, y + i);
		cout << v[i];
	}
	SetCursor(x, cy + y);
	cout << '>';
	while (true)
	{
		int key;
		key = _getch();
		if (key == VK_RETURN || (key == 77 && includeArrows))
		{
			ShowConsoleCursor(true);
			return cy;
		}
		else
		{
			switch (key)
			{
			case 72:
				if (cy > 0)
				{
					cout << "\b ";
					cy--;
				}
				else
				{
					cout << "\b ";
					cy = v.size() - 1;
				}
				break; //UP

			case 80:
				if (cy < v.size() - 1)
				{
					cout << "\b ";
					cy++;
				}
				else
				{
					cout << "\b ";
					cy = 0;
				}
				break; //DOWN
			}
			SetCursor(x, cy + y);
			cout << '>';
		}
	}
	//if error return -10
	return -10;
}

/*Render already selected ChooseVerical(...)
if last int = -1 No selected*/
void ChooseVerticalRender(vector <string> v, int x, int y, int wasChosen)
{
	int cy = wasChosen;
	ShowConsoleCursor(false);
	for (int i = 0; i < v.size(); i++)
	{
		SetCursor(x + 2, y + i);
		cout << v[i];
	}
	if (wasChosen > -1)
	{
		SetCursor(x, cy + y);
		cout << '>';
	}
	ShowConsoleCursor(true);
}