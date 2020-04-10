#include "Repository.h"

string RepoException::getMesaj() {
	return mesaj;
}

int Repository::getPozitie(const Film& film) {
	for (int i = 0; i < (int)this->filme.getLungime(); i++)
	{
		if (this->filme.getElem(i) == film)
			return i;
	}
	return -1;
}

void Repository::addFilm(const Film& film) {
	for (int i=0;i<this->filme.getLungime();i++)
	{
		if (this->filme.getElem(i) == film)
			throw RepoException("Film deja existent!");
	}
	this->filme.addElem(film);
}
void Repository::removeFilm(const Film& film)
{
	for (int i = 0; i < this->filme.getLungime(); i++)
	{
		if (this->filme.getElem(i) == film)
		{
			//filme.erase(filme.begin() + getPozitie(f));
			this->filme.deleteElem(i);
			return;
		}
	}
	throw RepoException("Film inexistent!");
}

void Repository::updateTitlu(Film& film, string& titluC)
{
	int i = searchFilm(film);
	if (i != -1)
		this->filme.getElem(i).setTitlu(titluC);
}

void Repository::updateGen(Film& film, string genC)
{
	int i = searchFilm(film);
	if (i != -1)
		this->filme.getElem(i).setGen(genC);
}

void Repository::updateActor(Film& film, string actorC)
{
	int i = searchFilm(film);
	if (i != -1)
		this->filme.getElem(i).setActor(actorC);
}

void Repository::updateAn(Film& film, int anC)
{
	int i = searchFilm(film);
	if (i != -1)
		this->filme.getElem(i).setAn(anC);
}

int Repository::searchFilm(Film& film)
{
	for (int i = 0; i < (int)this->filme.getLungime(); i++)
		if (this->filme.getElem(i) == film)
			return i;
	return -1;
}

VectorDinamic<Film>& Repository::getAll() {
	return this->filme;
}

Film& Repository::getFilm(int i)
{
	return this->filme.getElem(i);
}

int Repository::getRepoLungime()
{
	return this->filme.getLungime();
}
