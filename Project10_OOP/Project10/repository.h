#pragma once
#include"domain.h"
#include<stdlib.h>

typedef struct {
	Produs* produse;
	int lungime, capacitate;
}RepositoryProdus;

RepositoryProdus* creeazaRepositoryProdus();

Produs* getProdus(RepositoryProdus* repositoryProdus, int index);
/*Returneaza produsul cu index dat*/

int findProdus(RepositoryProdus* repositoryProdus, int ID);
/*Cauta un produs dupa ID
Returneaza index-ul daca l-a gasit si -1 altfel*/

int updateProdus(RepositoryProdus* repositoryProdus, int ID, int newCantitate);
/*Actualizeaza cantitatea produsului dupa ID-ul specificat, cu newCantitate
Returneaza 0 daca produsul exista, 1 altfel*/

int addProdus(RepositoryProdus* repositoryProdus, Produs produs);
/*Adauga produs
Daca produsul este deja in stoc, se actualizeaza cantitatea
Returneaza 0 daca produsul nu exista deja si 1 altfel*/

int removeProdus(RepositoryProdus* repositoryProdus, int ID);
/*Sterge produsul dupa ID
Daca produsul exista, returneaza 0, 1 altfel*/

int lungimeRepository(RepositoryProdus* repositoryProdus);
/*Returneaza lungime repository*/

void maresteRepository(RepositoryProdus* repositoryProdus);
/*Mareste repository*/

void scadeRepository(RepositoryProdus* repositoryProdus);
/*Scade repository*/

void destroyRepository(RepositoryProdus* repositoryProdus);
/*Distruge repository*/

