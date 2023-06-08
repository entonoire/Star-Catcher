#include "Item.h"
#include <random>

int random(int min, int max) { return min + (rand() % (max - min + 1)); }
int Item::pos[2] = { 0, 0 };

Item::Item(int sizeX, int sizeY) 
{

    updateItem(sizeX, sizeY);

}


void Item::updateItem(int sizeX, int sizeY)
{
    pos[0] = random(1, sizeX - 1);
    pos[1] = random(1, sizeY - 2);

}


int* Item::getPosition() { return pos; }
int Item::getX() { return pos[0]; }
int Item::getY() { return pos[1]; }