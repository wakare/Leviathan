#include <QFileDialog>
#include <QGridLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qevent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	m_pLevStruct(nullptr)
{
    ui->setupUi(this);
	// Register
	connect(ui->actionLoad_Mesh, SIGNAL(triggered(bool)), this, SLOT(LoadFile()));
	connect(ui->openGLWidget, SIGNAL(resized()), this, SLOT(OpenglWidgetResize()));

	m_updateTimer.setInterval(200);
	connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(Update()));
	m_updateTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadFile()
{
	QString path = QFileDialog::getOpenFileName(this,QString("Select mesh file"), QString("."), QString("Mesh file(*.*)"));
	if (path.length() == 0) return;
	
	_modelViewerPresenter().LoadFile(path.toStdString().c_str());
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
	static bool bFirstEvent = true;
	if (bFirstEvent)
	{
		_initialized();

		m_pLevStruct.reset(new LeviathanInitStruct);
		m_pLevStruct->parentHandle = ui->openGLWidget->winId();
		m_pLevStruct->width = event->size().width();
		m_pLevStruct->height = event->size().height();

		_runRenderService();

		bFirstEvent = false;
	}

	QWidget::resizeEvent(event);
}

void MainWindow::_pushTask(std::function<void()>task)
{
	m_taskLock.lock();
	m_tasks.push_back(task);
	m_taskLock.unlock();
}

void MainWindow::_processTask()
{
	m_taskLock.lock();
	for (auto& task : m_tasks)
	{
		task();
	}
	m_tasks.clear();
	m_taskLock.unlock();
}

void MainWindow::_initialized()
{
	
}
void MainWindow::_runRenderService()
{
	std::thread renderThread([this]() 
	{
		 _modelViewerPresenter().Init(m_pLevStruct->width, m_pLevStruct->height, m_pLevStruct->parentHandle);
		 _modelViewerPresenter().Run();
	});

	renderThread.detach();
}

void MainWindow::OpenglWidgetResize()
{
	auto _task = [this]()
	{
		HWND handle = (HWND)_modelViewerPresenter().GetWindowHandle();
		if (!handle) return;

		int width = ui->openGLWidget->width();
		int height = ui->openGLWidget->height();

		MoveWindow(handle, 0, 0, width, height, true);
	};

	_pushTask(_task);
}

void MainWindow::Update()
{
	if (_modelViewerPresenter().GetCurrentAppState() >= EAS_RUNNING)
	{
		_processTask();
	}
}


ModelViewerPresenter & MainWindow::_modelViewerPresenter()
{
	return ModelViewerPresenter::Instance();
}
