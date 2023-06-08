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
using namespace std;

int sizeX = 10, sizeY = 5;

void formatConsole()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);


    /* --- pressing F11 to fullscreen --- */
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


int main()
{
    Item item(sizeX - 1, sizeY - 2);
    bool refresh = true;
    Player player(1, 1);

    formatConsole();

    while (true)
    {
        if (player.getScore() % 10 == 0 && player.getScore() != 0)
        {
            sizeX += 5;
            sizeY += 2;
            player.increaseScore();

        }

        KeyEvent::listen(sizeX, sizeY, player, refresh);
        Display::update(player, refresh, sizeX, sizeY, item);


    }
    
    return 0;
}
