#include <stdio.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "teste.h"
#include "ui.h"

int main()
{
	testAll();
	
	RepositoryProdus repositoryProdus = creeazaRepositoryProdus();
	ServiceProdus serviceProdus = creeazaServiceProdus(&repositoryProdus);
	UI ui = creeazaUI(&serviceProdus);

	run(&ui);

	return 0;
}