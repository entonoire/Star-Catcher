#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "player.h"
#include "item.h"
#include <vector>
using namespace std;

class KeyEvent
{
private:
    static char direction;

public:
    static void listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running, vector<Item> stars);
    static bool wait;

};

#endif
