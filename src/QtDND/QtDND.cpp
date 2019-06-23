#include "QtDND.h"
#include <QEvent.h>
#include <QMimeData.h>

QtDND::QtDND(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setAcceptDrops(true);

	ui.textEdit->setAcceptDrops(false);
}

void QtDND::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasFormat("text/uri-list")) {
		event->acceptProposedAction();
	}
}

void QtDND::dropEvent(QDropEvent * event)
{
	ui.textEdit->setText(event->mimeData()->text());
}
