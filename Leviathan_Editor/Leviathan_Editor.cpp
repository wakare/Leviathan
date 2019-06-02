#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QSplitter>

#include "Leviathan_Editor.h"
#include "QSizePolicy"
#include "LevAttributeWidget.h"

Leviathan_Editor::Leviathan_Editor(QWidget *parent)
	: QMainWindow(parent)
{
	// Actually setup ui do nothing.
	ui.setupUi(this);

	_setupWidget();
}

void Leviathan_Editor::_setupWidget()
{
	m_openGL_widget.reset(new QOpenGLWidget);
	m_runtime_object_list_view.reset(new LevListView);
	m_resource_list_view.reset(new LevListView);
	m_attribute_view.reset(new LevAttributeWidget);

	m_main_splitter.reset(new QSplitter(Qt::Horizontal, ui.centralWidget));
	m_middle_splitter.reset(new QSplitter(Qt::Vertical));
	
	m_middle_splitter->addWidget(m_openGL_widget.get());
	m_middle_splitter->addWidget(m_resource_list_view.get());
	m_middle_splitter->setStretchFactor(0, 5);
	m_middle_splitter->setStretchFactor(1, 1);

	m_main_splitter->addWidget(m_runtime_object_list_view.get());
	m_main_splitter->addWidget(m_middle_splitter.get());
	m_main_splitter->addWidget(m_attribute_view.get());
	
	m_main_splitter->setStretchFactor(0, 1);
	m_main_splitter->setStretchFactor(1, 5);
	m_main_splitter->setStretchFactor(2, 1);

	ui.centralWidget->setLayout(new QGridLayout);
	ui.centralWidget->layout()->addWidget(m_main_splitter.get());
	//ui.centralWidget->setBackgroundRole(QPalette::Dark);
}
