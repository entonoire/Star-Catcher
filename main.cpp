﻿#include <iostream>
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

    SetConsoleTitleW(L"Star Catch - Beta v0.1");

    /* --- pressing F11 to fullscreen --- */
    if (false)
    {
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_F11;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_F11;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError())) << endl;
        }

    }

}

int main()
{
    Player player(1, 1);
    Item item(sizeX - 1, sizeY - 2, player);

    formatConsole();

    bool refresh = true;
    bool running = true;

    while (running)
    {
        KeyEvent::listen(sizeX, sizeY, player, refresh, running);

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

            }


            Display::update(player, refresh, sizeX, sizeY, item);

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
