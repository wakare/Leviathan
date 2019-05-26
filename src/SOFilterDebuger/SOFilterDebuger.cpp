#include "SOFilterDebuger.h"

SOFilterDebuger::SOFilterDebuger(QWidget *parent)
	: QMainWindow(parent)
	, m_main_module_inited(false)
	, m_update_timer(new QTimer)
	, m_main_module(new MainModule)
{
	ui.setupUi(this);

	connect(m_update_timer.get(), SIGNAL(timeout()), this, SLOT(slot_update()));
	connect(ui.openGLWidget, SIGNAL(resized()), this, SLOT(slot_resize()));
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(slot_start()));
	connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(slot_stop()));
	connect(ui.tickButton, SIGNAL(clicked()), this, SLOT(slot_tick()));
	connect(ui.RollBackButton, SIGNAL(clicked()), this, SLOT(slot_rollback()));
	m_update_timer->start(50);
}

bool SOFilterDebuger::_runMainModuleThread()
{
	/*
		Arguments:
			0. Data_folder
			1. Data_file_format
			2. start_index
			3. end_index
	*/

	QStringList arguments = QCoreApplication::arguments();
	EXIT_IF_FALSE(arguments.size() >= 5);

	MainModuleParameters parameter;
	parameter.window_handle = ui.openGLWidget->winId();
	parameter.window_width = ui.openGLWidget->width();
	parameter.window_height = ui.openGLWidget->height();
	parameter.data_folder = arguments[1].toStdString();
	parameter.data_file_format = arguments[2].toStdString();
	parameter.data_start_index = arguments[3].toInt();
	parameter.data_end_index = arguments[4].toInt();

	m_main_module_thread = std::thread([this, parameter]() 
		{
			_initMainModule(parameter); 
			m_main_module_inited = true; 

			while (true)
			{
				m_main_module->Update();
			}
		});
	m_main_module_thread.detach();

	return true;
}

bool SOFilterDebuger::_initMainModule(const MainModuleParameters& parameter)
{
	// Init main logic module
	m_main_module.reset(new MainModule());
	return m_main_module->SetupConfig(parameter);
}

void SOFilterDebuger::slot_rollback()
{

}

void SOFilterDebuger::slot_tick()
{

}

void SOFilterDebuger::slot_stop()
{
}

void SOFilterDebuger::slot_start()
{
}

void SOFilterDebuger::slot_update()
{
	static bool _first = true;
	if (_first)
	{
		_runMainModuleThread();
		_first = false;
	}

	m_main_module->SetNeedUpdate();
}

void SOFilterDebuger::slot_resize()
{
// 	if (!m_main_module_inited)
// 	{
// 		return;
// 	}
// 
// 	HWND handle = (HWND)LevRuntimeInterface::GetRuntimeData().windowHandle;
// 	if (!handle) return;
// 
// 	int width = ui.openGLWidget->width();
// 	int height = ui.openGLWidget->height();
// 
// 	MoveWindow(handle, 0, 0, width, height, true);
}
