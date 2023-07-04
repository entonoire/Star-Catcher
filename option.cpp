#include "option.h"
#include <iostream>
#include <Windows.h>
#include "menu.h"
#include "keyEvent.h"
#include <vector>
#include <fstream>
#include <string>
#include "display.h"
#include <ShlObj_core.h>
#include <direct.h>
using namespace std;
using namespace colorCode;
using namespace tool;


bool Option::open = false;
Option::Item Option::selectedItem = Item::appearance;
Option::Item Option::oldSelectedItem = Item::back;
vector<char> Option::appearances = { 'x', 'o', '@' };
bool Option::fullscreenState = false;
string path;

void Option::init()
{
	LPSTR appdata = new CHAR[MAX_PATH];
	ZeroMemory(appdata, MAX_PATH);

	if (SUCCEEDED(SHGetFolderPathA(GetConsoleWindow(), CSIDL_APPDATA, NULL, 0, appdata)))
	{
		
		path.append(appdata);
		path.append("\\.StarCatcher");

		int status = _mkdir(path.c_str());

		path.append("\\options.sc");
		ifstream file(path);

		if (file)
		{
			if (file.peek() == ifstream::traits_type::eof()) // if (file.isEmpty())
			{
				ofstream writer(path);

				for (char a : Option::appearances) writer << a << endl;
				writer << "%skip%" << endl << Option::fullscreenState;

				writer.close();
			}
			else
			{
				Option::appearances.clear();

				string line;
				bool running = true;

				while (getline(file, line))
				{
					if (running)
					{
						if (line == "%skip%") running = false;
						else Option::appearances.push_back(line[0]);

					}

				}

				getline(file, line);
				if (line == "1") Option::fullscreenState = true;
				else Option::fullscreenState = false;

			}


		}
		else
		{
			Display::debugMsg = L"couldn't acces option file (init)";
		}

		file.close();
	}
	delete[] appdata;

}


void Option::saveChange()
{
	ofstream file(path);

	if (file)
	{
		for (char a : Option::appearances) file << a << endl;
		file << "%skip%" << endl << Option::fullscreenState;


	}
	else
	{
		Display::debugMsg = L"couldn't acces option file (save)";
	}

}


void Option::setFullscreen(bool init)
{
	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_F11;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_F11;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs)) Display::debugMsg = (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
	else if (!init) Option::fullscreenState = !Option::fullscreenState;

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

		wcout << topLeftCorner << wstring(47, horizontalLine) << topRightCorner << endl;
		
		// title
		wcout << verticalLine << "                    ";
		SetConsoleTextAttribute(hConsole, title);
		wcout << underline << "OPTIONS";
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "                    " << verticalLine << endl;
		
		// separation line
		wcout << L"\u251C" << wstring(23, horizontalLine) << L"\u252C" << wstring(23, horizontalLine) << L"\u2524" << endl;
		wcout << verticalLine << "                       " << verticalLine << "                       " << verticalLine << endl;

		// appearance top
		wcout << verticalLine << "  ";
		if (selectedItem == appearance) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << topLeftCorner << wstring(16, horizontalLine) << topRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);

		// appearance selection top
		wcout << "   " << verticalLine << "    ";
		if (selectedItem == appearanceSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		wcout << topLeftCorner << wstring(13, horizontalLine) << topRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "    " << verticalLine << endl;

		// appearance middle
		wcout << verticalLine << " ";
		if (selectedItem == appearance) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << " " << verticalLine << "   APPEARANCE   " << verticalLine << " ";
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "  " << verticalLine << "   ";

		// appearance selection middle
		if (selectedItem == appearanceSelection)
		{
			SetConsoleTextAttribute(hConsole, selectColor);
			wcout << "<";
			wcout << verticalLine << "    ";

			for (char c : appearances)
			{
				SetConsoleTextAttribute(hConsole, selectColor);

				if (c == appearances[appearances.size() / 2])
				{

					wcout << " ";
					wcout << bold << c;
					SetConsoleTextAttribute(hConsole, selectColor);
					wcout << " ";

				}
				else
				{
					wcout << c;

				}

			}

			wcout << "    " << verticalLine;
			wcout << ">";

		}
		else
		{
			SetConsoleTextAttribute(hConsole, inaccessible);
			wcout << "<";
			wcout << verticalLine << "    ";


			for (char c : appearances)
			{
				SetConsoleTextAttribute(hConsole, inaccessible);

				if (c == appearances[appearances.size() / 2])
				{

					wcout << " ";
					wcout << bold << c;
					SetConsoleTextAttribute(hConsole, inaccessible);
					wcout << " ";

				}
				else
				{
					wcout << c;

				}

			}


			wcout << "    " << verticalLine;
			wcout << ">";

		}

		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << endl;

		// appearance bottom
		wcout << verticalLine << "  ";
		if (selectedItem == appearance) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << "    ";

		// appearance selection bottom
		if (selectedItem == appearanceSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		wcout << bottomLeftCorner << wstring(13, horizontalLine) << bottomRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "    " << verticalLine << endl;

		// fullscreen top
		wcout << verticalLine << "  ";
		if (selectedItem == Option::fullscreen) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << topLeftCorner << wstring(16, horizontalLine) << topRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << "        ";

		// fullscreen selection top
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		wcout << topLeftCorner << wstring(5, horizontalLine) << topRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "        " << verticalLine << endl;

		// fullscreen middle
		wcout << verticalLine << " ";
		if (selectedItem == Option::fullscreen) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << " " << verticalLine << "   FULLSCREEN   " << verticalLine << " ";

		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "  " << verticalLine << "       ";

		// fullscreen selection middle
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		if (Option::fullscreenState) wcout << "<" << verticalLine << " Yes " << verticalLine << ">"; else wcout << "<" << verticalLine << " No  " << verticalLine << ">";
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "       " << verticalLine << endl;


		// fullscreen bottom
		wcout << verticalLine << "  ";
		if (selectedItem == Option::fullscreen) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << "        ";

		// fullscreen selection bottom
		if (selectedItem == Option::fullscreenSelection) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, inaccessible);
		wcout << bottomLeftCorner << wstring(5, horizontalLine) << bottomRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "        " << verticalLine << endl;

		// back top
		wcout << verticalLine << "  ";
		if (selectedItem == back) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << topLeftCorner << wstring(16, horizontalLine) << topRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << "                       " << verticalLine << endl;

		// back middle
		wcout << verticalLine << " ";
		if (selectedItem == back) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << " " << verticalLine << "      BACK      " << verticalLine << "   ";
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << verticalLine << "  " << "                     " << verticalLine << endl;

		// back bottom
		wcout << verticalLine << "  ";
		if (selectedItem == back) SetConsoleTextAttribute(hConsole, selectColor); else SetConsoleTextAttribute(hConsole, color);
		wcout << bottomLeftCorner << wstring(16, horizontalLine) << bottomRightCorner;
		SetConsoleTextAttribute(hConsole, baseColor);
		wcout << "   " << verticalLine << "                       " << verticalLine << endl;

		wcout << bottomLeftCorner << wstring(23, horizontalLine) << L"\u2534" << wstring(23, horizontalLine) << bottomRightCorner << endl;

		if (Display::debugMsg != L"") wcout << "Debug: " << Display::debugMsg;

		oldSelectedItem = selectedItem;
		refresh = false;
	}

}
