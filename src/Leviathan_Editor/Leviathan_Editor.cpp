#include "Leviathan_Editor.h"

#include <thread>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QSplitter>
#include <QSizePolicy>

#include "LevScene.h"
#include "LevAttributeWidget.h"

Leviathan_Editor::Leviathan_Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	bool seted = _setupWidget();
	LEV_ASSERT(seted);

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
		return;
	}

	if (_proxy_inited)
	{
		m_runtime_object_view->Update();
	}
}

void Leviathan_Editor::_widget_initialized()
{
	_attachRenderer();
}

void Leviathan_Editor::_leviathan_initialized()
{
	SLOT_RESIZE();

	auto _scene_modified_callback = [this]()
	{
		_update_runtime_scene_object();
	};

	m_leviathan_proxy->UpdateSceneData([this, _scene_modified_callback](Scene::LevScene& scene)
	{
		scene.RegisterModifiedCallback(_scene_modified_callback);
	});
	
	_update_runtime_scene_object();
}

void Leviathan_Editor::_update_runtime_scene_object()
{
	m_leviathan_proxy->UpdateSceneData([this](Scene::LevScene& scene) 
		{
			m_runtime_object_view->SetSceneData(scene.GetSceneData());
		});
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

bool Leviathan_Editor::_setupWidget()
{
	EXIT_IF_FALSE(_setupResourceListView());
	EXIT_IF_FALSE(_setupSceneRuntimeObjectView());
	EXIT_IF_FALSE(_setupAttributePanelView());

	m_openGL_widget.reset(new QOpenGLWidget);
	m_main_splitter.reset(new QSplitter(Qt::Horizontal, ui.centralWidget));
	m_middle_splitter.reset(new QSplitter(Qt::Vertical));
	
	m_middle_splitter->addWidget(m_openGL_widget.data());
	m_middle_splitter->addWidget(m_resource_view.data());
	m_middle_splitter->setStretchFactor(0, 5);
	m_middle_splitter->setStretchFactor(1, 1);

	m_main_splitter->addWidget(m_runtime_object_view.data());
	m_main_splitter->addWidget(m_middle_splitter.data());
	m_main_splitter->addWidget(m_attribute_view.data());
	
	m_main_splitter->setStretchFactor(0, 1);
	m_main_splitter->setStretchFactor(1, 5);
	m_main_splitter->setStretchFactor(2, 1);

	ui.centralWidget->setLayout(new QGridLayout);
	ui.centralWidget->layout()->addWidget(m_main_splitter.data());

	return true;
}

bool Leviathan_Editor::_setupResourceListView()
{
	m_resource_view.reset(new LevResourcesListView);

	// For test
	auto command_args = QApplication::arguments();
	if (command_args.size() > 1)
	{
		auto& resource_folder_path = command_args[1];

		// TODO: the way getting raw char pointer too stupid
		EXIT_IF_FALSE(m_resource_view->SetResourcesFolderPath(resource_folder_path.toStdString().c_str()));
		EXIT_IF_FALSE(m_resource_view->InitItemsFormNode(m_resource_view->GetRootNode()));
	}

	return true;
}

bool Leviathan_Editor::_setupSceneRuntimeObjectView()
{
	m_runtime_object_view.reset(new LevSceneObjectTreeView);
	return true;
}

bool Leviathan_Editor::_setupAttributePanelView()
{
	m_attribute_view.reset(new LevAttributeWidget);
	return true;
}
