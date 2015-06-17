#include <iostream>
#include "Life.h"
#include <fstream>

using namespace std;

int main()
{
	Life mylife;
	mylife.fileVsRand();
	mylife.selectMode();
	mylife.runTime();
	mylife.calculateFuture();

	return 0;
}
