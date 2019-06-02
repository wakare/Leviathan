#include "GlobalDef.h"
#include <LevListView.h>
#include <QBoxLayout>

LevListView::LevListView(QWidget * parent)
	: QListView(parent)
{
	auto model_inited = _initStandardModel();
	LEV_ASSERT(model_inited);

	auto listView_inited = _initListView();
	LEV_ASSERT(listView_inited);

	// Test add item
	QStandardItem* item0 = new QStandardItem;
	item0->setText(QString("Item"));
	m_standard_model->appendRow(item0);

	QStandardItem* item1 = new QStandardItem;
	item1->setText(QString("Item"));
	m_standard_model->appendRow(item1);
}

bool LevListView::_initStandardModel()
{
	m_standard_model.reset(new QStandardItemModel);
	return true;
}

bool LevListView::_initListView()
{
	QVBoxLayout* box_layout = new QVBoxLayout;

	LEV_ASSERT(m_standard_model.get());
	setModel(m_standard_model.get());

	setSelectionRectVisible(true);
	setSelectionMode(QAbstractItemView::ExtendedSelection);

	return true;
}


