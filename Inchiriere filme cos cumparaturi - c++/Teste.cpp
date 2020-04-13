#include "Teste.h"
#include "Repository.h"
#include "Service.h"

void testStatistica()
{
	Repository repo;
	Service srv{ repo };
	srv.addFilmService("Titanic", "drama", 1984, "LeonardoDiCaprio");
	srv.addFilmService("Titanic2", "drama", 1997, "LeonardoDiCaprio");
	srv.addFilmService("Terminator", "SF", 1984, "Arnold");

	vector<DTO> v = srv.statistica();

	assert(v[0].getGen() == "SF");
	assert(v[0].getNrFilme() == 1);
	assert(v[1].getGen() == "drama");
	assert(v[1].getNrFilme() == 2);
}

void testService() {
	Repository repo;
	Service srv{ repo };
	srv.addFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");
	auto& filme1 = srv.getAll();
	assert(filme1.size() == 1);

	srv.updateTitluService("Titanic", "drama", 1997, "LeonardoDiCaprio", "Terminator");
	assert(srv.getFilm(0).getTitlu() == "Terminator");
	srv.updateGenService("Terminator", "drama", 1997, "LeonardoDiCaprio", "SF");
	assert(srv.getFilm(0).getGen() == "SF");
	srv.updateAnService("Terminator", "SF", 1997, "LeonardoDiCaprio", 1984);
	assert(srv.getFilm(0).getAn() == 1984);
	srv.updateActorService("Terminator", "SF", 1984, "LeonardoDiCaprio", "Arnold");
	assert(srv.getFilm(0).getActor() == "Arnold");
	
	srv.removeFilmService("Terminator", "SF", 1984, "Arnold");
	auto& filme2 = srv.getAll();
	assert(filme2.size() == 0);

	srv.addFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio");

	assert(srv.searchFilmService("Titanic", "drama", 1997, "LeonardoDiCaprio") == 0);
	try {
		srv.searchFilmService("Terminator", "SF", 1984, "Arnold");
		assert(false);
	}
	catch(RepoException&){
		assert(true);
	}

	srv.addFilmService("Titanic", "drama2", 1984, "LeonardoDiCaprio");
	srv.addFilmService("Titanic2", "drama3", 1997, "LeonardoDiCaprio");
	srv.addFilmService("Titanic", "drama5", 1997, "LeonardoDiCaprio");
	//vector<Film> rez {srv.getFilm(0),srv.getFilm(3)};

	assert(srv.filtrare("Titanic", 1997)[0]==srv.getFilm(0));
	assert(srv.filtrare("Titanic", 1997)[1] == srv.getFilm(3));

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
}

void testRepo() {
	Repository repo;
	RepoException repoEx{""};
	Film film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" };
	repo.addFilm(film);
	assert(repo.getPozitie(film) == 0);
	//const auto& filme = repo.getAll();
	vector<Film>& filme = repo.getAll();
	assert(filme.size() == 1);

	try {
		repo.addFilm(film);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	repo.removeFilm(film);
	assert(filme.size() == 0);

	try {
		repo.removeFilm(film);
		assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.getMesaj() == "Film inexistent!");
	}

	assert(repo.getPozitie(film) == -1);

	repo.addFilm(film);
	string s= "Terminator";
	repo.updateTitlu(film, s);
	assert(repo.getFilm(0).getTitlu() == "Terminator");
	repo.updateGen(repo.getFilm(0), "SF");
	assert(repo.getFilm(0).getGen() == "SF");
	repo.updateAn(repo.getFilm(0), 1984);
	assert(repo.getFilm(0).getAn() == 1984);
	repo.updateActor(repo.getFilm(0), "Arnold");
	assert(repo.getFilm(0).getActor() == "Arnold");

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

}

void testFilm()
{
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
	assert(s2 == "Terminator,SF,Arnold,1984\n");

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