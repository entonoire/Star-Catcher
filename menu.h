#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

class Menu
{

public:
	static enum Item { play = 0, quit = 1 };
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