#include "utils.h"
#include <iostream>
#include <string>

using namespace std;

void sendMessage(string message, string name)
{
	cout << name << " > " << message << endl;
}

int multiply(int a, int b)
{
	return a * b;
}


inline bool isInteger(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}