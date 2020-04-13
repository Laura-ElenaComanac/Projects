#include "Repository.h"

void Repository::initializeazaRepo()
{
	filme.push_back(Film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" });
	filme.push_back(Film{ "Terminator", "SF", 1984, "ArnoldSchwarzenegger" });
	filme.push_back(Film{ "Bohemian", "drama", 2018, "RamiMalek" });
	filme.push_back(Film{ "Noah", "biblical", 2014, "RusselCrowe" });
	filme.push_back(Film{ "Colonia", "history", 2015, "EmmaWatson" });
	filme.push_back(Film{ "Interstellar", "SF", 2014, "MatthewMcConaughey" });
	filme.push_back(Film{ "Passengers", "romantic", 2016, "JenniferLawrence" });
	filme.push_back(Film{ "Inception", "thriller", 2010, "LeonardoDiCaprio" });
	filme.push_back(Film{ "Oblivion", "action", 2013, "TomCruise" });
	filme.push_back(Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
}

vector<Film> Repository::getCos()
{
	return cos;
}

void Repository::adaugaCos(string titlu)
{
	for (Film film : filme)
		if (film.getTitlu() == titlu)
		{
			cos.push_back(film);
			return;
		}
	throw RepoException("\nFilm inexistent!\n\n");
}

void Repository::golesteCos()
{
	vector<Film> emptyVector;
	cos = emptyVector;
}

void Repository::genereazaCos(int nrFilme)
{
	/*
	char* s;
	const int len=10;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	s[len] = 0;
	*/

	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::shuffle(v.begin(), v.end(), std::default_random_engine(seed)); //amesteca vectorul v

	// random string: str
	auto randchar = []() -> char {
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};

	for (int i = 0; i < nrFilme; i++)
	{
		Film film;
		size_t length = 5;

		// random string: str
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		film.setTitlu(str);
		std::generate_n(str.begin(), length, randchar);
		film.setGen(str);
		std::generate_n(str.begin(), length, randchar);
		film.setActor(str);

		// random number: rndNr
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(1800, 2022);
		int rndNr = dist(mt); // numar aleator intre [0,size-1]
		film.setAn(rndNr);

		cos.push_back(film);
	}

}

int Repository::getPozitie(const Film& film) {
	//iota(begin(filme), end(filme), 0);
	std::vector<Film>::iterator it;
	it = std::find(this->filme.begin(), this->filme.end(), film);
	if(it != this->filme.end())
	{
		return it - this->filme.begin();
	}
	return -1;
}
void Repository::addFilm(const Film& film) {
	//std::vector<Film>::iterator it;
	//it = std::find(this->filme.begin(), this->filme.end(), film);
	if(std::find(filme.begin(), filme.end(), film) != filme.end())
	{
		throw RepoException("Film deja existent!");
		//return;
	}
	filme.push_back(film);
}

void Repository::removeFilm(const Film& film)
{
	std::vector<Film>::iterator it;
	it = std::find(this->filme.begin(), this->filme.end(), film);
	if(it == this->filme.end())
	{
		throw RepoException("Film inexistent!");
	}
	this->filme.erase(it);
}

void Repository::updateTitlu(Film& film, string& titluC)
{
	int i = getPozitie(film);
	if (i != -1)
		this->filme[i].setTitlu(titluC);
}

void Repository::updateGen(Film& film, string genC)
{
	int i = getPozitie(film);
	if (i != -1)
		this->filme[i].setGen(genC);
}

void Repository::updateActor(Film& film, string actorC)
{
	int i = getPozitie(film);
	if (i != -1)
		this->filme[i].setActor(actorC);
}

void Repository::updateAn(Film& film, int anC)
{
	int i = getPozitie(film);
	if (i != -1)
		this->filme[i].setAn(anC);
}

vector<Film>& Repository::getAll() {
	return this->filme;
}

Film& Repository::getFilm(int i)
{
	return this->filme[i];
}

int Repository::getRepoLungime()
{
	return this->filme.size();
}
