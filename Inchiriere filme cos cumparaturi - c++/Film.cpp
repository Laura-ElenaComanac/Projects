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

void Film::setTitlu(const string& titluC)
{
	this->titlu=titluC;
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

const string Film::printFilm()
{
	return "Titlu: " + this->titlu + "/ Gen: " + this->gen + "/ Actor principal: " + this->actor_principal + "/ Anul aparitiei: " + std::to_string(this->anul_aparitiei) + "\n";
}

const string Film::printFilmCVS()
{
	return this->titlu + "," + this->gen + "," + std::to_string(this->anul_aparitiei) + "," + this->actor_principal + "\n";
}

string Film::printFilmHTML()
{
	string s = "\t\t<tr>\n";
	s += "\t\t\t<td>" + this->titlu + "</td>\n";
	s += "\t\t\t<td>" + this->gen + "</td>\n";
	s += "\t\t\t<td>" + this->actor_principal + "</td>\n";
	s += "\t\t\t<td>" + std::to_string(this->anul_aparitiei) + "</td>\n";
	s += "\t\t</tr>\n";
	return s;
}

