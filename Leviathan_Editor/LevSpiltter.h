#pragma once

#include <QtWidgets/QMainWindow>
#include <QSplitter>
#include <memory>
#include "ui_LevSpliter.h"

class LevSpiltter : public QMainWindow
{
	Q_OBJECT

public:
	LevSpiltter(Qt::Orientation orientation, QWidget* widget0, QWidget* widget1, QWidget *parent = Q_NULLPTR);
	bool SetSpliterWidget(QWidget* widget0, QWidget* widget1);

private:
	void _setupWidget();

	Ui::LevSplitterCLass ui;
	std::unique_ptr<QSplitter> m_spiltter;
};
