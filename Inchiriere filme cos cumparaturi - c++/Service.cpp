#include "Service.h"


void Service::initializare()
{
	repository.initializeazaRepo();
}

void Service::adaugaCos(string titlu)
{
	repository.adaugaCos(titlu);
}

void Service::golesteCos()
{
	repository.golesteCos();
}

void Service::genereazaCos(int nrFilme)
{
	repository.genereazaCos(nrFilme);
}

vector<Film> Service::getCos()
{
	return repository.getCos();
}


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
	if (this->repository.getPozitie(film) != -1)
		return this->repository.getPozitie(film);
	throw RepoException("Film inexistent!\n");
}

vector<Film> Service::filtrare(string titlu, int an)
{
	vector<Film> filme = this->getAll();
	vector<Film> filtered { filme.size() };

	/*
	for (int i=0;i<getRepoLungime();i++)
	{
		string t = this->getFilm(i).getTitlu();
		int a = this->getFilm(i).getAn();
		if (t == titlu && a == an)
			rez.push_back(this->getFilm(i));
	}*/

	auto iterator = copy_if(filme.begin(), filme.end(), filtered.begin(),
		[titlu, an](const Film& filmCurent)
		{return filmCurent.getTitlu().compare(titlu) == 0 && filmCurent.getAn() == an; });

	filtered.resize(iterator - filtered.begin());

	return filtered;
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

vector<Film> Service::sortare(bool ordine(const Film& s1, const Film& s2))
{
	vector<Film>& filme = getAll();
	/*
	for (int i = 0; i < (int)filme.size() - 1; i++)
		for (int j = i + 1; j < (int)filme.size(); j++)
			if (!ordine(filme[i], filme[j]))
				swap(filme[i], filme[j]);
	*/

	std::sort(filme.begin(), filme.end(), ordine);

	return filme;
}

vector<Film>& Service::getAll()
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
	vector<Film> v = repository.getAll();
	map<string, int> count;
	map<string, int>::iterator iter;
	for (int i=0;i<v.size();i++)
	{
		iter = count.find(v[i].getGen());
		if (iter == count.end())
			count.insert(make_pair(v[i].getGen(), 1));
		else
			count[v[i].getGen()]++;
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
