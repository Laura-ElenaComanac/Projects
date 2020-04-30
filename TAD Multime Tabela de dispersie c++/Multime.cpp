#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

int hashCode(TElem elem)
{
	return abs(elem);
}

int Multime::d(TElem elem) const
{
	// dispersia prin diviziune
	return hashCode(elem)%m;
}

Multime::Multime() {
	/* de adaugat */
	m = 2;
	lungime = 0;
	elems = new Nod*[m];
	for (int i = 0; i < m; i++)
		elems[i] = nullptr;
}

// Theta(1)
bool Multime::adauga(TElem elem) {
	/* de adaugat */
	if (cauta(elem) == false) // elementul nu exista, deci il adaugam
	{
		if (float(lungime/m) > 1)
		{// redimensionare
			m *= 2;
			Nod** newElems = new Nod*[m];
			for (int i = 0; i < m; i++)
				newElems[i] = nullptr;
			for (int i = 0; i < m/2; i++)
			{
				Nod* curent = elems[i];
				Nod* urmInitial;
				while (curent != nullptr)
				{
					int ch = d(curent->cheie);
					urmInitial = curent->urm;
					if (newElems[ch] == nullptr) // cazul in care LSI e vida
					{
						curent->urm = nullptr;
						newElems[ch] = curent;

					}
					else
					{
						curent->urm = newElems[ch];
						newElems[ch] = curent;
					}
					curent = urmInitial;
				}
			}
			delete elems;
			elems = newElems;
		}

		// adaugare
		int ch = d(elem); // cheia lui elem
		Nod* nod = new Nod;
		nod->cheie = elem;

		nod->urm = elems[ch];
		elems[ch] = nod;
		lungime++;
		return true;
	}
	else // elementul exista deja in multime
		return false;
}

// O(n), n = nr elemente
bool Multime::sterge(TElem elem) {
	/* de adaugat */
	if (cauta(elem) == true) // elementul a fost gasit, deci il stergem
	{
		int ch = d(elem); // cheia lui elem
		Nod* nodCurent = elems[ch]; // adresa nodului la care sa afla cheia lui elem in tabela
		Nod* anterior = nullptr;
		while (nodCurent != nullptr) // caut elementul dupa cheie
			if (nodCurent->cheie != elem)
			{
				anterior = nodCurent;
				nodCurent = nodCurent->urm;
			}
			else
				break;

		//stergerea

		if (anterior == nullptr)
		{
			elems[ch] = nodCurent->urm;
			delete nodCurent;
		}
		else
		{
			anterior->urm = nodCurent->urm;
			delete nodCurent;
		}
		lungime--;

		return true;
	}
	else
		return false;
}

// O(n), n = nr elemente
bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	int ch = d(elem); // cheia lui elem
	Nod* nodCurent = elems[ch]; // adresa nodului la care sa afla cheia lui elem in tabela
	while (nodCurent != nullptr) // caut elementul dupa cheie
		if (nodCurent->cheie != elem)
			nodCurent = nodCurent->urm;
		else
			break;
	if (nodCurent != nullptr)
		return true;
	else
		return false;
}


int Multime::dim() const {
	/* de adaugat */
	return lungime;
}

bool Multime::vida() const {
	/* de adaugat */
	return lungime==0;
}


Multime::~Multime() {
	/* de adaugat */
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}
