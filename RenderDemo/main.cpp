#include "renderdemo.h"
#include <QtWidgets/QApplication>

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow window;
	window.show();

	return a.exec();
}
