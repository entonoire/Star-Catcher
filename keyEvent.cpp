#include "KeyEvent.h"
#include "Windows.h"
#include "player.h"
#include "item.h"

char KeyEvent::direction = 'n';

void KeyEvent::listen(int sizeX, int sizeY, Player& player, bool& refresh)
{
    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        if (player.getX() < sizeX - 1 && direction != 'r') player.moveRight();
        direction = 'r';

    }
    else if (GetKeyState(VK_LEFT) & 0x8000)
    {
        if (player.getX() > 0 && direction != 'l') player.moveLeft();
        direction = 'l';

    }
    else if (GetKeyState(VK_DOWN) & 0x8000)
    {
        if (player.getY() < sizeY - 2 && direction != 'd') player.moveDown();
        direction = 'd';

    }
    else if (GetKeyState(VK_UP) & 0x8000)
    {
        if (player.getY() > 1 && direction != 'u') player.moveUp();
        direction = 'u';

    }
    else if (GetKeyState(0x52) & 0x8000)  // R
    {
        Item::updateItem(sizeX, sizeY);
        refresh = true;

    }
    else
    {
        direction = 'n';

    }

}
