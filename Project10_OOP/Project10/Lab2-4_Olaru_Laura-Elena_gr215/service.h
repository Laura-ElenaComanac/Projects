#pragma once
#include"repository.h"

typedef struct
{
	RepositoryProdus* repositoryProdus;
}ServiceProdus;

ServiceProdus creeazaServiceProdus(RepositoryProdus* repositoryProdus);

int addServiceProdus(ServiceProdus* serviceProdus, int ID, char tip[], char producator[], char model[], int pret, int cantitate);
/*Creeaza obiectul produs si il valideaza
Adauga produs
Daca produsul este deja in stoc, se actualizeaza cantitatea
Returneaza 0 daca produsul nu exista deja si 1 altfel*/

int updateServiceProdus(ServiceProdus* serviceProdus, int ID, int newCantitate);
/*Actualizeaza cantitatea produsului dupa ID-ul specificat, cu newCantitate
Returneaza 0 daca produsul exista, 1 altfel*/

int removeServiceProdus(ServiceProdus* serviceProdus, int ID);
/*Sterge produsul dupa ID
Daca produsul exista, returneaza 0, 1 altfel*/

void viewSotrtedProdus(ServiceProdus* serviceProdus, Produs produs);
/*Vizualizare produse din stoc, ordonat dupa pret, cantitate (crescator/descrescator)*/

void viewCriteriuProdus(ServiceProdus* serviceProdus, Produs produs);
/*Vizualizare lista de produse filtrate dupa un criteriu (producator, pret, cantitate)*/

Produs* getServiceProdus(RepositoryProdus* repositoryProdus, int index);
/*Returneaza produsul cu index dat*/
