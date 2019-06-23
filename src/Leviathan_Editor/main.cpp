#include "Leviathan_Editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Leviathan_Editor w;
	w.show();
	return a.exec();
}
