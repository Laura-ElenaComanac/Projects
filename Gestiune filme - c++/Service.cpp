#include "Service.h"


void Service::addFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	this->repository.addFilm(film);
}

void Service::removeFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	this->repository.removeFilm(film);
}

void Service::updateTitluService(string titlu, string gen, int an, string actor, string titluC)
{
	Film film{ titlu,gen,an,actor };
	this->repository.updateTitlu(film, titluC);
}

void Service::updateGenService(string titlu, string gen, int an, string actor, string genC)
{
	Film film{ titlu,gen,an,actor };
	this->repository.updateGen(film, genC);
}

void Service::updateActorService(string titlu, string gen, int an, string actor, string anC)
{
	Film film{ titlu,gen,an,actor };
	this->repository.updateActor(film, anC);
}

void Service::updateAnService(string titlu, string gen, int an, string actor, int anul_aparitieiC)
{
	Film film{ titlu,gen,an,actor };
	this->repository.updateAn(film, anul_aparitieiC);
}

int Service::searchFilmService(string titlu, string gen, int an, string actor)
{
	Film film{ titlu,gen,an,actor };
	if (this->repository.searchFilm(film) != -1)
		return this->repository.searchFilm(film);
	throw RepoException("Film inexistent!\n");
}

VectorDinamic<Film> Service::filtrare(string titlu, int an)
{
	VectorDinamic<Film> rez;
	VectorDinamic<Film>& filme = getAll();
	for (int i=0;i<getRepoLungime();i++)
	{
		string t = this->getFilm(i).getTitlu();
		int a = this->getFilm(i).getAn();
		if (t == titlu && a == an)
			rez.addElem(this->getFilm(i));
	}
	return rez;
}
/*
bool Service::ordine(Film& s1, Film& s2)
{
	if (strcmp(s1.getTitlu().c_str(), s2.getTitlu().c_str()) < 0)
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
*/

VectorDinamic<Film> Service::sortare(bool ordine(const Film& s1, const Film& s2))
{
	VectorDinamic<Film>& filme = getAll();
	for (int i = 0; i < (int)filme.getLungime() - 1; i++)
		for (int j = i + 1; j < (int)filme.getLungime(); j++)
			if (!ordine(filme.getElem(i), filme.getElem(j)))
				swap(filme.getElem(i), filme.getElem(j));
	return filme;
}

VectorDinamic<Film>& Service::getAll()
{
	return repository.getAll();
}

Film& Service::getFilm(int i)
{
	return repository.getFilm(i);
}

int Service::getRepoLungime()
{
	return this->repository.getRepoLungime();
}

vector<DTO> Service::statistica()
{
	VectorDinamic<Film> v = this->repository.getAll();
	map<string, int> count;
	map<string, int>::iterator iter;
	for (int i=0;i<v.getLungime();i++)
	{
		iter = count.find(v.getElem(i).getGen());
		if (iter == count.end())
			count.insert(make_pair(v.getElem(i).getGen(), 1));
		else
			count[v.getElem(i).getGen()]++;
	}
	vector<DTO> statistica;
	for (iter = count.begin(); iter != count.end(); ++iter)
	{
		DTO obj{ iter->first, iter->second };
		statistica.push_back(obj);
	}
	return statistica;
}

string DTO::getGen(){
	return gen;
}

int DTO::getNrFilme(){
	return nrFilme;
}
