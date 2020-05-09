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

class CosGUI : public QWidget
{
protected:
	//RepositoryFile repoFile{ "Cos.txt", 0 };
	//Service& srv{ repoFile };
	Service& srv;
	UI& ui;
	QListWidget* cos = new QListWidget;
	QGridLayout* lyMain = new QGridLayout;

	QPushButton* btnAdauga = new QPushButton{ "&Adauga Cos" };
	QPushButton* btnSterge = new QPushButton{ "&Goleste Cos" };
	QPushButton* btnGenereaza = new QPushButton{ "&Genereaza Cos" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QPushButton* btnIesire = new QPushButton{ "&Iesire" };

	QLabel* label = new QLabel{ "Cos filme:" };

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtActor = new QLineEdit;

	QPushButton* btnExport = new QPushButton{ "&Export Cos" };
	QLineEdit* txtExtensie = new QLineEdit;
	QLineEdit* txtTitluFisier = new QLineEdit;

	void initGUI() {

		setLayout(lyMain);
		//lyMain->addWidget(cos);
		setStyleSheet("QWidget{background-color: black;color:darkturquoise}QPushButton{background-color:darkturquoise;color:black;border-radius:20px;padding:30}QPushButton:hover{background-color:indianred}QLabel{color:darkturquoise}QListWidgetItem{color:darkturquoise}QLineEdit{color:darkturquoise}");

		auto firstLy = new QVBoxLayout;
		auto secondLy = new QVBoxLayout;
		auto thirdLy = new QVBoxLayout;

		firstLy->addWidget(label);
		firstLy->addWidget(cos);

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
		lyBtns->addWidget(btnGenereaza);
		lyBtns->addWidget(btnUndo);

		secondLy->addLayout(lyBtns);

		auto formLy2 = new QFormLayout;
		formLy2->addWidget(btnExport);
		formLy2->addRow("Extensie(cvs/html):",txtExtensie);
		formLy2->addRow("Titlu Fisier:",txtTitluFisier);
		formLy2->addWidget(btnIesire);
		btnIesire->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton));

		thirdLy->addLayout(formLy2);

		lyMain->addLayout(firstLy, 0, 10);
		lyMain->addLayout(secondLy, 0, 20);
		lyMain->addLayout(thirdLy, 0, 30);
	}
	void loadData() {
		// fereastra filme
		cos->clear();
		vector<Film> cosFilme = srv.getCos();

		for (Film film : cosFilme)
		{
			//string titlu = film.getTitlu();
			//list->addItem(QString::fromStdString(titlu));

			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(film.getTitlu()));
			item->setData(Qt::UserRole, QString::fromStdString(film.getGen()));
			//item->setData(Qt::UserRole, QString::number(film.getAn()));
			//item->setData(Qt::UserRole, QString::fromStdString(film.getActor()));

			//item->setBackground(QBrush{ Qt::blue, Qt::SolidPattern });
			//item->setTextColor(Qt::green);
			item->setIcon(QApplication::style()->standardIcon(QStyle::SP_TrashIcon));
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
				auto film = srv.getFilmCos(titlu.toStdString());

				// setam lineEdit-urile cu atributele filmului
				txtTitlu->setText(titlu);
				txtGen->setText(gen);
				txtAn->setText(QString::number(film.getAn()));
				txtActor->setText(QString::fromStdString(film.getActor()));
			}
			});
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			auto titlu = txtTitlu->text();
			try {
				srv.adaugaCos(titlu.toStdString());
				QMessageBox::information(nullptr, "Info!", "Film adaugat cu succes!");
			}
			catch (RepoException& ex) {
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
				srv.golesteCos();
				QMessageBox::information(nullptr, "Info!", "Cos golit cu succes!");
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.getMesaj()));
			}
			loadData();
			});
		QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
			srv.genereazaCos(10);
			loadData();
			});
		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try {
				srv.undo();
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Warning!", QString::fromStdString(ex.getMesaj()));
			}
			loadData();
			});
		QObject::connect(btnExport, &QPushButton::clicked, [&]() {
			auto extensie = txtExtensie->text();
			auto titlu = txtTitluFisier->text();

			if (extensie == "cvs")
			{
				std::ofstream f{ titlu.toStdString() + ".cvs" };
				for (Film film : srv.getCos())
					f << film.printFilmCVS();
			}

			if (extensie == "html")
			{
				string st = titlu.toStdString() + ".html";
				ui.printFilmeHTML(st);
			}
			QMessageBox::information(nullptr, "Info!", "Cos exportat cu succes!");
			loadData();
			});
		QObject::connect(btnIesire, &QPushButton::clicked, [&]() {
			//qDebug() << "Buton Iesire apasat!!!";
			//QMessageBox::information(nullptr, "Info!","Ati iesit din aplicatie!");
			close();
			});
	}
public:
	CosGUI(Service& srv, UI& ui) :srv{ srv }, ui{ui}
	{
		initGUI();
		loadData();
		initConnect();
	}
};
