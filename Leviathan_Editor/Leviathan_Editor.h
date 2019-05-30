#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Leviathan_Editor.h"
#include "LevSpiltter.h"

class Leviathan_Editor : public QMainWindow
{
	Q_OBJECT

public:
	Leviathan_Editor(QWidget *parent = Q_NULLPTR);

private:
	void _setupWidget();

	Ui::Leviathan_EditorClass ui;
	std::unique_ptr<LevSpiltter> m_main_splitter;
};
