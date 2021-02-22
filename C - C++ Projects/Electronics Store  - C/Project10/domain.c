#include"domain.h"
#include<stdio.h>
#include<string.h>

Produs creeazaProdus(int ID, char tip[], char producator[], char model[], int pret, int cantitate)
{
	Produs produs;

	produs.ID=ID;

	strcpy(produs.tip, tip);
	strcpy(produs.producator, producator);
	strcpy(produs.model, model);

	produs.pret = pret;
	produs.cantitate = cantitate;

	return produs;
}

int getID(Produs* produs)
{
	return produs->ID;
}

char* getTip(Produs* produs)
{
	return produs->tip;
}

char* getProducator(Produs* produs)
{
	return produs->producator;
}

char* getModel(Produs* produs)
{
	return produs->model;
}

int getPret(Produs* produs)
{
	return produs->pret;
}

int getCantitate(Produs* produs)
{
	return produs->cantitate;
}

void setID(Produs* produs, int newID)
{
	produs->ID=newID;
}

char* setTip(Produs* produs, char newTip[])
{
	strcpy(produs->tip, newTip);
}
char* setProducator(Produs* produs, char newProducator[])
{
	strcpy(produs->producator, newProducator);
}

char* setModel(Produs* produs, char newModel[])
{
	strcpy(produs->model, newModel);
}

void setPret(Produs* produs, int newPret)
{
	produs->pret=newPret;
}

void setCantitate(Produs* produs, int newCantitate)
{
	produs->cantitate=newCantitate;
}

void printProdus(Produs* produs)
{
	printf("ID: %d, Tip: %s, Producator: %s, Model: %s, Pret: %d, Cantitate: %d\n",produs->ID,produs->tip,produs->producator,produs->model,produs->pret,produs->cantitate);
}
