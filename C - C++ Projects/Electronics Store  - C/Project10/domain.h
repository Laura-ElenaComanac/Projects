#pragma once

//identificator unic, tip (laptop, frigider, televizor,etc), producator, model, pret, cantitate.

typedef struct {
	int ID, pret, cantitate;
	char tip[30], producator[30], model[30];
}Produs;

Produs creeazaProdus(int ID, char tip[], char producator[], char model[], int pret, int cantitate);

int getID(Produs* produs);
/*Returneaza ID-ul produsului*/

char* getTip(Produs* produs);
/*Returneaza tipul produsului*/

char* getProducator(Produs* produs);
/*Returneaza producatorul produsului*/

char* getModel(Produs* produs);
/*Returneaza modelul produsului*/

int getPret(Produs* produs);
/*Returneaza pretul produsului*/

int getCantitate(Produs* produs);
/*Returneaza cantitatea produsului*/

void setID(Produs* produs, int newID);
/*Seteaza ID-ul produsului cu newID*/

char* setTip(Produs* produs, char newTip[]);
/*Seteaza tipul produsului cu newTip*/

char* setProducator(Produs* produs, char newProducator[]);
/*Seteaza producatorul produsului cu newProducator*/

char* setModel(Produs* produs, char newModel[]);
/*Seteaza modelul produsului cu newModel*/

void setPret(Produs* produs, int newPret);
/*Seteaza pretul produsului cu newPret*/

void setCantitate(Produs* produs, int newCantiatate);
/*Seteaza cantitatea produsului cu newCantiatate*/

void printProdus(Produs* produs);
/*Printeaza produsul produs*/

