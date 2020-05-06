#pragma once
#include "Film.h"

template <typename TElem>
class VectorDinamic {
private:
	int lungime, capacitate;
	TElem* elems;

	void cresteDimensiune();
	void scadeDimensiune();

public:
	// constructor
	VectorDinamic();

	// copy constructor
	VectorDinamic(const VectorDinamic<TElem>& vectorDinamic);

	// destructor
	~VectorDinamic();

	VectorDinamic& operator=(const VectorDinamic<TElem>& vectorDinamic);

	void addElem(const TElem& elem);
	void deleteElem(int poz);
	int getLungime();
	TElem& getElem(int poz);
	int findElem(const TElem& elem);

};

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic() {
	this->capacitate = 2;
	this->lungime = 0;
	this->elems = new TElem[this->capacitate];
}

template <typename TElem>
VectorDinamic<TElem>::VectorDinamic(const VectorDinamic<TElem>& vectorDinamic) {
	this->capacitate = vectorDinamic.capacitate;
	this->lungime = vectorDinamic.lungime;
	this->elems = new TElem[this->capacitate];

	for (int i = 0; i < this->lungime; i++)
		this->elems[i] = vectorDinamic.elems[i];

}

template <typename TElem>
VectorDinamic<TElem>::~VectorDinamic() {
	delete[] this->elems;
}

template <typename TElem>
VectorDinamic<TElem>& VectorDinamic<TElem> ::operator=(const VectorDinamic<TElem>& vectorDinamic) {
	if (this == &vectorDinamic)
		return *this;

	this->capacitate = vectorDinamic.capacitate;
	this->lungime = vectorDinamic.lungime;
	delete[] this->elems;

	this->elems = new TElem[this->capacitate];

	for (int i = 0; i < this->lungime; i++)
		this->elems[i] = vectorDinamic.elems[i];

	return *this;
}

template <typename TElem>
void VectorDinamic<TElem>::addElem(const TElem& elem) {
	if (this->capacitate - 1 == this->lungime)
		cresteDimensiune();
	this->elems[lungime] = elem;
	this->lungime++;
}

template <typename TElem>
void VectorDinamic<TElem>::deleteElem(int poz) {
	for (int i = poz; i < this->lungime; i++)
		this->elems[i] = this->elems[i + 1];
	if (this->capacitate / 2 == this->lungime)
		scadeDimensiune();
	this->lungime--;
}

template <typename TElem>
int VectorDinamic<TElem>::getLungime() {
	return this->lungime;
}

template <typename TElem>
TElem& VectorDinamic<TElem>::getElem(int poz) {
	return this->elems[poz];
}

template <typename TElem>
int VectorDinamic<TElem>::findElem(const TElem& elem) {
	for (int i = 0; i < this->lungime; i++)
		if (this->elems[i] == elem)
			return i;
	return -1;
}

template <typename TElem>
void VectorDinamic<TElem>::cresteDimensiune() {
	this->capacitate *= 2;
	TElem* largerElems = new TElem[this->capacitate];

	for (int i = 0; i <= this->lungime; i++)
		largerElems[i] = this->elems[i];

	delete[] this->elems;
	this->elems = largerElems;
}

template <typename TElem>
void VectorDinamic<TElem>::scadeDimensiune() {
	this->capacitate /= 2;
	TElem* smallerElems = new TElem[this->capacitate];

	for (int i = 0; i < this->lungime; i++)
		smallerElems[i] = this->elems[i];

	delete[] this->elems;
	this->elems = smallerElems;
}

