#include <iostream>
#include <string>
#include <conio.h>
#include "Windows.h"
#include <stdlib.h> 
#include <time.h>
#include <dos.h>
#include "player.h"
#include "display.h"
#include "keyEvent.h"
#include "Item.h"
#include <cwchar>
#include <cmath>
#include "menu.h"
#include <cstdio>
#include "option.h"
#include <vector>
#include <Xinput.h>
#define _WIN32_WINNT 0x0601
using namespace std;
#pragma execution_character_set( "utf-8" )

int sizeX = 10, sizeY = 5;


void formatConsole()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(1252); // ANSI Latin 1; Western European (Windows)

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    SetConsoleTitleW(L"Star Catch - Beta v0.3");

}

int main()
{
    Player player(1, 1);
    vector<Item> stars = { Item(sizeX - 1, sizeY - 2, player) };

    formatConsole();
    XINPUT_STATE controllerState;

    /* --- pressing F11 to fullscreen --- */
    if (Option::isFullscreen()) Option::setFullscreen();

    bool refresh = true;
    bool running = true;

    

    while (running)
    {

        DWORD result = XInputGetState(0, &controllerState);
        if (result == ERROR_SUCCESS) KeyEvent::listenXbox(controllerState, sizeX, sizeY, player, refresh, running, stars);
        KeyEvent::listen(sizeX, sizeY, player, refresh, running, stars);



        if (Menu::isOpen())
        {
            Menu::display(refresh);

        }
        else if (Option::isOpen())
        {
            Option::display(refresh);

        }
        else
        {
            if (player.getScore() % 10 == 0 && player.getScore() != 0)
            {
                sizeX += 5;
                sizeY += 2;
                player.increaseScore();
                stars.push_back(Item(sizeX - 1, sizeY - 2, player));

            }


            Display::update(player, refresh, sizeX, sizeY, stars);

        }

    }

    system("cls");        
    system("color 2");
    cout << "   _____  ____   ____  _____  ______     ________ " << endl;
    cout << "  / ____|/ __ \\ / __ \\|  __ \\|  _ \\ \\   / |  ____|" << endl;
    cout << " | |  __| |  | | |  | | |  | | |_) \\ \\_/ /| |__   " << endl;
    cout << " | | |_ | |  | | |  | | |  | |  _ < \\   / |  __|  " << endl;
    cout << " | |__| | |__| | |__| | |__| | |_) | | |  | |____ " << endl;
    cout << "  \\_____|\\____/ \\____/|_____/|____/  |_|  |______|" << endl;
    cout << "                                                  " << endl;
    Sleep(1000);
    

    return 0;
}
