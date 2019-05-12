#include <stdlib.h>
#include <iostream>
#include "dynlib.hpp"
#include <unistd.h>

using namespace std;


extern "C" void print()
{
	static unsigned int counter = 0;
	++counter;

	cout << counter << ":PID " << getpid() << ": In print() " << endl;
}
