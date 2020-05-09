#pragma once

#include "InchiriereFilme_CosCumparaturi_InterfataGrafica.h"
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

	QLabel* label = new QLabel{ "Cos filme:" };

	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QLineEdit* txtActor = new QLineEdit;

	void initGUI() {
		setLayout(lyMain);
		//lyMain->addWidget(list);

		auto firstLy = new QVBoxLayout;
		auto secondLy = new QVBoxLayout;

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
		lyBtns->addWidget(btnIesire);

		secondLy->addLayout(lyBtns);

		lyMain->addLayout(firstLy,0,0);
		lyMain->addLayout(secondLy,0,0);

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
	CosGUI(Service& srv) :srv{ srv }
	{
		initGUI();
		loadData();
		initConnect();
	}
};
