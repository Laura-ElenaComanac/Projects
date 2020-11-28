#include "Matrice.h"

#include <exception>
#include <iostream>
#include <new>
using namespace std;


Matrice::Matrice(int m, int n) {
	/* de adaugat */
	if (m <= 0 || n <= 0)
		throw exception("Bad input!");
	capacitate = 2;
	linie = new int[m + 1];
	coloana = new int[capacitate];
	valoare = new TElem[capacitate];
	nrLines = m;
	nrCols = n;
	nrElemente = 0;

	for (int i = 0; i < m + 1; i++)
		linie[i] = 0;
}



int Matrice::nrLinii() const {
	/* de adaugat */
	return nrLines;
}


int Matrice::nrColoane() const {
	/* de adaugat */
	return nrCols;
}


TElem Matrice::element(int i, int j) const {
	/* de adaugat */
	if (i < 0 || i >= nrLines || j < 0 || j >= nrCols)
		throw exception("Bad input!");
	for (int k = linie[i]; k < linie[i + 1]; k++)
		if (coloana[k] == j)
			return valoare[k];
	return NULL_TELEMENT;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	/* de adaugat */
	if (i < 0 || i >= nrLines || j < 0 || j >= nrCols)
		throw exception("Bad input!");
	for (int k = linie[i]; k < linie[i + 1]; k++)
	{
		if (coloana[k] == j)
		{
			TElem x = valoare[k];
			valoare[k] = e;
			return x;
		}
		if (nrElemente == capacitate)
		{
			capacitate *= 2;

			int* coloana2 = new int[capacitate];
			TElem* valoare2 = new TElem[capacitate];

			for (int k = 0; k < nrElemente; k++)
			{
				valoare2[k] = valoare[k];
				coloana2[k] = coloana[k];
			}

			delete coloana;
			delete valoare;

			coloana = coloana2;
			valoare = valoare2;


		}
	}

	int index = linie[i];
	for (int k = nrElemente; k > index; k--)
	{
		coloana[k] = coloana[k - 1];
		valoare[k] = valoare[k - 1];
	}
	coloana[index] = j;
	valoare[index] = e;

	for (int k = i + 1; k < nrLines + 1; k++)
		linie[k] += 1;

	nrElemente += 1;

	return NULL_TELEMENT;
}
