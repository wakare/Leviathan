#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelViewerPresenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	void _attachRenderService();
	void _runRenderService();
	ModelViewerPresenter& _modelViewerPresenter();


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
