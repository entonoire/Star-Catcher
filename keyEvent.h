#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "player.h"

class KeyEvent
{
private:
    static char direction;

public:
    static void listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running);

};

#endif
