#include "KeyEvent.h"
#include "Windows.h"
#include "player.h"
#include "item.h"
#include "menu.h"
#include "option.h"
#include <vector>

char KeyEvent::direction = 'n';
bool KeyEvent::wait = false;

void KeyEvent::listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running)
{
	if (Menu::isOpen())
	{
        /* --- Menu KeyEvent --- */
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
            case Menu::quit:
                running = false;

                break;
            case Menu::option:
                wait = true;
                Menu::setState(false);
                Option::setState(true);
                refresh = true;

                break;
            case Menu::play:
                Menu::setState(false);
                Option::setState(false);
                refresh = true;

                break;

            }

        }

	}
    else if (Option::isOpen())
    {
        /* --- Option KeyEvent --- */
        if ((GetKeyState(VK_DOWN) & 0x8000))
        {
            if (Option::getSelectedItem() != (Option::appearanceSelection || Option::fullscreenSelection))
            {
                if (Option::getSelectedItem() == Option::appearance) Option::setSelectedItem(Option::fullscreen);
                else if (Option::getSelectedItem() == Option::fullscreen) Option::setSelectedItem(Option::back);
                else Option::setSelectedItem(Option::appearance);

            }
            Sleep(100);

        }
        else if ((GetKeyState(VK_UP) & 0x8000))
        {
            if (Option::getSelectedItem() != (Option::appearanceSelection || Option::fullscreenSelection))
            {
                if (Option::getSelectedItem() == Option::appearance) Option::setSelectedItem(Option::back);
                else if (Option::getSelectedItem() == Option::back) Option::setSelectedItem(Option::fullscreen);
                else Option::setSelectedItem(Option::appearance);

            }
            Sleep(100);

        }
        else if (GetKeyState(VK_RETURN) & 0x8000)
        {
            switch (Option::getSelectedItem())
            {
            case Option::back:
                Option::setState(false);
                Menu::setState(true);
                refresh = true;

                break;
            case Option::appearance:
                if (!wait) Option::setSelectedItem(Option::appearanceSelection); // wait prevent appearanceSelection to be directly selected on option enter

                break;
            case Option::fullscreen:
                if (!wait) Option::setSelectedItem(Option::fullscreenSelection);

                break;

            }
            Sleep(100);
            wait = false;

        }
        else if (GetKeyState(VK_ESCAPE) & 0x8000)
        {
            if (Option::getSelectedItem() == Option::appearanceSelection)
            {
                Option::setSelectedItem(Option::appearance);
                wait = true;

            }
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setSelectedItem(Option::fullscreen);
                wait = true;

            }
            else
            {
                if (!wait)
                {
                    Option::setState(false);
                    Menu::setState(true);
                    refresh = true;

                }

            }
            Sleep(100);
            wait = false;

        }
        // make left and right change for the appearance selection
        else if (GetKeyState(VK_RIGHT) & 0x8000)
        {
            if (Option::getSelectedItem() == Option::appearanceSelection)
            {
                vector<char> v = Option::appearances;

                char first = v[0];

                for (int i = 0; i < v.size() - 1; i++) {
                    v[i] = v[i + 1];
                }

                v[v.size() - 1] = first;

                Option::updateAppearance(v);

                refresh = true;
                Sleep(100);
            }
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setFullscreen();
                refresh = true;
                Sleep(100);

            }

        }
        else if (GetKeyState(VK_LEFT) & 0x8000)
        {
            if (Option::getSelectedItem() == Option::appearanceSelection)
            {
                vector<char> v = Option::appearances;

                char last = v[v.size() - 1];

                for (int i = v.size() - 1; i > 0; i--)
                {
                    v[i] = v[i - 1];
                }

                v[0] = last;

                Option::updateAppearance(v);

                refresh = true;
                Sleep(100);
            }
            
        }

    }
    else
    {
        /* --- Game KeyEvent --- */
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
}
