#include "KeyEvent.h"
#include "player.h"
#include "item.h"
#include "menu.h"
#include "option.h"
#include <vector>
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#define _WIN32_WINNT 0x0601
using namespace std;

char direction = 'n';
bool wait = false;

void KeyEvent::listen(int sizeX, int sizeY, Player& player, bool& refresh, bool& running, vector<Item> stars)
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
                Option::saveChange();

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
                    Option::saveChange();

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
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setFullscreen();
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
            for (Item item : stars) Item::updateItem(sizeX, sizeY, player, item.getPosition());

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


char XboxDirection = 'n';
bool XboxWait = false;

void KeyEvent::listenXbox(XINPUT_STATE controllerState, int sizeX, int sizeY, Player& player, bool& refresh, bool& running, vector<Item> stars)
{
    if (Menu::isOpen())
    {
        /* --- Menu KeyEvent --- */
        if (controllerState.Gamepad.sThumbLY < -20000)
        {
            if (Menu::getSelectedItem() == Menu::Item::play) Menu::setSelectedItem(Menu::Item::option);
            else if (Menu::getSelectedItem() == Menu::Item::option) Menu::setSelectedItem(Menu::Item::quit);
            else Menu::setSelectedItem(Menu::Item::play);
            Sleep(200);

        }
        else if (controllerState.Gamepad.sThumbLY > 20000)
        {
            if (Menu::getSelectedItem() == Menu::Item::play) Menu::setSelectedItem(Menu::Item::quit);
            else if (Menu::getSelectedItem() == Menu::Item::option) Menu::setSelectedItem(Menu::Item::play);
            else Menu::setSelectedItem(Menu::Item::option);
            Sleep(200);

        }
        else if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
        {
            switch (Menu::getSelectedItem())
            {
            case Menu::quit:
                running = false;

                break;
            case Menu::option:
                XboxWait = true;
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
        if (controllerState.Gamepad.sThumbLY < -20000)
        {
            if (Option::getSelectedItem() != (Option::appearanceSelection || Option::fullscreenSelection))
            {
                if (Option::getSelectedItem() == Option::appearance) Option::setSelectedItem(Option::fullscreen);
                else if (Option::getSelectedItem() == Option::fullscreen) Option::setSelectedItem(Option::back);
                else Option::setSelectedItem(Option::appearance);

            }
            Sleep(200);

        }
        else if (controllerState.Gamepad.sThumbLY > 20000)
        {
            if (Option::getSelectedItem() != (Option::appearanceSelection || Option::fullscreenSelection))
            {
                if (Option::getSelectedItem() == Option::appearance) Option::setSelectedItem(Option::back);
                else if (Option::getSelectedItem() == Option::back) Option::setSelectedItem(Option::fullscreen);
                else Option::setSelectedItem(Option::appearance);

            }
            Sleep(200);

        }
        else if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
        {
            switch (Option::getSelectedItem())
            {
            case Option::back:
                Option::setState(false);
                Menu::setState(true);
                refresh = true;

                break;
            case Option::appearance:
                if (!XboxWait) Option::setSelectedItem(Option::appearanceSelection); // XboxWait prevent appearanceSelection to be directly selected on option enter

                break;
            case Option::fullscreen:
                if (!XboxWait) Option::setSelectedItem(Option::fullscreenSelection);

                break;

            }
            Sleep(200);
            XboxWait = false;

        }
        else if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
        {
            if (Option::getSelectedItem() == Option::appearanceSelection)
            {
                Option::setSelectedItem(Option::appearance);
                XboxWait = true;

            }
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setSelectedItem(Option::fullscreen);
                XboxWait = true;

            }
            else
            {
                if (!XboxWait)
                {
                    Option::setState(false);
                    Menu::setState(true);
                    refresh = true;

                }

            }
            Sleep(200);
            XboxWait = false;

        }
        // make left and right change for the appearance selection
        else if (controllerState.Gamepad.sThumbLX > 20000)
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
                Sleep(200);
            }
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setFullscreen();
                refresh = true;
                Sleep(200);

            }

        }
        else if (controllerState.Gamepad.sThumbLX < -20000)
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
                Sleep(200);
            }
            else if (Option::getSelectedItem() == Option::fullscreenSelection)
            {
                Option::setFullscreen();
                refresh = true;
                Sleep(200);

            }

        }

    }
    else
    {
        /* --- Game KeyEvent --- */
        if (controllerState.Gamepad.sThumbLX > 20000 || controllerState.Gamepad.sThumbRX > 20000 || controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
        {
            if (player.getX() < sizeX - 1 && XboxDirection != 'r') player.moveRight();
            XboxDirection = 'r';

        }
        else if (controllerState.Gamepad.sThumbLX < -20000 || controllerState.Gamepad.sThumbRX < -20000 || controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
        {
            if (player.getX() > 0 && XboxDirection != 'l') player.moveLeft();
            XboxDirection = 'l';

        }
        else if (controllerState.Gamepad.sThumbLY < -20000 || controllerState.Gamepad.sThumbRY < -20000 || controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
        {
            if (player.getY() < sizeY - 2 && XboxDirection != 'd') player.moveDown();
            XboxDirection = 'd';

        }
        else if (controllerState.Gamepad.sThumbLY > 20000 || controllerState.Gamepad.sThumbRY > 20000 || controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
        {
            if (player.getY() > 1 && XboxDirection != 'u') player.moveUp();
            XboxDirection = 'u';

        }
        else if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)  // R
        {
            for (Item item : stars) Item::updateItem(sizeX, sizeY, player, item.getPosition());

            refresh = true;

        }
        else if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
        {
            Menu::setState(true);
            refresh = true;

        }
        else
        {
            XboxDirection = 'n';

        }

    }

}