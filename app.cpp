#include <dlfcn.h>
#include <iostream>
#include "dynlib.hpp"
#include <ctime>
#include <unistd.h>

using namespace std;


int main()
{
  while(1)
	{
	  print();
	  cout << "Going to sleep..." << endl;
	  sleep(3);
	  cout << "Waked up ..." << endl;
	}

  return 0;
}
