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
#include <QSpinBox>
#include <QGridLayout> 

class CosGUI : public QWidget
{
protected:
	//RepositoryFile repoFile{ "Cos.txt", 0 };
	//Service& srv{ repoFile };
	Service& srv;
	QListWidget* cos = new QListWidget;
	QGridLayout* lyMain = new QGridLayout;

	QPushButton* btnAdauga = new QPushButton{ "&Adauga Cos" };
	QPushButton* btnSterge = new QPushButton{ "&Goleste Cos" };
	QPushButton* btnGenereaza = new QPushButton{ "&Genereaza Cos" };
	QPushButton* btnIesire = new QPushButton{ "&Iesire" };

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtActor = new QLineEdit;

	void initGUI() {

		setLayout(lyMain);
		lyMain->addWidget(cos);

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
		lyBtns->addWidget(btnGenereaza);
		lyBtns->addWidget(btnIesire);

		stgLy->addLayout(lyBtns);

		lyMain->addLayout(stgLy,0,0);
	}
	void loadData() {
		// fereastra filme
		cos->clear();
		vector<Film> filme = srv.getCos();

		for (Film film : filme)
		{
			//string titlu = film.getTitlu();
			//list->addItem(QString::fromStdString(titlu));

			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film.getTitlu()));
			item->setData(Qt::UserRole, QString::fromStdString(film.getGen()));
			//item->setData(Qt::UserRole, QString::number(film.getAn()));
			//item->setData(Qt::UserRole, QString::fromStdString(film.getActor()));

			//item->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
			item->setTextColor(Qt::green);
			item->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
			cos->addItem(item);
		}
	}
	void initConnect() {
		QObject::connect(cos, &QListWidget::itemSelectionChanged, [&]() {
			auto sel = cos->selectedItems();
			if (sel.isEmpty()) {
				txtTitlu->setText("");
				txtGen->setText("");
				txtAn->setText("");
				txtActor->setText("");
			}
			else {
				auto selItem = sel.at(0);

				// extragem atributele existente ale elementului selectat
				auto titlu = selItem->text();
				auto gen = selItem->data(Qt::UserRole).toString();

				// gasim filmul in lista
				auto film = srv.getFilm(titlu.toStdString());

				// setam lineEdit-urile cu atributele filmului
				txtTitlu->setText(titlu);
				txtGen->setText(gen);
				txtAn->setText(QString::number(film.getAn()));
				txtActor->setText(QString::fromStdString(film.getActor()));
			}
			});
	}
public:
	CosGUI(Service & srv) :srv{ srv }
	{
		initGUI();
		loadData();
		initConnect();
	}
};

class FilmeGUI : public QWidget
{
private:
	friend class cosGui;
	Service& service;
	QListWidget* list = new QListWidget;
	QHBoxLayout* lyMain = new QHBoxLayout{};

	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnSorteaza = new QPushButton{ "&Sorteaza" };
	QPushButton* btnFiltreaza = new QPushButton{ "&Filtreaza" };
	QPushButton* btnCauta = new QPushButton{ "&Cauta" };
	QPushButton* btnFereastra = new QPushButton{ "&Fereastra" };
	QPushButton* btnIesire = new QPushButton{ "&Iesire" };

	//QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtTitlu = new QLineEdit();
	QLineEdit* txtGen = new QLineEdit;
	QSpinBox* txtAn = new QSpinBox();
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
		lyBtns->addWidget(btnCauta);

		stgLy->addLayout(lyBtns);

		auto lyBtns2 = new QHBoxLayout;
		lyBtns2->addWidget(btnFiltreaza);
		lyBtns2->addWidget(btnSorteaza);
		lyBtns2->addWidget(btnFereastra);
		lyBtns2->addWidget(btnIesire);

		stgLy->addLayout(lyBtns2);

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
				txtAn->setValue(1888);
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
				txtAn->setValue(film.getAn());
				txtActor->setText(QString::fromStdString(film.getActor()));
			}
			});
		QObject::connect(btnFereastra, &QPushButton::clicked, [&]() {
			auto fereastra = new QWidget;
			//CosGUI guiCos{ srv };
			//guiCos.show();
			fereastra->show();
			});
		QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
			auto titlu = txtTitlu->text();
			Film film = service.getFilm(titlu.toStdString());
			txtTitlu->setText(QString::fromStdString(film.getTitlu()));
			txtGen->setText(QString::fromStdString(film.getGen()));
			txtAn->setValue(film.getAn());
			txtActor->setText(QString::fromStdString(film.getActor()));
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
			if (sel.isEmpty()) {
				QMessageBox::warning(this, "Warning!", "Alegeti filmul pe care doriti sa il modificati!");
				return;
			}
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
			txtAn->setValue(film.getAn());
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
