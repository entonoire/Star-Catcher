#ifndef OPTION_H
#define OPTION_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Option
{

public:
	static enum Item { appearance = 0, appearanceSelection = 1, back = 2, fullscreen = 3, fullscreenSelection = 4 };
	static void display(bool& refresh);
	static bool isOpen();
	static void setState(bool newState);
	static void setSelectedItem(Item newItem);
	static Item getSelectedItem();
	static void setFullscreen();
	static vector<char> appearances;
	static void updateAppearance(vector<char> update);
	static bool isFullscreen();

private:
	static bool open;
	static Item selectedItem;
	static Item oldSelectedItem;
	static bool fullscreenState;

};

#endif;