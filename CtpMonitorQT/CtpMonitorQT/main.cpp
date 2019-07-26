#include "CtpMonitorQT.h"
#include <QtWidgets/QApplication>
#include <QtGui>
#include "CtpRuntime.h"
#include <QMetaType>
int main(int argc, char *argv[])
{
	qRegisterMetaType<string>("string");
	QApplication a(argc, argv);
	CtpMonitorQT w;
	CtpRuntime::GetInstance()->Start();
	//w.showMaximized();
	w.show();
	return a.exec();
}
