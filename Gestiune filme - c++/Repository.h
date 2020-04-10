#pragma once
#include "Film.h"
#include "VectorDinamic.h"
//#include <vector>
//using std::vector;

class RepoException {
private:
	string mesaj;
public:
	RepoException(string msg) : mesaj{ msg } {}
	string getMesaj();
};

class Repository
{
private:
	VectorDinamic<Film> filme;
public:
	Repository() = default; //default constructor

	int getPozitie(const Film& film);
	void addFilm(const Film& film);
	void removeFilm(const Film& film);
	void updateTitlu(Film& film, string& titluC);
	void updateGen(Film& film, string genC);
	void updateActor(Film& film, string actorC);
	void updateAn(Film& film, int anC);
	int searchFilm(Film& film);
	VectorDinamic<Film>& getAll();
	Film& getFilm(int i);
	int getRepoLungime();
};