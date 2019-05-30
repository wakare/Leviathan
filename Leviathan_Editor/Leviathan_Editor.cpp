#include <QLabel>
#include <QLayout>

#include "Leviathan_Editor.h"

Leviathan_Editor::Leviathan_Editor(QWidget *parent)
	: QMainWindow(parent)
{
	// Actually setup ui do nothing.
	ui.setupUi(this);

	_setupWidget();
}

void Leviathan_Editor::_setupWidget()
{
	// Test label
	QLabel* m_test_label0 = new QLabel;
	QLabel* m_test_label1 = new QLabel;

	m_test_label0->setText(QString("This is label 0."));
	m_test_label1->setText(QString("This is label 1."));

	QLayout* central_layout = new QGridLayout(this);

	// Init main splitter
	m_main_splitter.reset(new LevSpiltter(Qt::Vertical, m_test_label0, m_test_label1, ui.centralWidget));
	
	central_layout->addWidget(m_main_splitter.get());
	ui.centralWidget->setLayout(central_layout);

// 	QVBoxLayout* vbox_layout = new  QVBoxLayout;
// 	m_main_splitter->setLayout(vbox_layout);
// 	setCentralWidget(m_main_splitter.get());
}
