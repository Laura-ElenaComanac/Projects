#include "service.h"

ServiceProdus creeazaServiceProdus(RepositoryProdus* repositoryProdus)
{
	ServiceProdus serviceProdus;

	serviceProdus.repositoryProdus = repositoryProdus;

	return serviceProdus;
}

Produs* getServiceProdus(ServiceProdus* serviceProdus, int index)
{
	return getProdus(serviceProdus->repositoryProdus, index);
}

int addServiceProdus(ServiceProdus* serviceProdus, int ID, char tip[], char producator[], char model[], int pret, int cantitate)
{
	Produs newProdus = creeazaProdus(ID, tip, producator, model, pret, cantitate);

	int error=validator(newProdus);

	if (error != 0)
		return error;

	return addProdus(serviceProdus->repositoryProdus, newProdus);
}

int updateServiceProdus(ServiceProdus* serviceProdus, int ID, int newCantitate)
{
	return updateProdus(serviceProdus->repositoryProdus, ID, newCantitate);
}

int removeServiceProdus(ServiceProdus* serviceProdus, int ID)
{
	return removeProdus(serviceProdus->repositoryProdus, ID);
}

void viewSotrtedProdus(ServiceProdus* serviceProdus, Produs produs)
{
	for(int i=0;i<serviceProdus->repositoryProdus->lungime;i++)
		for (int j = i + 1; j < serviceProdus->repositoryProdus->lungime - 1; j++)
			if (serviceProdus->repositoryProdus->produse[i].cantitate > serviceProdus->repositoryProdus->produse[j].cantitate)
			{
				Produs aux = serviceProdus->repositoryProdus->produse[i];
				serviceProdus->repositoryProdus->produse[i] = serviceProdus->repositoryProdus->produse[j];
				serviceProdus->repositoryProdus->produse[j] = aux;
			}
}

void viewCriteriuProdus(ServiceProdus* serviceProdus, Produs produs)
{

}
