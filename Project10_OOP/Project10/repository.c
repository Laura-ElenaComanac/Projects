#include"repository.h"
#include"domain.h"
#include<stdio.h>
#include<string.h>

RepositoryProdus* creeazaRepositoryProdus()
{
	RepositoryProdus* repositoryProdus=(RepositoryProdus*)malloc(sizeof(RepositoryProdus));

	repositoryProdus->capacitate = 2;
	repositoryProdus->lungime = 0;
	repositoryProdus->produse = (Produs*)malloc(sizeof(Produs) * repositoryProdus->capacitate);

	return repositoryProdus;
}

Produs* getProdus(RepositoryProdus* repositoryProdus, int index)
{
	if (index<0 || index > repositoryProdus->lungime)
		return NULL;
	return &repositoryProdus->produse[index];
}

int findProdus(RepositoryProdus* repositoryProdus, int ID)
{
	int i;
	for (i = 0; i < repositoryProdus->lungime; i++)
		if (getID(&repositoryProdus->produse[i]) == ID)
			return i;
	return -1;
}

int updateProdus(RepositoryProdus* repositoryProdus, int ID, int newCantitate)
{
	if (findProdus(repositoryProdus, ID) != -1)
	{
		int index = findProdus(repositoryProdus, ID);
		Produs* produs = getProdus(repositoryProdus, index);
		setCantitate(produs, newCantitate);
		return 0;
	}
	else
		return 1;
}

int addProdus(RepositoryProdus* repositoryProdus, Produs produs)
{
	if (findProdus(repositoryProdus, getID(&produs)) == -1)
	{
		if (repositoryProdus->capacitate == repositoryProdus->lungime)
			maresteRepository(repositoryProdus);
		repositoryProdus->produse[repositoryProdus->lungime] = produs;
		repositoryProdus->lungime++;
		return 0;
	}
	else
	{
		updateProdus(repositoryProdus, getID(&produs), getCantitate(&produs));
		return 1;
	}
}

int removeProdus(RepositoryProdus* repositoryProdus, int ID)
{
	int index = findProdus(repositoryProdus, ID);
	if (index != -1)
	{
		for (int i = index; i < repositoryProdus->lungime; i++)
			repositoryProdus->produse[i] = repositoryProdus->produse[i + 1];
		repositoryProdus->lungime--;
		if (repositoryProdus->capacitate == repositoryProdus->lungime*2)
			scadeRepository(repositoryProdus);
		return 0;
	}
	return 1;
}

int lungimeRepository(RepositoryProdus* repositoryProdus)
{
	return repositoryProdus->lungime;
}

void maresteRepository(RepositoryProdus* repositoryProdus)
{
	repositoryProdus->capacitate *= 2;
	Produs* largerRepositoryProdus = (Produs*)malloc(sizeof(Produs) * repositoryProdus->capacitate);
	for (int i = 0; i < repositoryProdus->lungime; i++)
		largerRepositoryProdus[i] = repositoryProdus->produse[i];

	free(repositoryProdus->produse);
	repositoryProdus->produse = largerRepositoryProdus;
}

void scadeRepository(RepositoryProdus* repositoryProdus)
{
	repositoryProdus->capacitate /= 2;
	Produs* largerRepositoryProdus = (Produs*)malloc(sizeof(Produs) * repositoryProdus->capacitate);
	for (int i = 0; i < repositoryProdus->lungime; i++)
		largerRepositoryProdus[i] = repositoryProdus->produse[i];

	free(repositoryProdus->produse);
	repositoryProdus->produse = largerRepositoryProdus;
}

void destroyRepository(RepositoryProdus* repositoryProdus)
{
	free(repositoryProdus->produse);
	free(repositoryProdus);
}
