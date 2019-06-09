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
	m_items.clear();
	m_standard_model->clear();
}

void LevListView::AddItem(std::unique_ptr<QStandardItem> item)
{
	m_standard_model->appendRow(item.get());
	m_items.push_back(std::move(item));
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


