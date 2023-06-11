#ifndef OPTION_H
#define OPTION_H

class Option
{

public:
	static void display(bool& refresh);
	static bool isOpen();
	static void setState(bool newState);
	static bool open;

};

#endif;