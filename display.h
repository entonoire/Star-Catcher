#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"
#include "item.h"

class Display
{
public:
    static void update(Player& player, bool& refresh, int sizeX, int sizeY, Item item);

};

#endif
