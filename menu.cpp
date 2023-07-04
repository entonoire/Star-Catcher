#include "menu.h"
#include <iostream>
#include "Item.h"
#include <Windows.h>
#include "display.h"

using namespace util;
using namespace std;
using namespace colorCode;
using namespace tool;

Menu::Item Menu::selectedItem = Menu::Item::play;
Menu::Item Menu::oldSelectedItem = Menu::Item::quit;
bool Menu::open = true;
wstring tips[3] = { L"You can zoom with CTRL + SCROLL.", L"Press R to force reload the game.", L"This thing is in beta so be carefull!" };


bool Menu::isOpen() { return open; }

void Menu::setState(bool state) 
{ 
    Menu::selectedItem = Menu::Item::play;
    Menu::oldSelectedItem = Menu::Item::quit;
    open = state;

}


Menu::Item Menu::getSelectedItem() { return Menu::selectedItem; }

void Menu::setSelectedItem(Item newItem) { Menu::selectedItem = newItem; }


void Menu::display(bool& refresh) {
    if (selectedItem != oldSelectedItem || refresh)
    {
        system("cls");
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        FlushConsoleInputBuffer(hConsole);


        // menu top
        wcout << topLeftCorner << wstring(48, horizontalLine) << topRightCorner << endl;
        wcout << verticalLine << "                  ";

        SetConsoleTextAttribute(hConsole, title);
        wcout << underline << "Star Catcher";
        SetConsoleTextAttribute(hConsole, baseColor);

        wcout << "                  " << verticalLine << endl;
        wcout << verticalLine << wstring(48, ' ') << verticalLine << endl;


        // play top
        wcout << verticalLine;
        if (selectedItem == Menu::play) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << "   " << topLeftCorner << wstring(16, horizontalLine) << topRightCorner << "    ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // scoreboard top
        wcout << "  ";
        if (selectedItem == Menu::scoreboard) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << topLeftCorner << wstring(16, horizontalLine) << topRightCorner;
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << "   " << verticalLine << endl;

        // play middle
        wcout << verticalLine << "   ";
        if (selectedItem == Menu::play) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << verticalLine << "      PLAY      " << verticalLine << "      ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // scoreboard middle
        if (selectedItem == Menu::scoreboard) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << verticalLine << "   SCOREBOARD   " << verticalLine;
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << "   " << verticalLine << endl;

        // play bottom
        wcout << verticalLine << "   ";
        if (selectedItem == Menu::play) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner << "      ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // scoreboard bottom
        if (selectedItem == Menu::scoreboard) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner << "   ";
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << verticalLine << endl;


        // quit top
        wcout << verticalLine;
        if (selectedItem == Menu::quit) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << "   " << topLeftCorner << wstring(16, horizontalLine) << topRightCorner << "    ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // option top
        wcout << "  ";
        if (selectedItem == Menu::option) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << topLeftCorner << wstring(16, horizontalLine) << topRightCorner;
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << "   " << verticalLine << endl;

        // quit middle
        wcout << verticalLine << "   ";
        if (selectedItem == Menu::quit) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << verticalLine << "      QUIT      " << verticalLine << "      ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // option middle
        if (selectedItem == Menu::option) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << verticalLine << "     OPTION     " << verticalLine;
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << "   " << verticalLine << endl;

        // quit bottom
        wcout << verticalLine << "   ";
        if (selectedItem == Menu::quit) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner << "      ";
        SetConsoleTextAttribute(hConsole, baseColor);

        // option bottom
        if (selectedItem == Menu::option) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
        wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner << "   ";
        SetConsoleTextAttribute(hConsole, baseColor);
        wcout << verticalLine << endl;


        // menu bottom
        wcout << verticalLine << wstring(48, ' ') << verticalLine << endl;
        wcout << bottomLeftCorner << wstring(48, horizontalLine) << bottomRightCorner << endl;


        wcout << endl << "Tip: " << tips[random(0, 2)] << endl;
        if (Display::debugMsg != L"") wcout << "Debug: " << Display::debugMsg;

        oldSelectedItem = selectedItem;
        refresh = false;
    }

}