#pragma once

#include <QtWidgets/QApplication>
#include "Service.h"
#include "UI.h"
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
#include <QGroupBox> 
#include "CosGUI.h"

class FilmeGUI : public QWidget
{
private:
	//friend class CosGui;
	Service& service;
	UI& ui;
	QListWidget* list = new QListWidget;
	QGridLayout* lyMain = new QGridLayout{};

	//QGroupBox* box = new QGroupBox{"Cos"};

	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnSorteaza = new QPushButton{ "&Sorteaza" };
	QPushButton* btnFiltreaza = new QPushButton{ "&Filtreaza" };
	QPushButton* btnCauta = new QPushButton{ "&Cauta" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QPushButton* btnStatistica = new QPushButton{ "&Statistica" };
	QPushButton* btnFereastra = new QPushButton{ "&Cos" };
	QPushButton* btnIesire = new QPushButton{ "&Iesire" };

	QLabel* label = new QLabel{"Inchiriere filme:"};
	QLabel* labelStat = new QLabel{ "Statisitica:" };

	//QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtTitlu = new QLineEdit();
	QLineEdit* txtGen = new QLineEdit;
	QSpinBox* txtAn = new QSpinBox();
	QLineEdit* txtActor = new QLineEdit;

	QLineEdit* txtGenStat = new QLineEdit;
	QLineEdit* txtNumarStat = new QLineEdit;

	void initGUI() {
		setLayout(lyMain);
		setStyleSheet("QWidget{background-color: black;color:palevioletred}QPushButton{background-color:palevioletred;color:black;border-radius:20px;padding:30}QPushButton:hover{background-color:indianred}QLabel{color:palevioletred}QListWidgetItem{color:palevioletred}QLineEdit{color:palevioletred}");

		//lyMain->addLayout(lyMainCos, 0, 20);

		auto firstLy = new QVBoxLayout;
		auto secondLy = new QVBoxLayout;
		auto thirdLy = new QVBoxLayout;

		firstLy->addWidget(label);
		firstLy->addWidget(list);

		auto fLy = new QHBoxLayout;
		fLy->addWidget(btnFiltreaza);
		fLy->addWidget(btnSorteaza);
		firstLy->addLayout(fLy);

		// descriere film
		auto formLy = new QFormLayout;
		formLy->addRow("Titlu", txtTitlu);
		formLy->addRow("Gen", txtGen);
		formLy->addRow("Anul aparitiei", txtAn);
		formLy->addRow("Actor principal", txtActor);
		secondLy->addLayout(formLy);

		// lista butoane
		auto lyBtns = new QHBoxLayout;

		lyBtns->addWidget(btnAdauga);
		lyBtns->addWidget(btnSterge);
		lyBtns->addWidget(btnModifica);

		secondLy->addLayout(lyBtns);

		auto lyBtns3 = new QHBoxLayout;
		lyBtns3->addWidget(btnCauta);
		lyBtns3->addWidget(btnUndo);
		btnFereastra->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation));

		secondLy->addLayout(lyBtns3);


		auto statLy = new QFormLayout;

		//statLy->addWidget(labelStat);
		statLy->addWidget(btnStatistica);
		statLy->addRow("Gen:", txtGenStat);
		statLy->addRow("Numar:", txtNumarStat);
		statLy->addWidget(btnFereastra);
		btnIesire->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton));
		statLy->addWidget(btnIesire);

		thirdLy->addLayout(statLy);

		lyMain->addLayout(firstLy,0,10);
		lyMain->addLayout(secondLy,0,20);
		lyMain->addLayout(thirdLy, 0, 30);
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
			//item->setTextColor(Qt::lightcoral);
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
		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try {
				service.undo();
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.getMesaj()));
			}
			loadData();
			});
		QObject::connect(btnStatistica, &QPushButton::clicked, [&]() {
			auto gen = txtGenStat->text();
			int nr,test=0;
			vector<DTO> v = service.statistica(nr);
			for (DTO& obj : v)
			{
				if (obj.getGen() == gen.toStdString())
				{
					txtNumarStat->setText(QString::number(obj.getNrFilme()));
					test = 1;
				}
			}
			if (!test)
				txtNumarStat->setText("");
			loadData();
			});
		QObject::connect(btnFereastra, &QPushButton::clicked, [&]() {
			//auto fereastra = new QWidget;
			//fereastra->show();
			//RepositoryFile repoFile{ "Filme.txt", 0 };
			//Service srv{ repoFile };
			auto guiCos = new CosGUI{service,ui};
			guiCos->show();
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
	FilmeGUI(Service& service, UI& ui) :service{ service }, ui{ui}
	{
		initGUI();
		loadData();
		initConnect();
	}
};
