#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w = new MainWindow;
	w.sizeHint();
	/*w.setMinimumSize(300, 300);
	w.setMaximumSize(500, 500);*/
	w.show();
	return a.exec();

}
