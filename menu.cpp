﻿#include "menu.h"
#include <iostream>
#include "Item.h"
#include <Windows.h>

using namespace util;
using namespace std;

Menu::Item Menu::selectedItem = Menu::Item::play;
Menu::Item Menu::oldSelectedItem = Menu::Item::quit;
bool Menu::open = true;
string tips[3] = {"You can zoom with CTRL + SCROLL.", "Press R to force reload the game.", "This thing is in beta so be carefull!"};


bool Menu::isOpen() { return open; }

void Menu::setState(bool state) { 
    open = state;
    system("cls");

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

        int color = FOREGROUND_GREEN;
        int selectColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        int baseColor = 7;

        cout << " ---------------------- " << endl;
        cout << "|     ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "\033[4mStar Catcher";
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
        cout << endl << "Tip: " << tips[random(0, 2)];

        oldSelectedItem = selectedItem;
        refresh = false;
    }

}