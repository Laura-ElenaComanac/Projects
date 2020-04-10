#pragma once
#include "Repository.h"
#include <algorithm>
#include <utility>
using std::swap;
#include <map>
using std::map;
#include <vector>
using std::vector;

class DTO
{
private:
	string gen;
	int nrFilme;
public:
	DTO(string gen, int nrFilme) : gen{ gen }, nrFilme{nrFilme}{}
	string getGen();
	int getNrFilme();
};


class Service
{
private:
	Repository& repository;
public:
	Service(Repository& repo) :repository{ repo } {}
	//Service() = default;

	void addFilmService(string titlu, string gen, int an, string actor);
	void removeFilmService(string titlu, string gen, int an, string actor);
	void updateTitluService(string titlu, string gen, int an, string actor, string titluC);
	void updateGenService(string titlu, string gen, int an, string actor, string genC);
	void updateActorService(string titlu, string gen, int an, string actor, string anC);
	void updateAnService(string titlu, string gen, int an, string actor, int anul_aparitieiC);
	int searchFilmService(string titlu, string gen, int an, string actor);
	VectorDinamic<Film> filtrare(string titlu, int an);
	VectorDinamic<Film> sortare(bool ordine(const Film& s1, const Film& s2));
	VectorDinamic<Film>& getAll();
	Film& getFilm(int i);
	int getRepoLungime();
	vector<DTO> statistica();

};