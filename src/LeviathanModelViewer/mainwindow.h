#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
	void Update();

protected:
	virtual void resizeEvent(QResizeEvent *event);

private:
	void _pushTask(std::function<void()> task);
	void _processTask();
	void _initialized();
	void _runRenderService();

	IController& _controller();
    Ui::MainWindow *ui;

	// Leviathan struct
	std::unique_ptr<LeviathanInitStruct> m_pLevStruct;
	QTimer m_updateTimer;
	
	std::vector<std::function<void()>> m_tasks;
	std::mutex m_taskLock;
};

#endif // MAINWINDOW_H
