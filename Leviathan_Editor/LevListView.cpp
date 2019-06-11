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
}

void LevListView::ClearItems()
{
	m_standard_model->removeRows(0, m_standard_model->rowCount());
}

void LevListView::AddItem(QStandardItem* item)
{
	m_standard_model->appendRow(item);
}

bool LevListView::_initStandardModel()
{
	m_standard_model.reset(new QStandardItemModel);
	return true;
}

bool LevListView::_initListView()
{
	QVBoxLayout* box_layout = new QVBoxLayout;

	LEV_ASSERT(m_standard_model.data());
	setModel(m_standard_model.data());

	setSelectionRectVisible(true);
	setSelectionMode(QAbstractItemView::ExtendedSelection);

	return true;
}


