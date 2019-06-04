#include <thread>
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

	m_timer.reset(new QTimer);
	m_timer->setInterval(100);

	connect(m_openGL_widget.data(), SIGNAL(resized()), this, SLOT(SLOT_RESIZE()));
	connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(SLOT_UPDATE()));

	m_timer->start();
}

void Leviathan_Editor::SLOT_RESIZE()
{
	if (!m_leviathan_proxy || !m_leviathan_proxy->HasInited())
	{
		return;
	}

	unsigned handle = m_leviathan_proxy->GetWindowHandle();

	unsigned width = m_openGL_widget->width();
	unsigned height = m_openGL_widget->height();

	MoveWindow((HWND)handle, 0, 0, width, height, true);
}

void Leviathan_Editor::resizeEvent(QResizeEvent *event)
{
	static bool _first = true;
	
	if (_first)
	{
		_widget_initialized();
		_first = false;
	}
}

void Leviathan_Editor::closeEvent(QCloseEvent * event)
{
	m_leviathan_proxy->Stop();

	while (!m_leviathan_proxy->HasStoped())
	{
		Sleep(100);
	}

	QMainWindow::closeEvent(event);
}

void Leviathan_Editor::SLOT_UPDATE()
{
	static bool _proxy_inited = false;

	if (!_proxy_inited && m_leviathan_proxy && m_leviathan_proxy->HasInited())
	{
		_leviathan_initialized();
		_proxy_inited = true;
	}
}

void Leviathan_Editor::_widget_initialized()
{
	_attachRenderer();
}

void Leviathan_Editor::_leviathan_initialized()
{
	SLOT_RESIZE();
}

void Leviathan_Editor::_attachRenderer()
{
	unsigned width = m_openGL_widget->width();
	unsigned height = m_openGL_widget->height();
	unsigned handle = m_openGL_widget->winId();

	std::thread _lev_render_thread([this, width, height, handle]() 
		{
			m_leviathan_proxy.Reset(new LeviathanProxy);
			m_leviathan_proxy->Init(width, height, handle);

			while (!m_leviathan_proxy->HasStoped())
			{
				m_leviathan_proxy->Update();
			}

			LogLine("[DEBUG] Exit leviathan proxy.");
		});
	_lev_render_thread.detach();
}

void Leviathan_Editor::_setupWidget()
{
	m_openGL_widget.reset(new QOpenGLWidget);
	m_runtime_object_list_view.reset(new LevListView);
	m_resource_list_view.reset(new LevListView);
	m_attribute_view.reset(new LevAttributeWidget);

	m_main_splitter.reset(new QSplitter(Qt::Horizontal, ui.centralWidget));
	m_middle_splitter.reset(new QSplitter(Qt::Vertical));
	
	m_middle_splitter->addWidget(m_openGL_widget.data());
	m_middle_splitter->addWidget(m_resource_list_view.data());
	m_middle_splitter->setStretchFactor(0, 5);
	m_middle_splitter->setStretchFactor(1, 1);

	m_main_splitter->addWidget(m_runtime_object_list_view.data());
	m_main_splitter->addWidget(m_middle_splitter.data());
	m_main_splitter->addWidget(m_attribute_view.data());
	
	m_main_splitter->setStretchFactor(0, 1);
	m_main_splitter->setStretchFactor(1, 5);
	m_main_splitter->setStretchFactor(2, 1);

	ui.centralWidget->setLayout(new QGridLayout);
	ui.centralWidget->layout()->addWidget(m_main_splitter.data());
}
