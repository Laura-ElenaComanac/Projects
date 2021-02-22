#include "service.h"

ServiceProdus* creeazaServiceProdus(RepositoryProdus* repositoryProdus)
{
	ServiceProdus* serviceProdus=(ServiceProdus*)malloc(sizeof(ServiceProdus));

	serviceProdus->repositoryProdus = repositoryProdus;

	return serviceProdus;
}

Produs* getServiceProdus(ServiceProdus* serviceProdus, int index)
{
	return getProdus(serviceProdus->repositoryProdus, index);
}

int addServiceProdus(ServiceProdus* serviceProdus, char ID[], char tip[], char producator[], char model[], char pret[], char cantitate[])
{
	
	int error=1;

	if (validatorString(ID) == 17)
		error *= 3;
	if (validatorString(pret) == 17) 
		error *= 2;
	if (validatorString(cantitate) == 17)
		error *= 13;


	Produs newProdus = creeazaProdus(atoi(ID), tip, producator, model, atoi(pret), atoi(cantitate));

	int error2 = validator(newProdus);

	if (error != 1 && error2!=0)
		return error*error2;
	if (error != 1)
		return error;
	if (error2 != 0)
		return error2;


	return addProdus(serviceProdus->repositoryProdus, newProdus);
}

int updateServiceProdus(ServiceProdus* serviceProdus, char ID[], char newCantitate[])
{
	int error = 1;

	if (validatorString(ID) == 17)
		error *= 3;
	if (validatorString(newCantitate) == 17)
		error *= 13;

	if (error != 1)
		return error;

	return updateProdus(serviceProdus->repositoryProdus, atoi(ID), atoi(newCantitate));
}

int removeServiceProdus(ServiceProdus* serviceProdus, char ID[])
{
	int error = 1;

	if (validatorString(ID) == 17)
		error *= 3;
	if (error != 1)
		return error;

	return removeProdus(serviceProdus->repositoryProdus, atoi(ID));
}

Produs* viewSortedProdus(ServiceProdus* serviceProdus)
{
	Produs* copyProduse = (Produs*)malloc(serviceProdus->repositoryProdus->lungime*sizeof(Produs));
	for (int i = 0; i < serviceProdus->repositoryProdus->lungime; i++)
		copyProduse[i] = *getServiceProdus(serviceProdus, i);
	for (int i = 0; i < serviceProdus->repositoryProdus->lungime-1; i++)
		for (int j = i+1; j < serviceProdus->repositoryProdus->lungime; j++)
			if (getPret(&copyProduse[i]) > getPret(&copyProduse[j]))
			{
				Produs aux;
				aux = copyProduse[i];
				copyProduse[i] = copyProduse[j];
				copyProduse[j] = aux;
			}
			else
				if (getPret(&copyProduse[i]) == getPret(&copyProduse[j]) && getCantitate(&copyProduse[i])<getCantitate(&copyProduse[j]))
				{
					Produs aux;
					aux = copyProduse[i];
					copyProduse[i] = copyProduse[j];
					copyProduse[j] = aux;
				}
	return copyProduse;
}

Copy viewCriteriuProdus(ServiceProdus* serviceProdus, int pret)
{
	Copy copie;
	Produs* copyProduse = (Produs*)malloc(serviceProdus->repositoryProdus->lungime * sizeof(Produs));
	int k = 0;
	for (int i = 0; i < serviceProdus->repositoryProdus->lungime; i++)
		if (getPret(&serviceProdus->repositoryProdus->produse[i]) == pret)
		{
			copyProduse[k] = serviceProdus->repositoryProdus->produse[i];
			k++;
		}
	copie.copyProduse = copyProduse;
	copie.lungime = k;
	return copie;
}

void destroyServiceProdus(ServiceProdus* serviceProdus)
{
	destroyRepository(serviceProdus->repositoryProdus);
	free(serviceProdus);
}
