#include "UI.h"

void UI::addFilmUI() {
	string titlu, gen, actor_principal;
	int anul_aparitiei;
	cout << "Introduceti titlul: ";
	cin >> titlu;
	cout << "Introduceti genul: ";
	cin >> gen;
	cout << "Introduceti actorul principal: ";
	cin >> actor_principal;
	cout << "Introduceti anul aparitiei: ";
	cin >> anul_aparitiei;
	try {
		service.addFilmService(titlu, gen, anul_aparitiei, actor_principal);
		cout << "Film adaugat cu succes!\n";
	}
	catch (RepoException& ex) {
		cout << ex.getMesaj();
	}
}

void UI::removeFilmUI() {
	string titlu, gen, actor_principal;
	int anul_aparitiei;
	cout << "Introduceti titlul: ";
	cin >> titlu;
	cout << "Introduceti genul: ";
	cin >> gen;
	cout << "Introduceti actorul principal: ";
	cin >> actor_principal;
	cout << "Introduceti anul aparitiei: ";
	cin >> anul_aparitiei;
	try {
		service.removeFilmService(titlu, gen, anul_aparitiei, actor_principal);
		cout << "Film sters cu succes!\n";
	}
	catch (RepoException& ex) {
		cout << ex.getMesaj();
	}
}

void UI::updateFilmUI()
{
	string titlu, gen, actor_principal;
	int anul_aparitiei, call;
	cout << "Introduceti titlul: ";
	cin >> titlu;
	cout << "Introduceti genul: ";
	cin >> gen;
	cout << "Introduceti actorul principal: ";
	cin >> actor_principal;
	cout << "Introduceti anul aparitiei: ";
	cin >> anul_aparitiei;
	cout << "1. Titlu\n2. Gen\n3. Actor principal\n4. Anul aparitiei\n";
	cout << "Introduceti numarul corespunzator valorii pe care doriti sa o modificati: ";
	cin >> call;
	string titluC, genC, actor_principalC;
	int anul_aparitieiC;
	try {
		switch (call) {
		case 1: {
			cout << "Introduceti titlul: ";
			cin >> titluC;
			service.updateTitluService(titlu, gen, anul_aparitiei, actor_principal, titluC);
			break;
		}
		case 2: {
			cout << "Introduceti genul: ";
			cin >> genC;
			service.updateGenService(titlu, gen, anul_aparitiei, actor_principal, genC);
			break;
		}
		case 3: {
			cout << "Introduceti actorul principal: ";
			cin >> actor_principalC;
			service.updateActorService(titlu, gen, anul_aparitiei, actor_principal, actor_principalC);
			break;
		}
		case 4: {
			cout << "Introduceti anul aparitiei: ";
			cin >> anul_aparitieiC;
			service.updateAnService(titlu, gen, anul_aparitiei, actor_principal, anul_aparitieiC);
			break;
		}
		}
	cout << "Film modificat cu succes!\n";
	}
	catch (RepoException& ex) {
		cout << ex.getMesaj();
	}
}

void UI::showAll()
{
	cout << "Filme:\n";
	vector<Film> filme = service.getAll();
	for (Film& f : filme)
		cout << f.printFilm() << '\n';
}

void UI::search()
{
	string titlu, gen, actor_principal;
	int anul_aparitiei;
	cout << "Introduceti titlul: ";
	cin >> titlu;
	cout << "Introduceti genul: ";
	cin >> gen;
	cout << "Introduceti actorul principal: ";
	cin >> actor_principal;
	cout << "Introduceti anul aparitiei: ";
	cin >> anul_aparitiei;
	try {
		int i = service.searchFilmService(titlu, gen, anul_aparitiei, actor_principal);
		cout << "Filmul cautat este:\n";
		Film& film = service.getFilm(i);
		cout << film.printFilm();
	}
	catch (RepoException& ex) {
		cout << ex.getMesaj();
	}

}

void UI::filter()
{
	string titlu;
	int anul_aparitiei;
	cout << "Introduceti titlul: ";
	cin >> titlu;
	cout << "Introduceti anul aparitiei: ";
	cin >> anul_aparitiei;
	vector<Film> rez = service.filtrare(titlu, anul_aparitiei);
	cout << "Filmele filtrate sunt:\n";
	for (Film& film : rez)
		cout << film.printFilm() << '\n';
}

void UI::sorting()
{
	cout << "Filmele sortate sunt:\n";
	vector<Film> sortate = service.sortare();
	for (Film& film : sortate)
		cout << film.printFilm()<<'\n';
}

void UI::run()
{
	int comanda = -1;
	while (comanda) {
		cout << "0. Iesire aplicatie\n1. Adauga film\n2. Sterge film\n3. Modifica film\n4. Afiseaza filme\n5. Cauta film\n6. Filtreaza filme\n7. Sorteaza filme\n";
		cout << "Introduceti comanda: ";
		cin >> comanda;
		switch (comanda) {
		case 0:
		{
			comanda = 0;
			break;
		}
		case 1: {
			addFilmUI();
			break;
		}
		case 2: {
			removeFilmUI();
			break;
		}
		case 3: {
			updateFilmUI();
			break;
		}
		case 4: {
			showAll();
			break;
		}
		case 5: {
			search();
			break;
		}
		case 6: {
			filter();
			break;
		}
		case 7: {
			sorting();
			break;
		}
		}
	}
}