#include "Item.h"
#include <random>
#include "player.h"


namespace util
{
    int random(int min, int max) { return min + (rand() % (max - min + 1)); }

}

int Item::pos[2] = { 0, 0 };

Item::Item(int sizeX, int sizeY, Player player) 
{
    updateItem(sizeX, sizeY, player);

}


void Item::updateItem(int sizeX, int sizeY, Player player)
{
    pos[0] = util::random(1, sizeX - 1);
    pos[1] = util::random(1, sizeY - 2);

    if (pos[0] == player.getX() && pos[1] == player.getY()) updateItem(sizeX, sizeX, player);

}


int* Item::getPosition() { return pos; }
int Item::getX() { return pos[0]; }
int Item::getY() { return pos[1]; }