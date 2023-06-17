#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"
#include "item.h"
#include <vector>
using namespace std;

class Display
{
public:
    static void update(Player& player, bool& refresh, int sizeX, int sizeY, vector<Item>& stars);

};

#endif
