#include "Repository.h"

void Repository::initializeazaRepo()
{
	std::pair<string, Film> film1("Titanic", Film{ "Titanic", "drama", 1997, "LeonardoDiCaprio" });
	//filme.insert(film1);
	this->addFilm(film1.second);
	std::pair<string, Film> film2("Terminator", Film{ "Terminator", "SF", 1984, "ArnoldSchwarzenegger" });
	//filme.insert(film2);
	this->addFilm(film2.second);
	std::pair<string, Film> film3("Bohemian", Film{ "Bohemian", "drama", 2018, "RamiMalek" });
	//filme.insert(film3);
	this->addFilm(film3.second);
	std::pair<string, Film> film4("Noah", Film{ "Noah", "biblical", 2014, "RusselCrowe" });
	//filme.insert(film4);
	this->addFilm(film4.second);
	std::pair<string, Film> film5("Colonia", Film{ "Colonia", "history", 2015, "EmmaWatson" });
	//filme.insert(film5);
	this->addFilm(film5.second);
	std::pair<string, Film> film6("Interstellar", Film{ "Interstellar", "SF", 2014, "MatthewMcConaughey" });
	//filme.insert(film6);
	this->addFilm(film6.second);
	std::pair<string, Film> film7("Passengers", Film{ "Passengers", "romantic", 2016, "JenniferLawrence" });
	//filme.insert(film7);
	this->addFilm(film7.second);
	std::pair<string, Film> film8("Inception", Film{ "Inception", "thriller", 2010, "LeonardoDiCaprio" });
	//filme.insert(film8);
	this->addFilm(film8.second);
	std::pair<string, Film> film9("Oblivion", Film{ "Oblivion", "action", 2013, "TomCruise" });
	//filme.insert(film9);
	this->addFilm(film9.second);
	std::pair<string, Film> film10("Nerve", Film{ "Nerve", "crime", 2016, "EmmaRoberts" });
	//filme.insert(film10);
	this->addFilm(film10.second);
}

vector<Film> Repository::getCos()
{
	return cos;
}

void Repository::adaugaCos(string titlu)
{
	unordered_map<string, Film>::iterator it = filme.begin();
	while (it != filme.end())
	{
		if ((*it).first == titlu)
		{
			cos.push_back((*it).second);
			return;
		}
		it++;
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

string Repository::getPozitie(const Film& film) {
	unordered_map<string, Film>::iterator it;
	it = filme.find(film.getTitlu());
	if (it != filme.end())
	{
		return it->first;
	}
	else
	{
		return "";
	}
}

void Repository::addFilm(const Film& film) {
	//std::vector<Film>::iterator it;
	//it = std::find(this->filme.begin(), this->filme.end(), film);

	unordered_map<string, Film>::iterator it;
	if (getPozitie(film) != "")
	{
		throw RepoException("Film deja existent!");
	}
	//filme.push_back(film);

	std::pair<string, Film> film1(film.getTitlu(), film);
	filme.insert(film1);
}

void Repository::removeFilm(const Film& film)
{
	//std::vector<Film>::iterator it;
	//auto it = std::find(filme.begin(), filme.end(), film);

	if (getPozitie(film) == "")
	{
		throw RepoException("Film inexistent!");
	}
	filme.erase(film.getTitlu());
}
/*
void Repository::updateTitlu(Film& film, string& titluC)
{
	string titlu = film.getTitlu();
	unordered_map<string, Film>::iterator it = getFilm(titlu);
	if (it != filme.end())
		(*it).second.setTitlu(titluC);

}
*/
void Repository::updateGen(Film& film, string genC)
{
	string titlu = film.getTitlu();
	unordered_map<string, Film>::iterator it = getFilm(titlu);
	if (it != filme.end())
		(*it).second.setGen(genC);
}

void Repository::updateActor(Film& film, string actorC)
{
	string titlu = film.getTitlu();
	unordered_map<string, Film>::iterator it = getFilm(titlu);
	if (it != filme.end())
		(*it).second.setActor(actorC);
}

void Repository::updateAn(Film& film, int anC)
{
	/*
	int i = getPozitie(film);
	if (i != -1)
		filme[i].setAn(anC);
	*/
	string titlu = film.getTitlu();
	unordered_map<string, Film>::iterator it = getFilm(titlu);
	if (it != filme.end())
		(*it).second.setAn(anC);
}

vector<Film> Repository::getAll() {
	vector<Film> dest{ filme.size() };
	if (filme.empty() == true)
		return dest;
	transform(filme.begin(), filme.end(), dest.begin(), [](auto it) {return it.second; });
	return dest;
}

unordered_map<string, Film>::iterator Repository::getFilm(string titlu)
{
	unordered_map<string, Film>::iterator it = filme.find(titlu);
	return it;
}

int Repository::getRepoLungime()
{
	return filme.size();
}

///RepositoryFile

void RepositoryFile::loadFromFile()
{
	std::ifstream in(fileName);
	if (!in.is_open()) {
		throw RepoException("Nu exista fisierul " + fileName + "!\n");
	}
	string linie;
	while (getline(in, linie)) {//!in.eof()
		vector<string> v;
		char lin[100];
		strcpy(lin, linie.c_str());
		char* p;
		string s;
		for (p = strtok(lin, ","); p != NULL; p = strtok(NULL, ","))
		{
			s = p;
			v.push_back(s);
		}
		Film film{ v[0],v[1],stoi(v[2]),v[3] };
		std::pair<string, Film> film1(v[0], film);
		filme.insert(film1);
	}
}

void RepositoryFile::writeToFile()
{
	std::ofstream out(fileName);
	for (auto& film : filme)
		out << film.second.printFilmCVS();
}

void RepositoryFile::setFileName(string fileName)
{
	this->fileName = fileName;
}

string RepositoryFile::getFileName()
{
	return fileName;
}
