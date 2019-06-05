#include "TreeViewTest.h"
#include <QGridLayout>

TreeViewTest::TreeViewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_setupTreeView();
}

void TreeViewTest::_setupTreeView()
{
	setLayout(new QGridLayout);

	m_item_model.reset(new QStandardItemModel);
	m_item_model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("Project Name") << QStringLiteral("Information"));

	m_tree_view.reset(new QTreeView);
	m_tree_view->setModel(m_item_model.data());
	
	layout()->addWidget(m_tree_view.data());

	QStandardItem* item = new QStandardItem;
	item->setText(QString("StandardItem0"));

	QStandardItem* item_subItem = new QStandardItem;
	item_subItem->setText(QString("Project Name: S0"));

	QStandardItem* sub_item = new QStandardItem;
	sub_item->setText(QString("ChildStandardItem0"));

	QStandardItem* sub_item_subItem = new QStandardItem;
	sub_item_subItem->setText(QString("SubItem Project Name: S1"));

	item->appendRow(sub_item);
	m_item_model->appendRow(item);
	m_item_model->setItem(m_item_model->indexFromItem(item).row(), 1, item_subItem);
	m_item_model->setItem(m_item_model->indexFromItem(sub_item).row(), 1, sub_item_subItem);
}
