#include "display.h"
#include "player.h"
#include "Item.h"
#include <iostream>
#include <Windows.h>
#include "option.h"
#include <vector>
using namespace std;

string Display::debugMsg = "";

void Display::update(Player& player, bool& refresh, int sizeX, int sizeY, vector<Item>& stars)
{

    if ((player.getOldX() != player.getX() || player.getOldY() != player.getY()) || refresh)
    {
        system("cls");
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        FlushConsoleInputBuffer(hConsole);

        for (Item& item : stars)
        {
            if (player.getX() == item.getX() && player.getY() == item.getY())
            {
                Item::updateItem(sizeX, sizeY, player, item.getPosition());
                player.increaseScore();

            }

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

                    bool alreadyDisplayed = false; // used to check if you need to put blanck or fill it with something

                    // display player
                    if (player.getX() == x && player.getY() == y)
                    {
                        cout << Option::appearances[(Option::appearances.size() - 1) / 2];
                        alreadyDisplayed = true;

                    }
                    

                    // display star
                    int previousCoord[2]{};

                    for (Item item : stars)
                    {
                        if (item.getX() == x && item.getY() == y)
                        {
                            
                            if (previousCoord[0] == x && previousCoord[1] == y)
                            {
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(x + 1), static_cast<short>(y) }); // overwrite old star that have the exact same pos
                                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

                            }
                            else
                            {
                                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
                            }
                            cout << "*";
                            SetConsoleTextAttribute(hConsole, 7);

                            alreadyDisplayed = true;

                            previousCoord[0] = x;
                            previousCoord[1] = y;

                        }

                    }


                    // empty display
                    if (!alreadyDisplayed) cout << " ";

                }

                cout << "|";
                if (y == sizeY / 2) cout << "  " << player.getScore() << " points";
                cout << endl;

            }

        }
        if (Display::debugMsg != "") cout << "Debug: " << Display::debugMsg;

        player.setOldPosition(player.getX(), player.getY());
        refresh = false;
    }

}
