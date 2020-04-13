#pragma once
#include "Exceptii.h"
#include "Film.h"
#include "VectorDinamic.h"
#include <vector>
using std::vector;
#include <numeric>
using std::iota;

#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock


class Repository
{
private:
	vector<Film> cos;
	vector<Film> filme;
public:
	Repository() = default; //default constructor

	/*Initializeaza repository cu 10 filme*/
	void initializeazaRepo();

	/*Returneaza lista cos*/
	vector<Film> getCos();

	/*Adauga un film in lista cos, gasit dupa titlu in repository
	Arunca exceptie daca filmul e inexistent*/
	void adaugaCos(string titlu);

	/*Goleste lista cos de toate filmele*/
	void golesteCos();

	/*Genereaza random nrFilme filme in cos*/
	void genereazaCos(int nrFilme);


	/*Returneaza pozitia filmului film*/
	int getPozitie(const Film& film);

	/*Adauga filmul in lista de filme
	Arunca exceptie daca filmul deja exista*/
	void addFilm(const Film& film);

	/*Sterge filmul din lista de filme
	Arunca exceptie daca filmul nu exista*/
	void removeFilm(const Film& film);

	/*Modifica titlul filmului din lista de filme cu titluC*/
	void updateTitlu(Film& film, string& titluC);

	/*Modifica genul filmului din lista de filme cu genC*/
	void updateGen(Film& film, string genC);

	/*Modifica actorul filmului din lista de filme cu actorC*/
	void updateActor(Film& film, string actorC);

	/*Modifica anul filmului din lista de filme cu anC*/
	void updateAn(Film& film, int anC);

	/*Returneaza lista de filme*/
	vector<Film>& getAll();

	/*Rrturneaza filmul de pe pozitia i*/
	Film& getFilm(int i);

	/*Retuneaza lungime repository*/
	int getRepoLungime();
};