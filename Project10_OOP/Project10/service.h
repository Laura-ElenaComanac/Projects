#pragma once
#include"repository.h"
#include"validare.h"

typedef struct
{
	RepositoryProdus* repositoryProdus;
}ServiceProdus;

typedef struct {
	int lungime;
	Produs* copyProduse;
}Copy;

ServiceProdus* creeazaServiceProdus(RepositoryProdus* repositoryProdus);

int addServiceProdus(ServiceProdus* serviceProdus, char ID[], char tip[], char producator[], char model[], char pret[], char cantitate[]);
/*Creeaza obiectul produs si il valideaza
Adauga produs
Daca produsul este deja in stoc, se actualizeaza cantitatea
Returneaza 0 daca produsul nu exista deja si 1 altfel*/

int updateServiceProdus(ServiceProdus* serviceProdus, char ID[], char newCantitate[]);
/*Actualizeaza cantitatea produsului dupa ID-ul specificat, cu newCantitate
Returneaza 0 daca produsul exista, 1 altfel*/

int removeServiceProdus(ServiceProdus* serviceProdus, char ID[]);
/*Sterge produsul dupa ID
Daca produsul exista, returneaza 0, 1 altfel*/

Produs* viewSortedProdus(ServiceProdus* serviceProdus);
/*Vizualizare produse din stoc, ordonat dupa pret, cantitate (crescator/descrescator)*/

Copy viewCriteriuProdus(ServiceProdus* serviceProdus, int pret);
/*Vizualizare lista de produse filtrate dupa un criteriu (producator, pret, cantitate)*/

void destroyServiceProdus(ServiceProdus* serviceProdus);
/*Distruge service*/
