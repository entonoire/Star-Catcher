#include "menu.h"
#include <iostream>
#include "Item.h"

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
    int sizeX = 23;
    int sizeY = 8;

    if (selectedItem != oldSelectedItem || refresh)
    {
        system("cls");

        for (int y = 0; y < sizeY; y++)
        {
            if (y == 0 || y == 7)
            {
                // draw top line
                cout << " ";
                for (int x = 0; x < sizeX - 1; x++) cout << "-";
                cout << " ";

                // show tip
                if (y == 7) cout << endl << endl << "Tip: " << tips[random(0, 2)];

            }
            else if (y == 1 || y == 4)
            {
                // draw items top
                cout << "|   ";
                for (int x = 0; x < sizeX - 7; x++) cout << "-";
                cout << "   |";

            }
            else if (y == 3 || y == 6)
            {
                // draw bottom line
                cout << "|   ";
                for (int x = 0; x < sizeX - 7; x++) cout << "¯";
                cout << "   |";

            }
            else if (y == 2)
            {
                // draw play item sides
                if (selectedItem == Item::play) cout << "| >|";
                else cout << "|  |";
                for (int x = 0; x < sizeX - 4; x++)
                {
                    if (x > 2 && x <= 8) cout << " ";
                    if (x == 8) cout << "PLAY";
                    else if (x >= 13) cout << " ";


                }
                if (selectedItem == Item::play) cout << "|< |";
                else cout << "|  |";

            }
            else if (y == 5)
            {
                // draw quit item sides
                if (selectedItem == Item::quit) cout << "| >|";
                else cout << "|  |";
                for (int x = 0; x < sizeX - 4; x++)
                {
                    if (x > 2 && x <= 8) cout << " ";
                    if (x == 8) cout << "QUIT";
                    else if (x >= 13) cout << " ";


                }
                if (selectedItem == Item::quit) cout << "|< |";
                else cout << "|  |";

            }

            cout << endl;

        }

        oldSelectedItem = selectedItem;
        refresh = false;
    }

}