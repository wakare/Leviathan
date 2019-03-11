#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	_attachRenderService();
	_runRenderService();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_attachRenderService()
{
	_modelViewerPresenter().Init(ui->openGLWidget->winId());
}

void MainWindow::_runRenderService()
{
	std::thread renderThread([this]() {_modelViewerPresenter().Run(); });
	renderThread.detach();
}

ModelViewerPresenter & MainWindow::_modelViewerPresenter()
{
	return ModelViewerPresenter::Instance();
}
