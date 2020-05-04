#pragma once

#include "Service.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>

class FilmeGUI : public QWidget
{
private:
	Service& service;
	QListWidget* list = new QListWidget;
	QHBoxLayout* lyMain = new QHBoxLayout{};
	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnIesire = new QPushButton{ "&Iesire" };
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtActor = new QLineEdit;

	void initGUI() {

		setLayout(lyMain);
		lyMain->addWidget(list);

		auto stgLy = new QVBoxLayout;

		// descriere film
		auto formLy = new QFormLayout;
		formLy->addRow("Titlu", txtTitlu);
		formLy->addRow("Gen", txtGen);
		formLy->addRow("Anul aparitiei", txtAn);
		formLy->addRow("Actor principal", txtActor);
		stgLy->addLayout(formLy);

		// lista butoane
		auto lyBtns = new QHBoxLayout;

		lyBtns->addWidget(btnAdauga);
		lyBtns->addWidget(btnSterge);
		lyBtns->addWidget(btnModifica);
		lyBtns->addWidget(btnIesire);

		stgLy->addLayout(lyBtns);

		lyMain->addLayout(stgLy);
	}
	void loadData() {
		// fereastra filme
		list->clear();
		vector<Film> filme = service.getAll();
		
		for (Film film : filme)
		{
			string titlu = film.getTitlu();
			list->addItem(QString::fromStdString(titlu));
		}
		//list->addItem(new QListWidgetItem{ "a" });
	}
	void initConnect() {
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			QMessageBox::information(nullptr, "Info!", "Film adaugat cu succes!");
			auto titlu = txtTitlu->text();
			auto gen = txtGen->text();
			auto an = txtAn->text();
			auto actor = txtActor->text();
			service.addFilmService(titlu.toStdString(), gen.toStdString(), an.toInt(), actor.toStdString());
			loadData();
			});
		QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
			QMessageBox::information(nullptr, "Info!", "Ati apasat butonul Sterge!");
			});
		QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
			QMessageBox::information(nullptr, "Info!", "Ati apasat butonul Modifica!");
			});
		QObject::connect(btnIesire, &QPushButton::clicked, [&]() {
			//qDebug() << "Buton Iesire apasat!!!";
			QMessageBox::information(nullptr, "Info!","Ati apasat butonul Iesire!");
			close();
			});
	}
public:
	FilmeGUI(Service& service) :service{ service }
	{
		initGUI();
		loadData();
		initConnect();
	}
};
