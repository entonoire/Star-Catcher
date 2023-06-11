#include "option.h"
#include <iostream>
#include <Windows.h>
#include "menu.h"
using namespace std;
using namespace colorCode;


bool Option::open = false;

bool Option::isOpen() { return Option::open; }

void Option::setState(bool newState) { Option::open = newState; }


void Option::display(bool& refresh)
{
	if (refresh)
	{
		system("cls");
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		FlushConsoleInputBuffer(hConsole);

		cout << " -----------------------------------------------" << endl;
		
		// title
		cout << "|                    ";
		SetConsoleTextAttribute(hConsole, title);
		cout << underline << "OPTIONS";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "                    |" << endl;

		cout << "|                                               |" << endl;

		// appearance top
		cout << "|   ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "----------------";
		SetConsoleTextAttribute(hConsole, baseColor);

		// appearance selection top
		cout << "    |     ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "-------------";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |" << endl;


		// appearance middle
		cout << "| ";
		SetConsoleTextAttribute(hConsole, color);
		cout << ">|   APPEARANCE   |<";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "  |   ";

		// appearance selection middle
		SetConsoleTextAttribute(hConsole, selectColor);
		cout << "<";
		SetConsoleTextAttribute(hConsole, color);
		cout << "|    o ";
		cout << bold << "x";
		SetConsoleTextAttribute(hConsole, color);
		cout << " @    |";
		SetConsoleTextAttribute(hConsole, selectColor);
		cout << ">";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "   |" << endl;

		// appearance bottom
		cout << "|   ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |     ";

		// appearance selection bottom
		SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |" << endl;

		// back top
		cout << "|   ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "---------------";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |                       |" << endl;

		// back middle
		cout << "|  ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "|      BACK      |";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "   |                       |" << endl;

		// back bottom
		cout << "|   ";
		SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |                       |" << endl;

		cout << " -----------------------------------------------" << endl;


		refresh = false;
	}

}