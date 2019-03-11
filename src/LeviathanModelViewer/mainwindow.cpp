#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	m_pLevStruct(nullptr)
{
    ui->setupUi(this);
	
	// Register
	connect(ui->actionLoad_Mesh, SIGNAL(triggered(bool)), this, SLOT(LoadFile()));

	m_pLevStruct.reset(new LeviathanInitStruct);
	m_pLevStruct->handle = ui->openGLWidget->winId();
	
	_attachRenderService();
	_runRenderService();
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

void MainWindow::_attachRenderService()
{
}

void MainWindow::_runRenderService()
{
	std::thread renderThread([this]() 
	{
		 _modelViewerPresenter().Init(m_pLevStruct->handle);
		 _modelViewerPresenter().Run();
	});

	renderThread.detach();
}

ModelViewerPresenter & MainWindow::_modelViewerPresenter()
{
	return ModelViewerPresenter::Instance();
}
