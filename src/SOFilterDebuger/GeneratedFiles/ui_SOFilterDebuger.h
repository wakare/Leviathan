/********************************************************************************
** Form generated from reading UI file 'SOFilterDebuger.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFILTERDEBUGER_H
#define UI_SOFILTERDEBUGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SOFilterDebugerClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QOpenGLWidget *openGLWidget;
    QGroupBox *ControlGroup;
    QPushButton *tickButton;
    QPushButton *RollBackButton;
    QGroupBox *SpeedControlGroup;
    QDoubleSpinBox *speedBox;
    QPushButton *stopButton;
    QPushButton *startButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SOFilterDebugerClass)
    {
        if (SOFilterDebugerClass->objectName().isEmpty())
            SOFilterDebugerClass->setObjectName(QString::fromUtf8("SOFilterDebugerClass"));
        SOFilterDebugerClass->resize(1086, 914);
        centralWidget = new QWidget(SOFilterDebugerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 1, 0, 1, 1);

        ControlGroup = new QGroupBox(centralWidget);
        ControlGroup->setObjectName(QString::fromUtf8("ControlGroup"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(ControlGroup->sizePolicy().hasHeightForWidth());
        ControlGroup->setSizePolicy(sizePolicy);
        ControlGroup->setMinimumSize(QSize(0, 50));
        tickButton = new QPushButton(ControlGroup);
        tickButton->setObjectName(QString::fromUtf8("tickButton"));
        tickButton->setGeometry(QRect(550, 20, 75, 23));
        RollBackButton = new QPushButton(ControlGroup);
        RollBackButton->setObjectName(QString::fromUtf8("RollBackButton"));
        RollBackButton->setGeometry(QRect(630, 20, 75, 23));
        SpeedControlGroup = new QGroupBox(ControlGroup);
        SpeedControlGroup->setObjectName(QString::fromUtf8("SpeedControlGroup"));
        SpeedControlGroup->setGeometry(QRect(880, 10, 181, 41));
        speedBox = new QDoubleSpinBox(SpeedControlGroup);
        speedBox->setObjectName(QString::fromUtf8("speedBox"));
        speedBox->setGeometry(QRect(50, 10, 131, 22));
        speedBox->setValue(1.000000000000000);
        stopButton = new QPushButton(ControlGroup);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(470, 20, 75, 23));
        startButton = new QPushButton(ControlGroup);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(390, 20, 75, 23));

        gridLayout->addWidget(ControlGroup, 0, 0, 1, 1);

        SOFilterDebugerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SOFilterDebugerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1086, 21));
        SOFilterDebugerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SOFilterDebugerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SOFilterDebugerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SOFilterDebugerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SOFilterDebugerClass->setStatusBar(statusBar);

        retranslateUi(SOFilterDebugerClass);

        QMetaObject::connectSlotsByName(SOFilterDebugerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SOFilterDebugerClass)
    {
        SOFilterDebugerClass->setWindowTitle(QApplication::translate("SOFilterDebugerClass", "SOFilterDebuger", nullptr));
        ControlGroup->setTitle(QApplication::translate("SOFilterDebugerClass", "Control", nullptr));
        tickButton->setText(QApplication::translate("SOFilterDebugerClass", "Tick", nullptr));
        RollBackButton->setText(QApplication::translate("SOFilterDebugerClass", "RollBack", nullptr));
        SpeedControlGroup->setTitle(QApplication::translate("SOFilterDebugerClass", "Speed", nullptr));
        stopButton->setText(QApplication::translate("SOFilterDebugerClass", "Stop", nullptr));
        startButton->setText(QApplication::translate("SOFilterDebugerClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SOFilterDebugerClass: public Ui_SOFilterDebugerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFILTERDEBUGER_H
