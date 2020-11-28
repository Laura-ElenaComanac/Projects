#pragma once
#include "Service.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	~ActiuneUndo() = default;
};

class UndoAdaugaCos :public ActiuneUndo {
	Film film;
	RepositoryMare& repository;
public:
	UndoAdaugaCos(RepositoryMare& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.golesteCos();
	}
};

class UndoAdauga :public ActiuneUndo {
	Film film;
	RepositoryMare& repository;
public:
	UndoAdauga(RepositoryMare& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.removeFilm(film);
	}
};

class UndoSterge :public ActiuneUndo {
	Film film;
	RepositoryMare& repository;
public:
	UndoSterge(RepositoryMare& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.addFilm(film);
	}
};

class UndoModifica :public ActiuneUndo {
	Film film;
	RepositoryMare& repository;
public:
	UndoModifica(RepositoryMare& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.updateAn(film, film.getAn());
		repository.updateActor(film, film.getActor());
		repository.updateGen(film, film.getGen());
	}
};