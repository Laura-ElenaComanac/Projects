#include "Repository.h"

string RepoException::getMesaj() {
	return mesaj;
}

int Repository::getPozitie(const Film& film){

	for (int i = 0;i <(int)filme.size();i++) {
		if (filme[i] == film)
			return i;
	}
	return -1;
}

void Repository::addFilm(const Film& film) {
	for (Film& f : filme) {
		if (f==film)
			throw RepoException("Film deja existent!");
	}
	filme.push_back(film);
}
void Repository::removeFilm(const Film& film)
{
		for (Film& f : filme) {
			if (f == film)
			{
				filme.erase(filme.begin() + getPozitie(f));
				return;
			}
		}
	throw RepoException("Film inexistent!");
}

void Repository::updateTitlu(Film& film, string titluC)
{
	int i = searchFilm(film);
	if (i != -1)
		filme[i].setTitlu(titluC);
}

void Repository::updateGen(Film& film, string genC)
{
	int i = searchFilm(film);
	if (i != -1)
		filme[i].setGen(genC);
}

void Repository::updateActor(Film& film, string actorC)
{
	int i = searchFilm(film);
	if (i != -1)
		filme[i].setActor(actorC);
}

void Repository::updateAn(Film& film, int anC)
{
	int i = searchFilm(film);
	if (i != -1)
		filme[i].setAn(anC);
}

int Repository::searchFilm(const Film& film)
{
	for (int i = 0; i < (int)filme.size(); i++)
		if (filme[i] == film)
			return i;
	return -1;
}

const vector<Film>& Repository::getAll() {
	return filme;
}

Film& Repository::getFilm(int i)
{
	return filme[i];
}
void testRepo() {
	Repository repo;
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	repo.addFilm(film);
	//const auto& filme = repo.getAll();
	const vector<Film>& filme = repo.getAll();
	assert(filme.size() == 1);

	try {
		repo.addFilm(film);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	repo.removeFilm(film);
	assert(filme.size() == 0);

	try {
		repo.removeFilm(film);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testFilm()
{
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	assert(film.getTitlu() == "Titanic");
	assert(film.getGen() == "drama");
	assert(film.getAn() == 1997);
	assert(film.getActor() == "LeonardoDiCaprio");
	film.setTitlu("Terminator");
	assert(film.getTitlu() == "Terminator");
	film.setGen("SF");
	assert(film.getGen() == "SF");
	film.setAn(1984);
	assert(film.getAn() == 1984);
	film.setActor("Arnold");
	assert(film.getActor() == "Arnold");
}