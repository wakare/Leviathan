#include "SOFilterDebuger.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SOFilterDebuger w;
	w.show();
	return a.exec();
}
