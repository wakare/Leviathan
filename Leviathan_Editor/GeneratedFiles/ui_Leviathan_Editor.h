/********************************************************************************
** Form generated from reading UI file 'Leviathan_Editor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVIATHAN_EDITOR_H
#define UI_LEVIATHAN_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Leviathan_EditorClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuWindow;
    QMenu *menuTool;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Leviathan_EditorClass)
    {
        if (Leviathan_EditorClass->objectName().isEmpty())
            Leviathan_EditorClass->setObjectName(QStringLiteral("Leviathan_EditorClass"));
        Leviathan_EditorClass->resize(1066, 839);
        centralWidget = new QWidget(Leviathan_EditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Leviathan_EditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Leviathan_EditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1066, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        Leviathan_EditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Leviathan_EditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Leviathan_EditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Leviathan_EditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Leviathan_EditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(Leviathan_EditorClass);

        QMetaObject::connectSlotsByName(Leviathan_EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *Leviathan_EditorClass)
    {
        Leviathan_EditorClass->setWindowTitle(QApplication::translate("Leviathan_EditorClass", "Leviathan_Editor", nullptr));
        menuFile->setTitle(QApplication::translate("Leviathan_EditorClass", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("Leviathan_EditorClass", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("Leviathan_EditorClass", "View", nullptr));
        menuWindow->setTitle(QApplication::translate("Leviathan_EditorClass", "Window", nullptr));
        menuTool->setTitle(QApplication::translate("Leviathan_EditorClass", "Tool", nullptr));
        menuHelp->setTitle(QApplication::translate("Leviathan_EditorClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Leviathan_EditorClass: public Ui_Leviathan_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVIATHAN_EDITOR_H
