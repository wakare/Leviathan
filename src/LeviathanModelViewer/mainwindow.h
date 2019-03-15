#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BaseStruct.h"
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

public slots:
	void LoadFile();
	void OpenglWidgetResize();

protected:
	virtual void resizeEvent(QResizeEvent *event);

private:
	void _initialized();
	void _attachRenderService();
	void _runRenderService();
	
	ModelViewerPresenter& _modelViewerPresenter();
    Ui::MainWindow *ui;

	// Leviathan struct
	std::unique_ptr<LeviathanInitStruct> m_pLevStruct;
};

#endif // MAINWINDOW_H
