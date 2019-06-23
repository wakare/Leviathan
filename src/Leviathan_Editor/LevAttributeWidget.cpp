#include "LevAttributeWidget.h"
#include <QLabel>
#include <QVBoxLayout>

LevAttributeWidget::LevAttributeWidget(QWidget* parent)
	: QGroupBox(QString("Attribute Panel"), parent)
{
	_setupAttributeView();
}

void LevAttributeWidget::SetViewSize(unsigned width, unsigned height)
{
	QSize size = sizeHint();
	size.setWidth(width);
	size.setHeight(height);
	setBaseSize(size);
}

void LevAttributeWidget::_setupAttributeView()
{
	setLayout(new QHBoxLayout);

	QLabel* label = new QLabel;
	label->setText(QString("Attribute panel show current select object attributes"));
	label->setMaximumSize(QSize(200, 50));

	layout()->addWidget(label);
}
