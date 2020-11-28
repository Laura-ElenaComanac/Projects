#include "ui.h"
#include <string.h>
#include <stdio.h>

UI* creeazaUI(ServiceProdus* serviceProdus)
{
	UI* ui=(UI*)malloc(sizeof(UI));
	ui->serviceProdus = serviceProdus;
	return ui;
}

void run(UI* ui)
{
	while (1)
	{
		printf("Lista comenzi:\n");
		printf("1. Adauga produs\n");
		printf("2. Actualizeaza cantitate produs\n");
		printf("3. Sterge produs\n");
		printf("4. Vizualizeaza produse ordonate dupa pret/cantitate\n");
		printf("5. Vizualizeaza produse filtrate dupa criteriul pret\n");
		printf("0. Iesire din aplicatie\n");

		int comanda=0;
		printf("> ");
		scanf("%d", &comanda);
		if (comanda == 1)
			addUiProdus(ui);
		if (comanda == 2)
			updateUiProdus(ui);
		if (comanda == 3)
			removeUiProdus(ui);
		if (comanda == 4)
			viewSortedUiProdus(ui);
		if (comanda == 5)
			viewCriteriuUIProdus(ui->serviceProdus);
		if (comanda == 0)
			return;
	}
}

void addUiProdus(UI* ui)
{
	int valReturnata;
	char tip[30], producator[30], model[30], ID[30], cantitate[30], pret[30];

	printf("Introduceti ID: ");
	scanf("%s", &ID);
	printf("Introduceti tip: ");
	scanf("%s", &tip);
	printf("Introduceti producator: ");
	scanf("%s", &producator);
	printf("Introduceti model: ");
	scanf("%s", &model);
	printf("Introduceti pret: ");
	scanf("%s", &pret);
	printf("Introduceti cantitate: ");
	scanf("%s", &cantitate);

	valReturnata = addServiceProdus(ui->serviceProdus, ID, tip, producator, model, pret, cantitate);

	if (valReturnata == 0)
		printf("Produs adaugat cu succes!\n");
	else
	{
		if (valReturnata > 1)
		{
			if (valReturnata % 3 == 0)
				printf("ID invalid!\n");
			if (valReturnata % 5 == 0)
				printf("Tip invalid!\n");
			if (valReturnata % 7 == 0)
				printf("Producator invalid!\n");
			if (valReturnata % 11 == 0)
				printf("Model invalid!\n");
			if (valReturnata % 2 == 0)
				printf("Pret invalid!\n");
			if (valReturnata % 13 == 0)
				printf("Cantitate invalida!\n");
		}
		else
		{
			printf("Exista deja un produs cu acest ID!\n");
			printf("S-a actualizat cantitatea produsului!\n");
		}
	}
}

void updateUiProdus(UI* ui)
{
	int valReturnata;
	char ID[30], cantitate[30];

	printf("Introduceti ID: ");
	scanf("%s", &ID);
	printf("Introduceti noua cantitate: ");
	scanf("%s", &cantitate);

	valReturnata = updateServiceProdus(ui->serviceProdus, ID, cantitate);

	if (valReturnata == 0)
		printf("Produs actualizat cu succes!\n");
	else
		if (valReturnata > 1)
		{
			if (valReturnata % 3 == 0)
				printf("ID invalid!\n");
			if (valReturnata % 13 == 0)
				printf("Cantitate invalida!\n");
		}
		else
			printf("Nu exista un produs cu acest ID!\n");
}

void removeUiProdus(UI* ui)
{
	char ID[30];
	int valReturnata;

	printf("Introduceti ID: ");
	scanf("%s", &ID);

	//printf(ID);

	valReturnata = removeServiceProdus(ui->serviceProdus,ID);

	//printf("%d", valReturnata);

	if (valReturnata == 0)
		printf("Produs sters cu succes!\n");
	else
		if (valReturnata > 1)
		{
			if (valReturnata % 3 == 0)
				printf("ID invalid!\n");
		}
		else
			printf("Nu exista un produs cu acest ID!\n");

}

void viewSortedUiProdus(UI* ui)
{
	Produs* copyProduse;
	copyProduse = viewSortedProdus(ui->serviceProdus);
	for (int i = 0; i < ui->serviceProdus->repositoryProdus->lungime; i++)
		printProdus(&copyProduse[i]);
	free(copyProduse);
}

Copy viewCriteriuUIProdus(ServiceProdus* serviceProdus)
{
	printf("Introduceti pretul dupa care se filtreaza lista: ");
	int pret;
	scanf("%d", &pret);
	Copy copie = viewCriteriuProdus(serviceProdus, pret);
	printf("Lista filtrata este:\n");
	for (int i = 0; i < copie.lungime; i++)
		printProdus(&copie.copyProduse[i]);
}

void destroyUI(UI* ui)
{
	destroyServiceProdus(ui->serviceProdus);
	free(ui);
}
