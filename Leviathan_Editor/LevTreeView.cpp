#include "LevTreeView.h"

#include <QStandardItemModel>
#include <QVBoxLayout>
#include "GlobalDef.h"

LevTreeView::LevTreeView(QWidget * parent)
	: QTreeView(parent)
{
	auto model_inited = _initStandardModel();
	LEV_ASSERT(model_inited);

	auto treeView_inited = _initTreeView();
	LEV_ASSERT(treeView_inited);
}

void LevTreeView::ClearItems()
{
	m_standard_model->clear();
}

void LevTreeView::AddItem(QStandardItem* item)
{
 	m_standard_model->appendRow(item);
}

bool LevTreeView::_initStandardModel()
{
	m_standard_model.reset(new QStandardItemModel);
	return true;
}

bool LevTreeView::_initTreeView()
{
	QVBoxLayout* box_layout = new QVBoxLayout;

	LEV_ASSERT(m_standard_model.data());
	setModel(m_standard_model.data());

	setSelectionMode(QAbstractItemView::ExtendedSelection);

	return true;
}
