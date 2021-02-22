#include "IteratorMultime.h"
#include "Multime.h"

// Theta(1)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m), curent(mult.prim) {
	/* de adaugat */
	//curent = mult.prim;
}

// Theta(1)
TElem IteratorMultime::element() const {
	// de adaugat 
	return curent->elem;
}

// Theta(1)
bool IteratorMultime::valid() const {
	// de adaugat 
	return curent!= nullptr;
}

// Theta(1)
void IteratorMultime::urmator() {
	// de adaugat 
	curent = curent->next;
}

// Theta(1)
void IteratorMultime::prim() {
	// de adaugat 
	curent = mult.prim;
}