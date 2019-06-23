#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDND.h"

class QtDND : public QMainWindow
{
	Q_OBJECT

public:
	QtDND(QWidget *parent = Q_NULLPTR);

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent *event);

private:
	Ui::QtDNDClass ui;
};
