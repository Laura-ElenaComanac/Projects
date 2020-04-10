#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include <crtdbg.h>

int main()
{
	runAllTests();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
