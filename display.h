#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"
#include "item.h"
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

namespace tool
{
    extern wchar_t topLeftCorner;
    extern wchar_t topRightCorner;
    extern wchar_t horizontalLine;
    extern wchar_t verticalLine;
    extern wchar_t bottomLeftCorner;
    extern wchar_t bottomRightCorner;

}

class Display
{
public:
    static wstring debugMsg;
    static void update(Player& player, bool& refresh, int sizeX, int sizeY, vector<Item>& stars);

};

#endif
