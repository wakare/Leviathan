#include <QGridLayout>

#include "LevSpiltter.h"

LevSpiltter::LevSpiltter(Qt::Orientation orientation, QWidget* widget0, QWidget* widget1, QWidget *parent /*= Q_NULLPTR*/)
{
	m_spiltter.reset(new QSplitter(orientation, parent));
	setCentralWidget(m_spiltter.get());
	m_spiltter->setBackgroundRole(QPalette::Dark);

	SetSpliterWidget(widget0, widget1);
}

bool LevSpiltter::SetSpliterWidget(QWidget* widget0, QWidget* widget1)
{
	widget0->setParent(m_spiltter.get());
	widget1->setParent(m_spiltter.get());

	return true;
}

void LevSpiltter::_setupWidget()
{
	ui.setupUi(this);
}

