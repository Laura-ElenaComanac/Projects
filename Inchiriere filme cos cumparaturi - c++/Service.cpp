#include "Service.h"

void Service::addFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	repository.addFilm(film);
}

void Service::removeFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	repository.removeFilm(film);
}

void Service::updateTitluService(string titlu, string gen, int an, string actor, string titluC)
{
	Film film{ titlu,gen,an,actor };
	repository.updateTitlu(film, titluC);
}

void Service::updateGenService(string titlu, string gen, int an, string actor, string genC)
{
	Film film{ titlu,gen,an,actor };
	repository.updateGen(film, genC);
}

void Service::updateActorService(string titlu, string gen, int an, string actor, string anC)
{
	Film film{ titlu,gen,an,actor };
	repository.updateActor(film, anC);
}

void Service::updateAnService(string titlu, string gen, int an, string actor, int anul_aparitieiC)
{
	Film film{ titlu,gen,an,actor };
	repository.updateAn(film, anul_aparitieiC);
}

int Service::searchFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	if(repository.searchFilm(film)!=-1)
		return repository.searchFilm(film);
	throw RepoException("Film inexistent!\n");
}

vector<Film> Service::filtrare(string titlu, int an)
{
	vector<Film> rez;
	const vector<Film> filme = getAll();
	for (const Film& film : filme)
	{
		string t = film.getTitlu();
		int a = film.getAn();
		if (t == titlu && a == an)
			rez.push_back(film);
	}
	return rez;
}

bool Service::ordine(Film& s1, Film& s2)
{
	if(strcmp(s1.getTitlu().c_str(),s2.getTitlu().c_str())<0)
		return true;
	if (strcmp(s1.getTitlu().c_str(), s2.getTitlu().c_str()) > 0)
		return false;
	if (strcmp(s1.getActor().c_str(), s2.getActor().c_str()) < 0)
		return true;
	if (strcmp(s1.getActor().c_str(), s2.getActor().c_str()) > 0)
		return false;
	if (s1.getAn() < s2.getAn())
		return true;
	if (s1.getAn() > s2.getAn())
		return false;
	if (strcmp(s1.getGen().c_str(), s2.getGen().c_str()) < 0)
		return true;
	if (strcmp(s1.getGen().c_str(), s2.getGen().c_str()) > 0)
		return false;
	return true;
}

vector<Film> Service::sortare()
{
	vector<Film> filme = getAll();
	for (int i = 0; i < (int)filme.size() - 1; i++)
		for (int j = i + 1; j < (int)filme.size(); j++)
			if(!ordine(filme[i],filme[j]))
				swap(filme[i], filme[j]);
	return filme;

}

const vector<Film> Service::getAll()
{
	return repository.getAll();
}

Film& Service::getFilm(int i)
{
	return repository.getFilm(i);
}

void testFilmService() {
	Repository repo;
	Service srv{ repo };
	srv.addFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");
	const auto& filme1 = srv.getAll();
	assert(filme1.size() == 1);
	srv.removeFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");
	const auto& filme2 = srv.getAll();
	assert(filme2.size() == 0);
}