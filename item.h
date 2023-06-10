#ifndef ITEM_H
#define ITEM_H

#include "player.h"

namespace util
{
    int random(int min, int max);

}

class Item
{
private:
    static int pos[2];

public:
    Item(int posX, int posY, Player player);

    static void updateItem(int sizeX, int sizeY, Player player);
    int* getPosition();
    int getX();
    int getY();

};

#endif
