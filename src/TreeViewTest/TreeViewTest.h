#pragma once

#include <QtWidgets/QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QScopedPointer>
#include "ui_TreeViewTest.h"

class TreeViewTest : public QMainWindow
{
	Q_OBJECT

public:
	TreeViewTest(QWidget *parent = Q_NULLPTR);

private:
	void _setupTreeView();

	Ui::TreeViewTestClass ui;
	QScopedPointer<QStandardItemModel> m_item_model;
	QScopedPointer<QTreeView> m_tree_view;
};
