#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//Theta(1)
bool rel(TElem e1, TElem e2)
{
	if (e1 <= e2)
		return true;
	return false;
}

//Theta(1)
Multime::Multime() {
	/* de adaugat */
	prim = NULL;
	lungime = 0;
}

// cazul favorabil Theta(1) - inserez la inceput
// cazul defavorabil Theta(n) - adaug la finalul listei

// O(n), n = nr elemente
bool Multime::adauga(TElem elem) {// inserare
	/* de adaugat */

	if (cauta(elem) == true) // elementul deja exista in lista
		return false;

	//creeazaNodLSI
	Nod* nou= new Nod;
	nou->elem = elem;
	nou->next = NULL;

	if (prim == NULL || rel(elem, prim->elem)) // daca se adauga la inceputul listei
	{
		nou->next = prim;
		prim = nou;
		lungime++;
		return true;
	}
	else
	{
		Nod* q = prim; // nou se adauga dupa q, q<nou
		//se parcurge pana la nodul q dupa care trebuie adaugat nou
		while (q->next != NULL && !(rel(elem, q->next->elem)))
			q = q->next;
		if (elem != q->elem) // daca elem nu mai apare in multime
		{
			nou->next = q->next; // nodul urmator a lui nou devine nodul urmator al lui q, nou=q 
			q->next = nou; // nodul urmator al lui q devine nodul nou, q+1=nou
			lungime++;
			return true;
		}
	}
	return false;
}

// O(n), n = nr elemente
bool Multime::sterge(TElem elem) {
	/* de adaugat */

	if (lungime == 0) // lista e vida
		return false;

	Nod* p, *q; // p este adresa nodului din lista care va fi sters
	// q e nod auxiliar

	p = prim;
	if (prim->elem == elem) // daca se sterge primul element al listei
	{
		prim = prim->next;
		delete p;
		lungime--;
		return true;
	}
	while (p->next != NULL && p->next->elem != elem)
		p = p->next;

	if (p->next == NULL)// elementul nu se afla in lista
		return false;
	if (p->next->elem == elem) // se sterge elementul gasit
	{
		q = p->next;
		p->next = q->next;
		delete q;
		lungime--;
		return true;
	}
}

// O(n), n = nr elemente
bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	Nod* p = prim;
	while (p != NULL)
	{
		if (p->elem == elem)
			return true;
		p = p->next;
	}
	return false;
}

// Theta(1)
int Multime::dim() const {
	/* de adaugat */
	return lungime;
}

// Theta(1)
bool Multime::vida() const {
	/* de adaugat */
	return prim == NULL; // lungime == 0
}

// Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

// Theta(n), n = nr elemente
Multime::~Multime() {
	/* de adaugat */
	Nod* p = prim;
	while (p != NULL)
	{
		Nod* aux = p->next;
		delete p;
		p = aux;
	}
}





