#include "display.h"
#include "player.h"
#include "Item.h"
#include <iostream>
#include <Windows.h>
#include "option.h"
#include <vector>
using namespace std;
using namespace tool;

namespace tool
{
    wchar_t topLeftCorner = L'\u256D';
    wchar_t topRightCorner = L'\u256E';
    wchar_t horizontalLine = L'\u2500';
    wchar_t verticalLine = L'\u2502';
    wchar_t bottomLeftCorner = L'\u2570';
    wchar_t bottomRightCorner = L'\u256F';

    //wchar_t topLeftCorner = L'\u250C';
    //wchar_t topRightCorner = L'\u2510';
    //wchar_t bottomLeftCorner = L'\u2514';
    //wchar_t bottomRightCorner = L'\u2518';
}


wstring Display::debugMsg = L"";

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
            if (y == 0)
            {
                // box top
                wcout << topLeftCorner;
                for (int x = 0; x < sizeX; x++) wcout << horizontalLine;
                wcout << topRightCorner << endl;

            }
            else if (y == sizeY - 1)
            {
                // box bottom
                wcout << bottomLeftCorner;
                for (int x = 0; x < sizeX; x++) wcout << horizontalLine;
                wcout << bottomRightCorner << endl;

            }
            else
            {
                wcout << verticalLine;
                for (int x = 0; x < sizeX; x++)
                {

                    bool alreadyDisplayed = false; // used to check if you need to put blanck or fill it with something

                    // display player
                    if (player.getX() == x && player.getY() == y)
                    {
                        wcout << Option::appearances[(Option::appearances.size() - 1) / 2];
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
                            wcout << L"\u2605";
                            SetConsoleTextAttribute(hConsole, 7);

                            alreadyDisplayed = true;

                            previousCoord[0] = x;
                            previousCoord[1] = y;

                        }

                    }


                    // empty display
                    if (!alreadyDisplayed) wcout << " ";

                }

                wcout << verticalLine;
                if (y == sizeY / 2) wcout << "  " << player.getScore() << " points";
                wcout << endl;

            }

        }
        if (Display::debugMsg != L"") wcout << "Debug: " << Display::debugMsg;

        player.setOldPosition(player.getX(), player.getY());
        refresh = false;
    }

}
