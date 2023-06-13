#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <Windows.h>
using namespace std;

namespace colorCode
{
	int const color = FOREGROUND_GREEN;
	string const underline = "\033[4m";
	string const bold = "\033[7m";
	int const title = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	int const selectColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	int const baseColor = 7;
	int const inaccessible = 8;

}

class Menu
{

public:
	static enum Item { play = 0, quit = 1, option = 2 };
	static bool isOpen();
	static void display(bool& refresh);
	static Item getSelectedItem();
	static void setSelectedItem(Item newItem);
	static void setState(bool state);

private:
	static bool open;
	static Item selectedItem;
	static Item oldSelectedItem;

};

#endif