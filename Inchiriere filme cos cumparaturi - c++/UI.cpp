#include "UI.h"

void UI::showCos()
{
	cout << "Filmele din cos sunt:\n\n";
	vector<Film> cos = service.getCos();

	for (Film film : cos)
		cout << film.printFilm();
}

void UI::adaugaCos()
{
	string titlu;

	cout << "Adauga in cos un film dupa titlu\n";
	cout << "Introduceti titlu film: ";

	cin >> titlu;
	try {
		service.adaugaCos(titlu);
		cout << "\nFilm adaugat in cos cu succes!\n";
		cout << "\nNumarul total de filme din cos este: "<<service.getCos().size()<<"\n\n";
	}
	catch (RepoException& ex) {
		cout << ex.getMesaj();
	}
}

void UI::golesteCos()
{
	cout << "Sterge toate produsele din cos\n";
	service.golesteCos();
	cout << "\nCos golit cu succes!\n";
	cout << "\nNumarul total de filme din cos este: " << service.getCos().size() << "\n\n";
}

void UI::genereazaCos()
{
	cout << "Genereaza cos\n";
	cout << "Introduceti numarul total de filme:";
	int nrFilme;
	cin >> nrFilme;
	service.genereazaCos(nrFilme);
	cout << "\nCos generat cu succes!\n";
	cout << "\nNumarul total de filme din cos este: " << service.getCos().size() << "\n\n";
}

void UI::printFilmeHTML(string st)
{
	std::ofstream f{ st };
	f << "<!DOCTYPE html>\n";
	f << "<html>\n";
	f << "\t<head>\n";
	f << "\t\t<title>Inchiriere filme</title>\n";
	f << "\t</head>\n";
	f << "\t<body>\n";
	f << "\t\t<table>\n";
	f << "\t\t<tr>\n";
	f << "\t\t\t<td>Titlu</td>\n";
	f << "\t\t\t<td>Gen</td>\n";
	f << "\t\t\t<td>Actor principal</td>\n";
	f << "\t\t\t<td>Anul aparitiei</td>\n";
	f << "\t\t</tr>\n";

	for (Film film : service.getCos())
		f << film.printFilmHTML();

	f << "\t\t</table>\n";
	f << "\t</body>\n";
	f << "</html>\n";
}

void UI::exportCos()
{
	string nume_fisier;
	string extensie;

	cout << "Salveaza cos in fisier\n";
	cout << "Introduceti extensia (cvs / html) pe care doriti sa o folositi pentru fisier: ";
	cin >> extensie;
	cout << "Introduceti numele fisierului: ";
	cin >> nume_fisier;

	if (extensie == "cvs")
	{
		std::ofstream f{ nume_fisier + ".cvs" };
		for (Film film : service.getCos())
			f << film.printFilmCVS();
	}

	if (extensie == "html")
	{
		string st = nume_fisier + ".html";
		printFilmeHTML(st);
	}

	cout << "\nCos exportat cu succes!\n";
	cout << "\nNumarul total de filme din cos este: " << service.getCos().size() << "\n\n";
}


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
	cout << "1. Gen\n2. Actor principal\n3. Anul aparitiei\n";
	cout << "Introduceti numarul corespunzator valorii pe care doriti sa o modificati: ";
	cin >> call;
	string titluC, genC, actor_principalC;
	int anul_aparitieiC;
	try {
		switch (call) {
		/*
		case 1: {
			cout << "Introduceti titlul: ";
			cin >> titluC;
			service.updateTitluService(titlu, gen, anul_aparitiei, actor_principal, titluC);
			break;
		}*/
		case 1: {
			cout << "Introduceti genul: ";
			cin >> genC;
			service.updateGenService(titlu, gen, anul_aparitiei, actor_principal, genC);
			break;
		}
		case 2: {
			cout << "Introduceti actorul principal: ";
			cin >> actor_principalC;
			service.updateActorService(titlu, gen, anul_aparitiei, actor_principal, actor_principalC);
			break;
		}
		case 3: {
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
	cout << "\nFilme ce pot fi inchiriate:\n\n";
	vector<Film> filme = service.getAll();
	for (int i=0;i<filme.size();i++)
		cout << filme[i].printFilm() << '\n';
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
		string i = service.searchFilmService(titlu, gen, anul_aparitiei, actor_principal);
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
	for (int i=0;i<rez.size();i++)
		cout << rez[i].printFilm() << '\n';
}

void UI::sorting()
{
	int call;

	cout << "1. Titlu\n2. Gen\n3. Actor principal\n4. Anul aparitiei\n";
	cout << "Introduceti numarul corespunzator valorii dupa care doriti sa sortati: ";
	cin >> call;

	vector<Film> sortate;

	switch (call)
	{
	case 1: {
		sortate = service.sortare([](const Film& s1, const Film& s2) {return s1.getTitlu() <= s2.getTitlu(); });
		break;
	}
	case 2: {
		sortate = service.sortare(([](const Film& s1, const Film& s2) {return s1.getGen() <= s2.getGen(); }));
		break;
	}
	case 3: {
		sortate = service.sortare(([](const Film& s1, const Film& s2) {return s1.getAn() <= s2.getAn(); }));
		break;
	}
	case 4: {
		sortate = service.sortare(([](const Film& s1, const Film& s2) {return s1.getActor() <= s2.getActor(); }));
		break;
	}
	}
	cout << "Filmele sortate sunt:\n";
	for (int i=0;i<sortate.size();i++)
		cout << sortate[i].printFilm() << '\n';
}

void UI::statistica()
{
	int nr;
	vector<DTO> v = this->service.statistica(nr);
	cout << "Statistica: ";
	for (DTO& obj : v)
	{
		cout << "Gen: " << obj.getGen() << " Numar: " << obj.getNrFilme()<<'\n';
	}
	cout << "Suma anilor este: " << nr<<'\n';
}

void UI::undo()
{
	try {
		service.undo();
		cout << "Operatia de undo executata cu succes!\n";
	}
	catch (RepoException ex) {
		cout << ex.getMesaj();
	}
}

void UI::run()
{
	string fileName;
	int comanda = -1;
	while (comanda) {
		cout << "\nMeniu inchiriere filme:\n\n";
		cout << "0. Iesire aplicatie\n1. Adauga film\n2. Sterge film\n3. Modifica film\n4. Afiseaza filme\n5. Cauta film\n6. Filtreaza filme\n7. Sorteaza filme\n8. Statistica\n\n";
		cout << "Inchiriere filme:\n\n";
		cout << "9. Afiseaza filme ce pot fi inchiriate\n";
		cout << "10. Adauga un film in cos\n";
		cout << "11. Goleste cos\n";
		cout << "12. Genereaza cos\n";
		cout << "13. Export\n";
		cout << "14. Afiseaza filme din cos\n";
		cout << "15. Undo\n";
		cout << "\nIntroduceti comanda: ";
		cin >> comanda;
		cout << "\n";
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
		case 8: {
			statistica();
			break;
		}
		case 9: {
			showAll();
			break;
		}
		case 10: {
			adaugaCos();
			break;
		}
		case 11: {
			golesteCos();
			break;
		}
		case 12: {
			genereazaCos();
			break;
		}
		case 13: {
			exportCos();
			break;
		}
		case 14: {
			showCos();
			break;
		}
		case 15: {
			undo();
			break;
		}
		}
	}
}