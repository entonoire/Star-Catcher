#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"
#include "item.h"
#include <vector>
#include <string>
using namespace std;

class Display
{
public:
    static string debugMsg;
    static void update(Player& player, bool& refresh, int sizeX, int sizeY, vector<Item>& stars);

};

#endif
