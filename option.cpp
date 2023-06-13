#include "option.h"
#include <iostream>
#include <Windows.h>
#include "menu.h"
#include "keyEvent.h"
#include <vector>
using namespace std;
using namespace colorCode;


bool Option::open = false;
Option::Item Option::selectedItem = Item::appearance;
Option::Item Option::oldSelectedItem = Item::back;
vector<char> Option::appearances = { 'x', 'o', '@' };
bool Option::fullscreenState = false;


void Option::setFullscreen()
{
	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_F11;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_F11;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs)) cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError())) << endl;
	else Option::fullscreenState = !Option::fullscreenState;

}

bool Option::isFullscreen() { return Option::fullscreenState; }


bool Option::isOpen() { return Option::open; }

void Option::updateAppearance(vector<char> update) { Option::appearances = update; }

void Option::setState(bool newState) { 
	Option::selectedItem = Item::appearance;
	Option::oldSelectedItem = Item::back;

	Option::open = newState;

}


void Option::setSelectedItem(Item newItem) { Option::selectedItem = newItem; }

Option::Item Option::getSelectedItem() { return Option::selectedItem; }


void Option::display(bool& refresh)
{
	if (selectedItem != oldSelectedItem || refresh)
	{
		system("cls");
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		FlushConsoleInputBuffer(hConsole);

		cout << " -----------------------------------------------" << endl;
		
		// title
		cout << "|                    ";
		SetConsoleTextAttribute(hConsole, title);
		cout << underline << "OPTIONS";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "                    |" << endl;
		
		cout << "|                                               |" << endl;

		// appearance top
		cout << "|   ";
		if (selectedItem == appearance) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "----------------";
		SetConsoleTextAttribute(hConsole, baseColor);

		// appearance selection top
		cout << "    |     ";
		if (selectedItem == appearanceSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		cout << "-------------";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |" << endl;


		// appearance middle
		cout << "| ";
		if (selectedItem == appearance)
		{
			SetConsoleTextAttribute(hConsole, selectColor);
			cout << ">|   APPEARANCE   |<";

		}
		else
		{
			SetConsoleTextAttribute(hConsole, color);
			if (selectedItem == appearanceSelection) cout << ">|   APPEARANCE   |<"; else cout << " |   APPEARANCE   | ";

		}
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "  |   ";

		// appearance selection middle
		if (selectedItem == appearanceSelection)
		{
			SetConsoleTextAttribute(hConsole, selectColor);
			cout << "<";
			cout << "|    ";

			for (char c : appearances)
			{
				SetConsoleTextAttribute(hConsole, selectColor);

				if (c == appearances[appearances.size() / 2])
				{

					cout << " ";
					cout << bold << c;
					SetConsoleTextAttribute(hConsole, selectColor);
					cout << " ";

				}
				else
				{
					cout << c;

				}

			}

			cout << "    |";
			cout << ">";

		}
		else
		{
			SetConsoleTextAttribute(hConsole, inaccessible);
			cout << "<";
			cout << "|    ";


			for (char c : appearances)
			{
				SetConsoleTextAttribute(hConsole, inaccessible);

				if (c == appearances[appearances.size() / 2])
				{

					cout << " ";
					cout << bold << c;
					SetConsoleTextAttribute(hConsole, inaccessible);
					cout << " ";

				}
				else
				{
					cout << c;

				}

			}


			cout << "    |";
			cout << ">";

		}

		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "   |" << endl;

		// appearance bottom
		cout << "|   ";
		if (selectedItem == appearance) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |     ";

		// appearance selection bottom
		if (selectedItem == appearanceSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "     |" << endl;

		// fullscreen top
		cout << "|   ";
		if (selectedItem == Option::fullscreen) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "----------------";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |         ";

		// fullscreen selection top
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		cout << "-----";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "         |" << endl;

		// fullscreen middle
		cout << "| ";
		if (selectedItem == Option::fullscreen)
		{
			SetConsoleTextAttribute(hConsole, selectColor);
			cout << ">|   FULLSCREEN   |<";

		}
		else
		{
			SetConsoleTextAttribute(hConsole, color);
			if (selectedItem == Option::fullscreenSelection) cout << ">|   FULLSCREEN   |<"; else cout << " |   FULLSCREEN   | ";

		}

		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "  |       ";

		// fullscreen selection middle
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		if (Option::fullscreenState) cout << "<| Yes |>"; else cout << "<| No  |>";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "       |" << endl;


		// fullscreen bottom
		cout << "|   ";
		if (selectedItem == Option::fullscreen) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |         ";

		// fullscreen selection bottom
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		cout << "¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "         |" << endl;

		// back top
		cout << "|   ";
		if (selectedItem == back) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "----------------";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |                       |" << endl;

		// back middle
		cout << "| ";
		if (selectedItem == back)
		{
			SetConsoleTextAttribute(hConsole, selectColor);
			cout << ">|      BACK      |<";

		}
		else
		{
			SetConsoleTextAttribute(hConsole, color);
			cout << " |      BACK      | ";

		}
		
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "  |                       |" << endl;

		// back bottom
		cout << "|   ";
		if (selectedItem == back) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
		SetConsoleTextAttribute(hConsole, baseColor);
		cout << "    |                       |" << endl;

		cout << " -----------------------------------------------" << endl;

		oldSelectedItem = selectedItem;
		refresh = false;
	}

}
