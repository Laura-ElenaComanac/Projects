#pragma once
#include "Repository.h"
#include "ActiuneUndo.h"
#include <algorithm>
#include <utility>
using std::swap;
#include <map>
using std::map;
#include <vector>
using std::vector;
using std::copy_if;

class DTO
{
private:
	string gen;
	int nrFilme;
public:
	DTO(string gen, int nrFilme) : gen{ gen }, nrFilme{ nrFilme }{}
	string getGen();
	int getNrFilme();
};


class Service
{
private:
	RepositoryMare& repository;
	//RepositoryFile& repositoryFile;
	vector<std::shared_ptr<ActiuneUndo>> actiuniUndo;
public:
	Service(RepositoryMare& repo) :repository{ repo } {}
	//Service() = default;

	//~Service();

	/*Initializeaza repository cu 10 filme*/
	void initializare();

	/*Adauga un film in lista cos, gasit dupa titlu in repository
	Arunca exceptie daca filmul e inexistent*/
	void adaugaCos(string titlu);

	/*Goleste lista cos de toate filmele*/
	void golesteCos();

	/*Genereaza random nrFilme filme in cos*/
	void genereazaCos(int nrFilme);

	/*Returneaza lista cos*/
	vector<Film> getCos();


	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Adauga filmul in repository*/
	void addFilmService(string titlu, string gen, int an, string actor);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Sterge filmul din repository*/
	void removeFilmService(string titlu, string gen, int an, string actor);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Modifica titlul filmului din repository cu titluC*/
	//void updateTitluService(string titlu, string gen, int an, string actor, string titluC);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Modifica genul filmului din repository cu genC*/
	void updateGenService(string titlu, string gen, int an, string actor, string genC);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Modifica actorul filmului din repository cu anC*/
	void updateActorService(string titlu, string gen, int an, string actor, string anC);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Modifica anul filmului din repository cu anul_aparitieiC*/
	void updateAnService(string titlu, string gen, int an, string actor, int anul_aparitieiC);

	/*Formeaza un obiect de tip Film in service cu parametrii titlu, gen, an, actor
	Returneaza filmul cautat in repository*/
	string searchFilmService(string titlu, string gen, int an, string actor);

	/*Returneaza lista filtrata de filme dupa titlu si an*/
	vector<Film> filtrare(int an);

	/*Sorteaza lista de filme dupa o functie ordine*/
	vector<Film> sortare(bool ordine(const Film& s1, const Film& s2));

	/*Returneaza lista de filme*/
	vector<Film> getAll();

	/*Returneaza un film cu titlul titlu*/
	Film& getFilm(string titlu);

	/*Returneaza lungime repository*/
	int getRepoLungime();

	/*Returneaza o statistica a filmelor*/
	vector<DTO> statistica(int& sum);

	void undo();
};