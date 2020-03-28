/********************************************************************************
** Form generated from reading UI file 'TreeViewTest.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEVIEWTEST_H
#define UI_TREEVIEWTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TreeViewTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TreeViewTestClass)
    {
        if (TreeViewTestClass->objectName().isEmpty())
            TreeViewTestClass->setObjectName(QStringLiteral("TreeViewTestClass"));
        TreeViewTestClass->resize(600, 400);
        menuBar = new QMenuBar(TreeViewTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TreeViewTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TreeViewTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TreeViewTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TreeViewTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TreeViewTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TreeViewTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TreeViewTestClass->setStatusBar(statusBar);

        retranslateUi(TreeViewTestClass);

        QMetaObject::connectSlotsByName(TreeViewTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TreeViewTestClass)
    {
        TreeViewTestClass->setWindowTitle(QApplication::translate("TreeViewTestClass", "TreeViewTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TreeViewTestClass: public Ui_TreeViewTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEVIEWTEST_H
