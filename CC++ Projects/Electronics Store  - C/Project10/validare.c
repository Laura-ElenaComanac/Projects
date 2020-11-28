#include <stdio.h>
#include <string.h>
#include "validare.h"


int validator(Produs produs)
{
	int cod_eroare = 1;
	if (!(getID(&produs) >= 0 && getID(&produs) <= 9999999999))
		cod_eroare *= 3;
	char prod[100];
	strcpy(prod,getTip(&produs));
	int test = 1;
	for (int i = 0; i < strlen(prod); i++)
		if ((prod[i] < 'a' || prod[i] > 'z') && (prod[i] < 'A' || prod[i] > 'Z'))
			test = 0;
	if(test==0)
		cod_eroare *= 5;
	strcpy(prod,getProducator(&produs));
	test = 1;
	for (int i = 0; i < strlen(prod); i++)
		if ((prod[i] < 'a' || prod[i] > 'z') && (prod[i] < 'A' || prod[i] > 'Z'))
			test = 0;
	if (test == 0)
		cod_eroare *= 7;
	strcpy(prod, getModel(&produs));
	test = 1;
	for (int i = 0; i < strlen(prod); i++)
		if ((prod[i] < 'a' || prod[i] > 'z') && (prod[i] < 'A' || prod[i] > 'Z'))
			test = 0;
	if (test == 0)
		cod_eroare *= 11;
	if (!(getPret(&produs) >= 0 && getPret(&produs) <= 9999999999))
		cod_eroare *= 2;
	if (!(getCantitate(&produs) >= 0 && getCantitate(&produs) <= 9999999999))
		cod_eroare *= 13;
	if (cod_eroare > 1)
		return cod_eroare;
	else
		return 0;
}
int validatorString(char s[])
{
	for (int i = 0; i < strlen(s); i++)
		if (s[i] < '0' || s[i]>'9')
			return 17;
	return 0;

}