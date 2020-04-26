#pragma once
#include"Service.h"
using std::cin;
using std::cout;

class UI
{
private:
	Service& service;
public:
	UI(Service& srv) : service{ srv } {
		//service.initializare();
	}

	void showCos();
	void adaugaCos();
	void golesteCos();
	void genereazaCos();
	void printFilmeHTML(string st);
	void exportCos();

	void addFilmUI();
	void removeFilmUI();
	void updateFilmUI();
	void showAll();
	void search();
	void filter();
	void sorting();
	void statistica();
	void undo();
	void run();
};