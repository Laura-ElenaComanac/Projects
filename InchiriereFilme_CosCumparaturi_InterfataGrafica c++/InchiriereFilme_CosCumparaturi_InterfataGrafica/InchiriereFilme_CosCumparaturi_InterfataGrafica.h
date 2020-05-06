#pragma once

#include <QtWidgets/QApplication>
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
#include <qpalette.h>
#include <qbrush.h>

class FilmeGUI : public QWidget
{
private:
	Service& service;
	QListWidget* list = new QListWidget;
	QHBoxLayout* lyMain = new QHBoxLayout{};

	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnSorteaza = new QPushButton{ "&Sorteaza" };
	QPushButton* btnFiltreaza = new QPushButton{ "&Filtreaza" };
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
		lyBtns->addWidget(btnSorteaza);
		lyBtns->addWidget(btnFiltreaza);
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
			//string titlu = film.getTitlu();
			//list->addItem(QString::fromStdString(titlu));

			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film.getTitlu()));
			item->setData(Qt::UserRole,QString::fromStdString(film.getGen()));
			//item->setData(Qt::UserRole, QString::number(film.getAn()));
			//item->setData(Qt::UserRole, QString::fromStdString(film.getActor()));

			//item->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
			item->setTextColor(Qt::blue);
			item->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
			list->addItem(item);
		}
	}
	void initConnect() {
		QObject::connect(list, &QListWidget::itemSelectionChanged, [&](){
			auto sel = list->selectedItems();
			if (sel.isEmpty()) {
				txtTitlu->setText("");
				txtGen->setText("");
				txtAn->setText("");
				txtActor->setText("");
			}
			else{
				auto selItem = sel.at(0);

				// extragem atributele existente ale elementului selectat
				auto titlu = selItem->text();
				auto gen = selItem->data(Qt::UserRole).toString();

				// gasim filmul in lista
				auto film = service.getFilm(titlu.toStdString());

				// setam lineEdit-urile cu atributele filmului
				txtTitlu->setText(titlu);
				txtGen->setText(gen);
				txtAn->setText(QString::number(film.getAn()));
				txtActor->setText(QString::fromStdString(film.getActor()));
			}
			});
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			auto titlu = txtTitlu->text();
			auto gen = txtGen->text();
			auto an = txtAn->text();
			auto actor = txtActor->text();
			try {
				service.addFilmService(titlu.toStdString(), gen.toStdString(), an.toInt(), actor.toStdString());
				QMessageBox::information(nullptr, "Info!", "Film adaugat cu succes!");
			}
			catch (RepoException &ex) {
				QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.getMesaj()));
			}
			loadData();
			});
		QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
			auto titlu = txtTitlu->text();
			auto gen = txtGen->text();
			auto an = txtAn->text();
			auto actor = txtActor->text();
			try {
				service.removeFilmService(titlu.toStdString(), gen.toStdString(), an.toInt(), actor.toStdString());
				QMessageBox::information(nullptr, "Info!", "Film sters cu succes!");
			}
			catch (RepoException& ex){
				QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.getMesaj()));
			}
			loadData();
			});
		QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
			//auto titlu = txtTitlu->text();
			auto gen = txtGen->text();
			auto an = txtAn->text();
			auto actor = txtActor->text();

			auto sel = list->selectedItems();
			auto selItem = sel.at(0);

			// extragem atributele existente ale elementului selectat
			auto titlu = selItem->text();
			//auto gen = selItem->data(Qt::UserRole).toString();

			// gasim filmul in lista
			auto film = service.getFilm(titlu.toStdString());

			service.updateGenService(film.getTitlu(),film.getGen(), film.getAn(), film.getActor(),gen.toStdString());
			service.updateAnService(film.getTitlu(), film.getGen(), film.getAn(), film.getActor(), an.toInt());
			service.updateActorService(film.getTitlu(), film.getGen(), film.getAn(), film.getActor(), actor.toStdString());
			
			// setam lineEdit-urile cu atributele filmului modificat
			txtTitlu->setText(titlu);
			txtGen->setText(QString::fromStdString(film.getGen()));
			txtAn->setText(QString::number(film.getAn()));
			txtActor->setText(QString::fromStdString(film.getActor()));

			loadData();
			QMessageBox::information(nullptr, "Info!", "Film modificat cu succes!");
			});
		QObject::connect(btnSorteaza, &QPushButton::clicked, [&]() {
			auto titlu = txtTitlu->text();

			QVector<Film> sortate;

			sortate = QVector<Film>::fromStdVector(service.sortare([](const Film& s1, const Film& s2) {return s1.getTitlu() <= s2.getTitlu(); }));

			list->clear();
			for (Film film : sortate)
			{
				QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film.getTitlu()));
				item->setData(Qt::UserRole, QString::fromStdString(film.getGen()));
				//item->setData(Qt::UserRole, QString::number(film.getAn()));
				//item->setData(Qt::UserRole, QString::fromStdString(film.getActor()));

				//item->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
				item->setTextColor(Qt::red);
				item->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
				list->addItem(item);
			}
			});
		QObject::connect(btnFiltreaza, &QPushButton::clicked, [&]() {
			auto an = txtAn->text();

			QVector<Film> filtrate;

			filtrate = QVector<Film>::fromStdVector(service.filtrare(an.toInt()));

			list->clear();
			for (Film film : filtrate)
			{
				QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film.getTitlu()));
				item->setData(Qt::UserRole, QString::fromStdString(film.getGen()));
				//item->setData(Qt::UserRole, QString::number(film.getAn()));
				//item->setData(Qt::UserRole, QString::fromStdString(film.getActor()));

				//item->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
				item->setTextColor(Qt::red);
				item->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
				list->addItem(item);
			}
			});
		QObject::connect(btnIesire, &QPushButton::clicked, [&]() {
			//qDebug() << "Buton Iesire apasat!!!";
			//QMessageBox::information(nullptr, "Info!","Ati iesit din aplicatie!");
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
