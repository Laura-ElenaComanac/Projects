#include "ui.h"
#include <string.h>
#include <stdio.h>

UI creeazaUI(ServiceProdus* serviceProdus)
{
	UI ui;
	ui.serviceProdus = serviceProdus;
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
		printf("5. Vizualizeaza produse filtrate dupa un criteriu (producator, pret, cantitate)\n");
		//char userInput[50];
		//userInput[0] = '\0';

		int comanda=0;
		printf("> ");
		scanf("%d", &comanda);
		if (comanda == 1)
			addUiProdus(ui);
		if (comanda == 2)
			updateUiProdus(ui);
		if (comanda == 3)
			removeUiProdus(ui);
		//if (comanda == 4)
	//		viewSortedUiProdus(ui);
		if (comanda == 0)
			return;
	}
}

void addUiProdus(UI* ui)
{
	int ID, valReturnata, cantitate, pret;;
	char tip[30], producator[30], model[30];

	printf("Introduceti ID: ");
	scanf("%d", &ID);
	printf("Introduceti tip: ");
	scanf("%s", &tip);
	printf("Introduceti producator: ");
	scanf("%s", &producator);
	printf("Introduceti model: ");
	scanf("%s", &model);
	printf("Introduceti pret: ");
	scanf("%d", &pret);
	printf("Introduceti cantitate: ");
	scanf("%d", &cantitate);

	valReturnata = addServiceProdus(ui->serviceProdus, ID, tip, producator, model, pret, cantitate);

	if (valReturnata == 0)
		printf("Produs adaugat cu succes!\n");
	else
	{
		if (valReturnata > 1)
		{
			if (valReturnata % 3 == 0)
				printf("\nID invalid!");
			if (valReturnata % 5 == 0)
				printf("\nTip invalid!\n");
			if (valReturnata % 7 == 0)
				printf("\nProducator invalid!\n");
			if (valReturnata % 11 == 0)
				printf("\nModel invalid!\n");
			if (valReturnata % 2 == 0)
				printf("\nPret invalid!\n");
			if (valReturnata % 13 == 0)
				printf("\nCantitate invalida!\n");
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
	int ID, valReturnata, cantitate;

	printf("Introduceti ID: ");
	scanf("%d", &ID);
	printf("Introduceti noua cantitate: ");
	scanf("%d", &cantitate);

	valReturnata = updateServiceProdus(ui->serviceProdus, ID, cantitate);

	if (valReturnata == 0)
		printf("Produs actualizat cu succes!\n");
	else
		printf("Nu exista un produs cu acest ID!\n");
}

void removeUiProdus(UI* ui)
{
	int ID, valReturnata;

	printf("Introduceti ID: ");
	scanf("%d", &ID);

	valReturnata = removeServiceProdus(ui->serviceProdus,ID);

	if (valReturnata == 0)
		printf("Produs sters cu succes!\n");
	else
		printf("Nu exista un produs cu acest ID!\n");

}

void viewSortedUiProdus(UI* ui)
{
	for (int i = 0; i < ui->serviceProdus->repositoryProdus->lungime; i++)
		printProdus(getServiceProdus(ui->serviceProdus, i));
}
