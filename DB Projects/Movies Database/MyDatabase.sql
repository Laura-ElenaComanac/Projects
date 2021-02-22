CREATE DATABASE Filme
go
use Filme
go


CREATE TABLE Melodii
(
	idMelodie INT PRIMARY KEY,
	numeMelodie VARCHAR(50),
	numeCompozitor VARCHAR(50),
	numeInterpret VARCHAR(50)
);

ALTER TABLE Melodii ADD melodie VARCHAR(100)


CREATE TABLE Genuri
(
	numeGen VARCHAR(50) PRIMARY KEY,
	categorie VARCHAR(50)
);

CREATE TABLE Regizori
(
	idRegizor INT PRIMARY KEY,
	numeRegizor VARCHAR(50),
	dataNasterii DATE,
	bibliografie VARCHAR(50)
);

CREATE TABLE Actori
(
	idActor INT PRIMARY KEY,
	numeActor VARCHAR(50),
	dataNasterii DATE,
	bibliografie VARCHAR(50)
);

CREATE TABLE Roluri
(
	numeRol VARCHAR(50) PRIMARY KEY,
	idActor INT REFERENCES Actori(idActor),
	importanta VARCHAR(50)
);

CREATE TABLE Filme
(
	idFilm INT PRIMARY KEY,
	numeFilm VARCHAR(50),
	dataLansare DATE,
	durata INT,
	popularitate INT CHECK (popularitate>=1 AND popularitate<=10),
	trailer VARCHAR(100)
);

CREATE TABLE Cinema
(
	idCinema INT PRIMARY KEY,
	numeCinema VARCHAR(50),
	tara VARCHAR(50),
	oras VARCHAR(50),
	capacitate INT
);

CREATE TABLE Proiectii
(
	idProiectie INT PRIMARY KEY,
	idFilm INT REFERENCES Filme(idFilm),
	idCinema INT REFERENCES Cinema(idCinema),
	suport3D VARCHAR(2) CHECK(suport3D='DA' OR suport3D='NU'),
	suport4D VARCHAR(2) CHECK(suport4D='DA' OR suport4D='NU'),
	costBilet INT,
	dataProiectie DATE
);

ALTER TABLE Proiectii ALTER COLUMN dataProiectie DATETIME


CREATE TABLE ColoanaSonora
(
	idFilm INT REFERENCES Filme(idFilm),
	idMelodie INT REFERENCES Melodii(idMelodie), 
	PRIMARY KEY (idFilm, idMelodie)
);

CREATE TABLE GenuriFilme
(
	idFilm INT REFERENCES Filme(idFilm),
	numeGen VARCHAR(50) REFERENCES Genuri(numeGen),
	PRIMARY KEY (idFilm, numeGen)
);

CREATE TABLE Distributie
(
	idFilm INT REFERENCES Filme(idFilm),
	idActor INT REFERENCES Actori(idActor),
	idRegizor INT REFERENCES Regizori(idRegizor),
	PRIMARY KEY (idFilm, idActor, idRegizor)
);