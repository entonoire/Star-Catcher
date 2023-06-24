#include "menu.h"
#include <iostream>
#include "Item.h"
#include <Windows.h>
#include "display.h"

using namespace util;
using namespace std;
using namespace colorCode;

Menu::Item Menu::selectedItem = Menu::Item::play;
Menu::Item Menu::oldSelectedItem = Menu::Item::quit;
bool Menu::open = true;
string tips[3] = {"You can zoom with CTRL + SCROLL.", "Press R to force reload the game.", "This thing is in beta so be carefull!"};


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

        cout << " ---------------------- " << endl;
        cout << "|     ";
        SetConsoleTextAttribute(hConsole, title);
        cout << underline << "Star Catcher";
        SetConsoleTextAttribute(hConsole, baseColor);
        cout << "     |" << endl;
        cout << "|                      |" << endl;

        // play button
        cout << "|   ";
        if (selectedItem == Menu::play)
        {
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "| ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << ">|      PLAY      |<";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << " | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, color);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "|  ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "|      PLAY      |";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "  | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;

        }


        // option button
        cout << "|   ";
        if (selectedItem == Menu::option)
        {
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "| ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << ">|     OPTION     |<";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << " | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, color);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "|  ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "|     OPTION     |";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "  | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;

        }


        // quit button
        cout << "|   ";
        if (selectedItem == Menu::quit)
        {
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "| ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << ">|      QUIT      |<";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << " | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, selectColor);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, color);
            cout << "----------------";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;
            cout << "|  ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "|      QUIT      |";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "  | " << endl;
            cout << "|   ";
            SetConsoleTextAttribute(hConsole, color);
            cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
            SetConsoleTextAttribute(hConsole, baseColor);
            cout << "   |" << endl;

        }


        cout << "|                      |" << endl;
        cout << " ---------------------- " << endl;
        cout << endl << "Tip: " << tips[random(0, 2)] << endl;

        if (Display::debugMsg != "") cout << "Debug: " << Display::debugMsg;

        oldSelectedItem = selectedItem;
        refresh = false;
    }

}