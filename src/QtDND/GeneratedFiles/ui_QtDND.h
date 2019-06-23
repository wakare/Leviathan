/********************************************************************************
** Form generated from reading UI file 'QtDND.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDND_H
#define UI_QTDND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDNDClass
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtDNDClass)
    {
        if (QtDNDClass->objectName().isEmpty())
            QtDNDClass->setObjectName(QString::fromUtf8("QtDNDClass"));
        QtDNDClass->resize(879, 961);
        centralWidget = new QWidget(QtDNDClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(90, 120, 691, 681));
        QtDNDClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtDNDClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 879, 21));
        QtDNDClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtDNDClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtDNDClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtDNDClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtDNDClass->setStatusBar(statusBar);

        retranslateUi(QtDNDClass);

        QMetaObject::connectSlotsByName(QtDNDClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtDNDClass)
    {
        QtDNDClass->setWindowTitle(QApplication::translate("QtDNDClass", "QtDND", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDNDClass: public Ui_QtDNDClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDND_H
