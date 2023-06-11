#include "display.h"
#include "player.h"
#include "Item.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void Display::update(Player& player, bool& refresh, int sizeX, int sizeY, Item item)
{

    if ((player.getOldX() != player.getX() || player.getOldY() != player.getY()) || refresh)
    {
        system("cls");
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        FlushConsoleInputBuffer(hConsole);

        if (player.getX() == item.getX() && player.getY() == item.getY())
        {
            Item::updateItem(sizeX, sizeY, player);
            player.increaseScore();

        }

        for (int y = 0; y < sizeY; y++)
        {
            if (y == 0 || y == sizeY - 1)
            {
                cout << " ";
                for (int x = 0; x < sizeX; x++) cout << "-";
                cout << " " << endl;

            }
            else
            {
                cout << "|";
                for (int x = 0; x < sizeX; x++)
                {


                    if (player.getX() == x && player.getY() == y) cout << "o";
                    else if (item.getX() == x && item.getY() == y)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
                        cout << "*";
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    else cout << " ";

                }

                cout << "|";
                if (y == sizeY / 2) cout << "  " << player.getScore() << " points";
                cout << endl;

            }

        }


        player.setOldPosition(player.getX(), player.getY());
        refresh = false;
    }

}
