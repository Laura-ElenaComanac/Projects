#pragma once
#include"Service.h"
using std::cin;
using std::cout;

class UI
{
private:
	Service& service;
public:
	UI(Service& srv) : service{ srv } {}
	void addFilmUI();
	void removeFilmUI();
	void updateFilmUI();
	void showAll();
	void search();
	void filter();
	void sorting();
	void statistica();
	void run();
};