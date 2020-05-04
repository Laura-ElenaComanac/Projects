/********************************************************************************
** Form generated from reading UI file 'InchiriereFilme_CosCumparaturi_InterfataGrafica.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCHIRIEREFILME_COSCUMPARATURI_INTERFATAGRAFICA_H
#define UI_INCHIRIEREFILME_COSCUMPARATURI_INTERFATAGRAFICA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InchiriereFilme_CosCumparaturi_InterfataGraficaClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InchiriereFilme_CosCumparaturi_InterfataGraficaClass)
    {
        if (InchiriereFilme_CosCumparaturi_InterfataGraficaClass->objectName().isEmpty())
            InchiriereFilme_CosCumparaturi_InterfataGraficaClass->setObjectName(QString::fromUtf8("InchiriereFilme_CosCumparaturi_InterfataGraficaClass"));
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->resize(600, 400);
        menuBar = new QMenuBar(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->setStatusBar(statusBar);

        retranslateUi(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);

        QMetaObject::connectSlotsByName(InchiriereFilme_CosCumparaturi_InterfataGraficaClass);
    } // setupUi

    void retranslateUi(QMainWindow *InchiriereFilme_CosCumparaturi_InterfataGraficaClass)
    {
        InchiriereFilme_CosCumparaturi_InterfataGraficaClass->setWindowTitle(QCoreApplication::translate("InchiriereFilme_CosCumparaturi_InterfataGraficaClass", "InchiriereFilme_CosCumparaturi_InterfataGrafica", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InchiriereFilme_CosCumparaturi_InterfataGraficaClass: public Ui_InchiriereFilme_CosCumparaturi_InterfataGraficaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCHIRIEREFILME_COSCUMPARATURI_INTERFATAGRAFICA_H
