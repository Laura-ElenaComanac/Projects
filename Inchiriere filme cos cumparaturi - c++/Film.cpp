#include "Film.h"

string Film::getTitlu() const {
	return titlu;
}
string Film::getGen() const {
	return gen;
}
string Film::getActor() const {
	return actor_principal;
}
int Film::getAn() const {
	return anul_aparitiei;
}

void Film::setTitlu(string titluC)
{
	this->titlu = titluC;
}

void Film::setGen(string genC)
{
	this->gen = genC;
}

void Film::setAn(int anC)
{
	this->anul_aparitiei = anC;
}

void Film::setActor(string actorC)
{
	this->actor_principal = actorC;
}

bool Film::operator==(const Film& f)
{
	if (this->titlu == f.titlu && this->gen == f.gen && this->actor_principal == f.actor_principal && this->anul_aparitiei == f.anul_aparitiei) 
		return true;
	return false;
}

string Film::printFilm()
{
	return "Titlu: "+this->titlu + " Gen: "+this->gen + " Actor principal: "+this->actor_principal + " Anul aparitiei: " + std::to_string(this->anul_aparitiei)+"\n";
}
