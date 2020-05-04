#include "Teste.h"
#include "Repository.h"
#include "Service.h"

void testExceptii()
{
	RepositoryFile repo{ "Filme.txt",0.7 };
	for (int i = 1; i <= 10; i++)
	{
		try {
			repo.addFilm(Film("s", "a", 1, "a"));
		}
		catch (RepoException& ex)
		{
			cout << ex.getMesaj() << '\n';
		}
		try {
			repo.removeFilm(Film("w", "d", 2016, "q"));
		}
		catch (RepoException& ex)
		{
			cout << ex.getMesaj() << '\n';
		}
	}
}

void testStatistica()
{
	Repository repo;
	Service srv{ repo };
	srv.addFilmService("Titanic", "drama", 1984, "LeonardoDiCaprio");
	srv.addFilmService("Titanic2", "drama", 1997, "LeonardoDiCaprio");
	srv.addFilmService("Terminator", "SF", 1984, "Arnold");

	int nr;
	vector<DTO> v = srv.statistica(nr);

	assert(v[0].getGen() == "SF");
	assert(v[0].getNrFilme() == 1);
	assert(v[1].getGen() == "drama");
	assert(v[1].getNrFilme() == 2);
}

void testService() {
	Repository repo;
	Service srv{ repo };
	assert(srv.getRepoLungime() == 0);
	srv.addFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");
	auto filme1 = srv.getAll();
	assert(filme1.size() == 1);

	//srv.updateTitluService("Titanic", "drama", 1997, "LeonardoDiCaprio", "Terminator");
	//assert(film1.getTitlu() == "Terminator");

	srv.updateGenService("Titanic", "drama", 1997, "LeonardoDiCaprio", "SF");
	assert(srv.getFilm("Titanic").getGen() == "SF");
	srv.updateAnService("Titanic", "SF", 1997, "LeonardoDiCaprio", 1984);
	assert(srv.getFilm("Titanic").getAn() == 1984);
	srv.updateActorService("Titanic", "SF", 1984, "LeonardoDiCaprio", "Arnold");
	assert(srv.getFilm("Titanic").getActor() == "Arnold");

	srv.removeFilmService("Titanic", "SF", 1984, "Arnold");
	auto filme2 = srv.getAll();
	assert(filme2.size() == 0);

	srv.addFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");

	assert(srv.searchFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio") == "Titanic");
	try {
		srv.searchFilmService("Terminator", "SF", 1984, "Arnold");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	srv.addFilmService("Titanic1", "drama2", 1984, "LeonardoDiCaprio");
	srv.addFilmService("Titanic2", "drama3", 1997, "LeonardoDiCaprio");
	srv.addFilmService("Titanic3", "drama5", 1997, "LeonardoDiCaprio");
	//vector<Film> rez {srv.getFilm(0),srv.getFilm(3)};

	assert(srv.filtrare("Titanic", 1997)[0] == srv.getFilm("Titanic"));
	assert(srv.filtrare("Titanic2", 1997)[0] == srv.getFilm("Titanic2"));

	Repository repo2;
	Service srv2{ repo2 };

	srv2.addFilmService("b", "drama2", 1984, "LeonardoDiCaprio");
	srv2.addFilmService("a", "drama3", 1997, "LeonardoDiCaprio");

	vector<Film>  sorted = srv2.sortare([](const Film& s1, const Film& s2) {return s1.getTitlu() <= s2.getTitlu(); });
	assert(sorted[0] == Film("a", "drama3", 1997, "LeonardoDiCaprio"));
	assert(sorted[1] == Film("b", "drama2", 1984, "LeonardoDiCaprio"));


	Repository repo3;
	Service srv3{ repo3 };
	srv3.addFilmService("Nerve", "crime", 2016, "EmmaRoberts");
	srv3.adaugaCos("Nerve");
	vector<Film> cos = srv3.getCos();
	//cout << cos[0].printFilm();
	assert(cos[0] == Film("Nerve", "crime", 2016, "EmmaRoberts"));
	srv3.genereazaCos(3);
	srv3.golesteCos();

	Repository repo4;
	Service srv4{ repo4 };
	assert(srv4.getRepoLungime() == 0);
	srv4.initializare();
	assert(srv4.getRepoLungime() == 10);
	srv4.removeFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");
	srv4.undo();
	assert(srv4.getRepoLungime() == 10);
	srv4.addFilmService("Laura", "SF", 2000, "Elena");
	srv4.undo();
	assert(srv4.getRepoLungime() == 10);
	srv4.updateAnService("Titanic", "drama", 1997, "LeonardoDiCaprio", 2000);
	srv4.undo();
	assert(srv4.getFilm("Titanic").getAn() == 1997);
	try {
		srv4.undo();
		assert(false);
	}
	catch (RepoException ex) {
		assert(true);
	}

	Repository repo5;
	Service srv5{ repo5 };
	srv5.addFilmService("Nerve", "crime", 2016, "EmmaRoberts");
	srv5.adaugaCos("Nerve");
	srv5.undo();
	assert(srv5.getFilm("Nerve").getAn() == 2016);
}

void testRepo() {
	Repository repo;
	RepoException repoEx{ "" };
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	std::pair<string, Film> film1("Titanic", film);

	repo.addFilm(film);

	assert(repo.getPozitie(film) == "Titanic");
	auto filme = repo.getAll();
	//vector<Film> filme = repo.getAll();
	assert(filme.size() == 1);

	try {
		repo.addFilm(film);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(filme.size() == 1);

	repo.removeFilm(film);
	assert(repo.getRepoLungime() == 0);

	try {
		repo.removeFilm(film);
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.getMesaj() == "Film inexistent!");
	}

	assert(repo.getPozitie(film) == "");

	repo.addFilm(film);
	string s = "Titanic";

	//repo.updateTitlu(film, s);
	unordered_map<string, Film>::iterator it = repo.getFilm(s);
	Film film867 = it->second;
	//cout << (*it).second.printFilm();

	//assert(film1.getTitlu() == "Terminator");

	//repo.updateGen(film, "SF");
	//assert(film1.getGen() == "SF");

	//repo.updateAn(film, 1984);
	//assert(film1.getAn() == 1984);

	//repo.updateActor(film, "Arnold");
	//assert(film1.getActor() == "Arnold");


	Repository repo2;
	repo2.addFilm(Film("Nerve", "crime", 2016, "EmmaRoberts"));
	try {
		repo2.adaugaCos("Titanic");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		ex.getMesaj() == "\nFilm inexistent!\n\n";
	}

	RepositoryFile repo3{ "Teste.txt" , 0 };
	repo3.addFilm(Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
	assert(repo3.getRepoLungime() == 1);
	repo3.removeFilm(Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
	assert(repo3.getRepoLungime() == 0);
	repo3.addFilm(Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
	Film film2{ "Nerve", "crime", 2016, "EmmaRoberts" };
	repo3.updateGen(film, "horror");
	repo3.updateGen(film, "crime");
	repo3.updateAn(film, 2000);
	repo3.updateAn(film, 2016);
	repo3.updateActor(film, "Laura");
	repo3.updateActor(film, "EmmaRoberts");
	repo3.removeFilm(Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
	repo3.setFileName("Teste2.txt");
	assert(repo3.getFileName() == "Teste2.txt");

	try {
		RepositoryFile repo4{ "aaa.txt" , 0 };
		assert(false);
	}
	catch (RepoException ex) {
		assert(true);
	}

}

void testFilm()
{
	assert(!(Film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" } == Film{ "Terminator", "drama", 1997, "LeonardoDiCaprio" }));
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	assert(film.getTitlu() == "Titanic");
	assert(film.getGen() == "drama");
	assert(film.getAn() == 1997);
	assert(film.getActor() == "LeonardoDiCaprio");
	film.setTitlu("Terminator");
	assert(film.getTitlu() == "Terminator");
	film.setGen("SF");
	assert(film.getGen() == "SF");
	film.setAn(1984);
	assert(film.getAn() == 1984);
	film.setActor("Arnold");
	assert(film.getActor() == "Arnold");
	string s = film.printFilm();
	//"Titlu: " + this->titlu + "/ Gen: " + this->gen + "/ Actor principal: " + this->actor_principal + "/ Anul aparitiei: " + std::to_string(this->anul_aparitiei) + "\n";
	assert(s == "Titlu: Terminator/ Gen: SF/ Actor principal: Arnold/ Anul aparitiei: 1984\n");

	const string s2 = film.printFilmCVS();
	assert(s2 == "Terminator,SF,1984,Arnold\n");

	string s3 = film.printFilmHTML();
	assert(s3 == "\t\t<tr>\n\t\t\t<td>Terminator</td>\n\t\t\t<td>SF</td>\n\t\t\t<td>Arnold</td>\n\t\t\t<td>1984</td>\n\t\t</tr>\n");
}

/*
void testVectorDinamic()
{
	VectorDinamic<Film> vectorDinamic;
	VectorDinamic<Film> vectorDinamic2;
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	vectorDinamic.addElem(film);
	vectorDinamic2 = vectorDinamic;
	vectorDinamic2 = vectorDinamic2;
	assert(vectorDinamic2.getElem(0) == vectorDinamic.getElem(0));
	Film film2{ "Titanic2", "drama", 1997, "LeonardoDiCaprio" };
	vectorDinamic.addElem(film2);
	assert(vectorDinamic.getLungime() == 2);
	vectorDinamic.deleteElem(0);
	assert(vectorDinamic.getLungime() == 1);
}
*/