#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& mult) : multime(mult) {
	/* de adaugat */
	pozCurent = 0;
	deplasare();
}

void IteratorMultime::deplasare()
{
	//gaseste prima lista nevida incepand cu locatia pozCurent din tabela
	while (pozCurent < multime.m && multime.elems[pozCurent] == nullptr)
		pozCurent++;
	if (pozCurent < multime.m)
		nodCurent = multime.elems[pozCurent];
	else
		nodCurent = nullptr;
}

void IteratorMultime::prim() {
	/* de adaugat */
	pozCurent = 0;
	deplasare();
}


void IteratorMultime::urmator() {
	/* de adaugat */
	nodCurent = nodCurent->urm;
	// daca s-a terminat de iterat lista curenta, cautam prima lista nevida, pentru a repozitiona iteratorul
	if (nodCurent == nullptr)
	{
		pozCurent++;
		deplasare();
	}
}


TElem IteratorMultime::element() const {
	/* de adaugat */
	return nodCurent->cheie;
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	return pozCurent<multime.m && nodCurent!=nullptr;
}