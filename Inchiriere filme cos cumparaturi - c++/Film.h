#pragma once
#include <assert.h>
#include <string>
#include <iostream>
using std::string;
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class Film
{
private:
	string titlu, gen, actor_principal;
	int anul_aparitiei;
public:
	//Constructor
	Film(string titlu, string gen, int an, string actor) :titlu{ titlu }, gen{ gen }, anul_aparitiei{ an }, actor_principal{ actor }{}
	string getTitlu() const;
	string getGen() const;
	string getActor() const;
	int getAn() const;
	void setTitlu(string titlu);
	void setGen(string gen);
	void setAn(int an);
	void setActor(string actor);
	bool operator==(const Film& f);
	string printFilm();

	
	//Copy constructor
	/*
	Film(const Film& film) :titlu{ film.titlu }, gen{ film.gen }, anul_apariției{ film.an }, actor_principal{ film.actor }{
		{
	}*/
};

