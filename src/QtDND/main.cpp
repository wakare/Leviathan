#include "QtDND.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtDND w;
	w.show();
	return a.exec();
}
