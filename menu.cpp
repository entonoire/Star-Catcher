#include "menu.h"
#include <iostream>
using namespace std;

Menu::Item Menu::selectedItem = Menu::Item::play;
Menu::Item Menu::oldSelectedItem = Menu::Item::quit;
bool Menu::open = true;


bool Menu::isOpen() { return open; }

void Menu::setState(bool state) { 
    open = state;
    system("cls");

}


Menu::Item Menu::getSelectedItem() { return Menu::selectedItem; }

void Menu::setSelectedItem(Item newItem) { Menu::selectedItem = newItem; }


void Menu::display(int sizeX, int sizeY, bool& refresh) {
    if (selectedItem != oldSelectedItem || refresh)
    {
        system("cls");

        for (int y = 0; y < sizeY; y++)
        {
            if (y == 0 || y == 7)
            {
                // draw top end bottom lines
                cout << " ";
                for (int x = 0; x < sizeX - 1; x++) cout << "-";
                cout << " ";

            }
            else if (y == 1 || y == 4)
            {
                
                if (sizeX > 10)
                {
                    cout << "|   ";
                    for (int x = 0; x < sizeX - 7; x++) cout << "-";
                    cout << "   |";

                }
                else
                {
                    cout << "|  ";
                    for (int x = 0; x < sizeX - 7; x++) cout << "-";
                    cout << "  |";

                }

            }
            else if (y == 3 || y == 6)
            {
                if (sizeX > 10)
                {
                    cout << "|   ";
                    for (int x = 0; x < sizeX - 7; x++) cout << "¯";
                    cout << "   |";

                }
                else
                {
                    cout << "|  ";
                    for (int x = 0; x < sizeX - 7; x++) cout << "¯";
                    cout << "  |";

                }

            }
            else if (y == 2)
            {
                if (sizeX > 10)
                {
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
                else
                {
                    if (selectedItem == Item::play) cout << "|>|";
                    else cout << "| |";
                    for (int x = 0; x < sizeX - 4; x++)
                    {
                        if (x > 1 && x <= 3) cout << " ";
                        if (x == 4) cout << "PLAY";
                        else if (x >= 7) cout << " ";


                    }
                    if (selectedItem == Item::play) cout << "|<|";
                    else cout << "| |";

                }

            }
            else if (y == 5)
            {
                if (sizeX > 10)
                {
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
                else
                {
                    if (selectedItem == Item::quit) cout << "|>|";
                    else cout << "| |";
                    for (int x = 0; x < sizeX - 4; x++)
                    {
                        if (x > 1 && x <= 3) cout << " ";
                        if (x == 4) cout << "QUIT";
                        else if (x >= 7) cout << " ";


                    }
                    if (selectedItem == Item::quit) cout << "|>|";
                    else cout << "| |";

                }

            }
            else
            {
                cout << "|";
                for (int x = 0; x < sizeX; x++) cout << " ";
                cout << "|";

            }

            cout << endl;
        }

        oldSelectedItem = selectedItem;
        refresh = false;
    }

}