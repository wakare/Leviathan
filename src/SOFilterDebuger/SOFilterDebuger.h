#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <memory>
#include "ui_SOFilterDebuger.h"
#include "MainModule.h"

using namespace SOFilter;

class SOFilterDebuger : public QMainWindow
{
	Q_OBJECT

public slots:
	void slot_rollback();
	void slot_tick();
	void slot_stop();
	void slot_start();
	void slot_update();
	void slot_resize();

public:
	SOFilterDebuger(QWidget *parent = Q_NULLPTR);

private:
	bool _runMainModuleThread();
	bool _initMainModule(const MainModuleParameters& parameter);

	Ui::SOFilterDebugerClass ui;

	volatile bool m_main_module_inited;
	std::thread m_main_module_thread;
	std::shared_ptr<MainModule> m_main_module;

	std::unique_ptr<QTimer> m_update_timer;
};
