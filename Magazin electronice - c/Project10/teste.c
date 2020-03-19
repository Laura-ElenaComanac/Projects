#include<assert.h>
#include<string.h>
#include<stdio.h>
#include"teste.h"
#include"domain.h"
#include"repository.h"
#include"service.h"

void testProdus()
{
	Produs produs = creeazaProdus(222, "laptop", "Apple", "Macbook Pro", 2000, 1);

	assert(getID(&produs) == 222);
	assert(strcmp(getTip(&produs),"laptop")==0);
	assert(strcmp(getProducator(&produs), "Apple") == 0);
	assert(strcmp(getModel(&produs), "Macbook Pro") == 0);
	assert(getPret(&produs) == 2000);
	assert(getCantitate(&produs) == 1);

	setID(&produs, 10);
	setTip(&produs, "mouse");
	setProducator(&produs, "Asus");
	setModel(&produs, "XRD");
	setPret(&produs, 22);
	setCantitate(&produs, 3);

	assert(getID(&produs) == 10);
	assert(strcmp(getTip(&produs), "mouse") == 0);
	assert(strcmp(getProducator(&produs), "Asus") == 0);
	assert(strcmp(getModel(&produs), "XRD") == 0);
	assert(getPret(&produs) == 22);
	assert(getCantitate(&produs) == 3);
}

void testRepository()
{
	RepositoryProdus* repositoryProdus = creeazaRepositoryProdus();
	Produs produs = creeazaProdus(222, "laptop", "Apple", "Macbook Pro", 2000, 1);
	Produs altProdus = creeazaProdus(222, "laptop", "Apple", "Macbook Pro", 2000, 5);
	Produs incaUnProdus = creeazaProdus(12, "mouse", "Asus", "III", 20, 2);
	
	assert(repositoryProdus->lungime == 0);

	assert(addProdus(repositoryProdus, produs) == 0);
	addProdus(repositoryProdus, produs);
	assert(addProdus(repositoryProdus, produs) == 1);
	assert(repositoryProdus->lungime == 1);

	assert(getID(&repositoryProdus->produse[0]) == 222);
	assert(strcmp(getTip(&repositoryProdus->produse[0]), "laptop") == 0);
	assert(strcmp(getProducator(&repositoryProdus->produse[0]), "Apple") == 0);
	assert(strcmp(getModel(&repositoryProdus->produse[0]), "Macbook Pro") == 0);
	assert(getPret(&repositoryProdus->produse[0]) == 2000);
	assert(getCantitate(&repositoryProdus->produse[0]) == 1);

	assert(findProdus(repositoryProdus, 222) == 0);
	assert(findProdus(repositoryProdus, 111) == -1);

	addProdus(repositoryProdus, altProdus);
	assert(repositoryProdus->lungime == 1);
	assert(getCantitate(&repositoryProdus->produse[0]) == 5);

	addProdus(repositoryProdus, incaUnProdus);
	assert(repositoryProdus->lungime == 2);

	assert(removeProdus(repositoryProdus, 222) == 0);
	assert(removeProdus(repositoryProdus, 999) == 1);

	assert(repositoryProdus->lungime == 1);

	assert(updateProdus(repositoryProdus, 12, 7) == 0);
	assert(updateProdus(repositoryProdus, 999, 7) == 1);

	assert(getCantitate(&repositoryProdus->produse[0]) == 7);

	destroyRepository(repositoryProdus);

}

void testService()
{
	RepositoryProdus* repositoryProdus = creeazaRepositoryProdus();
	ServiceProdus* serviceProdus = creeazaServiceProdus(repositoryProdus);

	assert(addServiceProdus(serviceProdus, "22", "laptop", "Apple", "MacbookPro", "2000", "1") == 0);
	assert(addServiceProdus(serviceProdus, "22", "laptop", "Apple", "MacbookPro", "2000", "1") == 1);

	addServiceProdus(serviceProdus, "22", "mouse", "Asus", "III", "20", "2");
	assert(getCantitate(&serviceProdus->repositoryProdus->produse[0]) == 2);

	assert(removeServiceProdus(serviceProdus, "22") == 0);
	assert(removeServiceProdus(serviceProdus, "999") == 1);

	addServiceProdus(serviceProdus, "55", "laptop", "Apple", "MacbookPro", "2000", "5");

	assert(updateServiceProdus(serviceProdus, "55", "7") == 0);
	assert(updateServiceProdus(serviceProdus, "999", "8") == 1);

	assert(getCantitate(&serviceProdus->repositoryProdus->produse[0]) == 7);

	destroyServiceProdus(serviceProdus);

}

void testAll()
{
	testProdus();
	testRepository();
	testService();
	printf("It's all working! ;)");
}