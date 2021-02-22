#pragma once
#include "Service.h"

class ActiuneUndo {
public:
	virtual void doUndo()=0;
	~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	Film film;
	Repository& repository;
public:
	UndoAdauga(Repository& repository, const Film& film) : repository{ repository }, film{ film }{}
		void doUndo() override {
			repository.removeFilm(film);
		}
};

class UndoSterge :public ActiuneUndo {
	Film film;
	Repository& repository;
public:
	UndoSterge(Repository& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.addFilm(film);
	}
};

class UndoModifica :public ActiuneUndo {
	Film film;
	Repository& repository;
public:
	UndoModifica(Repository& repository, const Film& film) : repository{ repository }, film{ film }{}
	void doUndo() override {
		repository.updateAn(film, film.getAn());
		repository.updateActor(film, film.getActor());
		repository.updateGen(film, film.getGen());
	}
};