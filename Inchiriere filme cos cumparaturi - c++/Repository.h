#pragma once
#include "Film.h"
#include <vector>
using std::vector;

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
	vector<Film> filme;
public:
	Repository() = default; //default constructor

	int getPozitie(const Film& film);
	void addFilm(const Film& film);
	void removeFilm(const Film& film);
	void updateTitlu(Film& film, string titluC);
	void updateGen(Film& film, string genC);
	void updateActor(Film& film, string actorC);
	void updateAn(Film& film, int anC);
	int searchFilm(const Film& film);
	const vector<Film>& getAll();
	Film& getFilm(int i);
};
void testRepo();
void testFilm();