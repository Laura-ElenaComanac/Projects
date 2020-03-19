#include <stdio.h>
//#include <crtdbg.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "teste.h"
#include "ui.h"

//#define _CRTDBG_MAP_ALLOC

int main()
{
	testAll();
	
	RepositoryProdus* repositoryProdus = creeazaRepositoryProdus();
	ServiceProdus* serviceProdus = creeazaServiceProdus(repositoryProdus);
	UI* ui = creeazaUI(serviceProdus);

	run(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}