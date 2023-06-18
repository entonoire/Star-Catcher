#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "player.h"
#include "item.h"
#include <vector>
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#define _WIN32_WINNT 0x0601
using namespace std;

class KeyEvent
{

public:
    static void listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running, vector<Item> stars);
    static void listenXbox(XINPUT_STATE controllerState, int sizeX, int sizeY, Player& player, bool& refresh, bool& running, vector<Item> stars);

};

#endif
