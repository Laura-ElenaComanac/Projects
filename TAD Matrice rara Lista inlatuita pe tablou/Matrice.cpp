#include "Matrice.h"

#include <exception>

using namespace std;

// Theta(c), c = capacitatea initiala
Matrice::Matrice(int m, int n) {
	/* de adaugat */
	if (m <= 0 || n <= 0)
		throw exception("Exceptie nr linii si nr coloane!");

	capacitate = 1;
	lungime = 0;
	lines = m;
	cols = n;

	prim = -1;
	primLiber = 0;

	elems = new Nod[capacitate];
	urm = new int[capacitate];

	//for (int i = 0; i < capacitate; i++)
		//elems[i].valoare = NULL_TELEMENT;

	for (int i = 0; i < capacitate-1; i++)
		urm[i] = i + 1;
	urm[capacitate-1] = -1;
}


// Theta(1)
int Matrice::nrLinii() const {
	/* de adaugat */
	return lines;
}

// Theta(1)
int Matrice::nrColoane() const {
	/* de adaugat */
	return cols;
}

// O(n), n = nr elemente
TElem Matrice::element(int i, int j) const {
	/* de adaugat */
	if (i < 0 || j < 0 || i >= lines || j >= cols)
		throw exception("Exceptie pozitie invalida in Matrice!");

	int curent = prim;

	while (curent != -1) // mai intai ajung la linie
	{
		if (elems[curent].linie == i && elems[curent].coloana == j)
			return elems[curent].valoare;
		curent = urm[curent];
	}
	return NULL_TELEMENT;
}

// O(n), n = nr elemente
TElem Matrice::modifica(int i, int j, TElem e) {
	/* de adaugat */
	if (i < 0 || j < 0 || i >= lines || j >= cols)
		throw exception("Exceptie pozitie invalida in Matrice!");

	// cazul in care lista este vida
	if (prim == -1)
	{
		if (e == NULL_TELEMENT) // daca elementul pe care vrem sa il introducem este nul
			return NULL_TELEMENT;

		// adaug pe prima pozitie elementul nenul
		Nod elem;
		elem.linie = i;
		elem.coloana = j;
		elem.valoare = e;

		prim = primLiber;
		primLiber = urm[primLiber];
		elems[prim] = elem;
		return NULL_TELEMENT;
	}
	// cazul in care adaug un element nenul
	if (primLiber == -1) // lista plina => redimensionam lista
	{
		Nod* newElems = new Nod[capacitate * 2];
		int* newUrm = new int[capacitate * 2];

		for (int i = 0; i < capacitate; i++)
		{
			newElems[i] = elems[i];
			newUrm[i] = urm[i];
		}
		for (int i = capacitate; i < capacitate * 2 - 1; i++)
			newUrm[i] = i + 1;
		newUrm[capacitate * 2 - 1] = -1;

		delete[] elems;
		delete[] urm;

		elems = newElems;
		urm = newUrm;

		primLiber = capacitate;
		capacitate *= 2;
	}

	// Parcurg lista pana cand gasesc elementul pe care trebuie sa il modific
	int curent = prim; // primul element din lista
	int anterior = -1;

	while (curent != -1 && elems[curent].linie != i) // mai intai ajung la linie
	{
		anterior = curent;
		curent = urm[curent];
	}
	while (curent != -1 && elems[curent].coloana != j && elems[curent].linie == i) // apoi la coloana
	{
		anterior = curent;
		curent = urm[curent];
	}

	if (curent == -1) // elementul nu a fost gasit, deci il adaugam in lista
	{
		if (e == NULL_TELEMENT) // daca elementul pe care vrem sa il introducem este nul
			return NULL_TELEMENT;



		// adaug in lista elementul nenul
		Nod elem;
		elem.linie = i;
		elem.coloana = j;
		elem.valoare = e;

		/*
		prim = primLiber;
		primLiber = urm[primLiber];
		elems[prim] = elem;
		*/

		curent = primLiber;
		//prim = curent;
		primLiber = urm[primLiber];
		urm[anterior] = curent;
		urm[curent] = -1;
		elems[curent] = elem;
		
		return NULL_TELEMENT;
	}

	if (anterior == -1) // trebuie sa modificam primul element din lista
	{
		if (e == NULL_TELEMENT) // stergere
			if (elems[prim].linie!=i || elems[prim].coloana!=j) // elementul nu se afla in lista
				return NULL_TELEMENT;
			else // stergerea primului element din lista
			{
				prim = urm[curent]; // primul element va fi acum al doilea
				urm[curent] = primLiber;
				primLiber = curent; // pozitia primului element devine prima pozitie libera
				return elems[curent].valoare;
			}
		else // modificare element cu cel nou
		{
			int oldE = elems[curent].valoare; // valoarea vechiului element

			Nod elem; // elementul nou
			elem.linie = i;
			elem.coloana = j;
			elem.valoare = e;

			elems[prim] = elem;

			return oldE;
		}

	}
	else // trebuie sa modificam un element din interiorul listei
	{
		if (e == NULL_TELEMENT) // stergere
			if (elems[curent].linie != i || elems[curent].coloana != j) // elementul nu se afla in lista
				return NULL_TELEMENT;
			else // stergerea unui element din interiorul listei
			{
				int auxCurent = curent;
				int oldCurent = elems[curent].valoare; // vechea valoare a elementului curent
				
				curent = urm[curent]; // elementul curent va fi acum urmatorul
				urm[anterior] = curent;
				urm[auxCurent] = primLiber;
				primLiber = auxCurent; // pozitia elementului curent initial devine prima pozitie libera
				return oldCurent;
			}
		else // modificare element cu cel nou
		{
			int oldE = elems[curent].valoare; // valoarea vechiului element

			Nod elem; // elementul nou
			elem.linie = i;
			elem.coloana = j;
			elem.valoare = e;

			elems[curent] = elem;

			return oldE;
		}
	}
}

