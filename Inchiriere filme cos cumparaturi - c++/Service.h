#pragma once
#include "Repository.h"
#include <algorithm>
#include <utility>
using std::swap;

class Service
{
private:
	Repository& repository;
public:
	Service(Repository& repo) :repository{repo}{}
	//Service() = default;

	void addFilmService(string titlu, string gen, int an, string actor);
	void removeFilmService(string titlu, string gen, int an, string actor);
	void updateTitluService(string titlu, string gen, int an, string actor, string titluC);
	void updateGenService(string titlu, string gen, int an, string actor, string genC);
	void updateActorService(string titlu, string gen, int an, string actor, string anC);
	void updateAnService(string titlu, string gen, int an, string actor, int anul_aparitieiC);
	int searchFilmService(string titlu, string gen, int an, string actor);
	vector<Film> filtrare(string titlu, int an);
	bool ordine(Film& s1, Film& s2);
	vector<Film> sortare();
	const vector<Film> getAll();
	Film& getFilm(int i);
};

void testFilmService();