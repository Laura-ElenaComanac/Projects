#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

class Film
{
private:
	string titlu, gen, actor_principal;
	int anul_aparitiei;

public:
	//Constructor
	Film() = default;
	Film(string titlu, string gen, int an, string actor) :titlu{ titlu }, gen{ gen }, anul_aparitiei{ an }, actor_principal{ actor }{}
	string getTitlu() const;
	string getGen() const;
	string getActor() const;
	int getAn() const;
	void setTitlu(const string& titlu);
	void setGen(string gen);
	void setAn(int an);
	void setActor(string actor);
	bool operator==(const Film& f);
	string printFilm();


	//Copy constructor
	/*
	Film(const Film& film) :titlu{ film.titlu }, gen{ film.gen }, anul_apari?iei{ film.an }, actor_principal{ film.actor }{
		{
	}*/
};

