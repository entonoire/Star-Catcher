#include "KeyEvent.h"
#include "Windows.h"
#include "player.h"
#include "item.h"
#include "menu.h"

char KeyEvent::direction = 'n';

void KeyEvent::listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running)
{
	if (!Menu::isOpen())
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
            Item::updateItem(sizeX, sizeY, player);
            refresh = true;

        }
        else if (GetKeyState(VK_ESCAPE) & 0x8000)
        {
            Menu::setState(true);
            refresh = true;

        }
        else
        {
            direction = 'n';

        }

	}
    else
    {
        if ((GetKeyState(VK_DOWN) & 0x8000))
        {
            if (Menu::getSelectedItem() == Menu::Item::play) Menu::setSelectedItem(Menu::Item::option);
            else if (Menu::getSelectedItem() == Menu::Item::option) Menu::setSelectedItem(Menu::Item::quit);
            else Menu::setSelectedItem(Menu::Item::play);
            Sleep(100);

        }
        else if ((GetKeyState(VK_UP) & 0x8000))
        {
            if (Menu::getSelectedItem() == Menu::Item::play) Menu::setSelectedItem(Menu::Item::quit);
            else if (Menu::getSelectedItem() == Menu::Item::option) Menu::setSelectedItem(Menu::Item::play);
            else Menu::setSelectedItem(Menu::Item::option);
            Sleep(100);

        }
        else if (GetKeyState(VK_RETURN) & 0x8000)
        {
            switch (Menu::getSelectedItem())
            {
            case Menu::quit :
                running = false;
                break;

            case Menu::play:
                Menu::setState(false);
                refresh = true;

                break;

            }

        }

    }
}
