#include "CtpMonitorQT.h"
#include "QtAccountListDetailWidget.h"
#include "QtAccountListWidget.h"
#include "QtAccountDetailWidget.h"
#include "QtLogWidget.h"
#include <QDockWidget>



CtpMonitorQT::CtpMonitorQT(QWidget *parent)
	: QMainWindow(parent)
{ 
	ui.setupUi(this);
	QWidget* p = takeCentralWidget();
	if (p)
		delete p;
	setDockNestingEnabled(true);
	
//	QTabWidget * qtabwidget = new QTabWidget(this);
	//QDockWidget * qdockwidget0 = new QDockWidget(u8"账户视图",this);
	//QtAccountListWidget * widget_accountlist = new QtAccountListWidget;
	//qdockwidget0->setWidget(widget_accountlist);
	//addDockWidget(Qt::LeftDockWidgetArea, qdockwidget0);
	QDockWidget * qdockwidget1 = new QDockWidget(u8"账户详细内容",this);
	QtAccountDetailWidget * widget_accountdetail = new QtAccountDetailWidget;
	//qdockwidget1->setStyleSheet(QString::fromUtf8("border:1px solid red"));
	qdockwidget1->setWidget(widget_accountdetail);
	addDockWidget(Qt::LeftDockWidgetArea, qdockwidget1);
//	splitDockWidget(qdockwidget0,qdockwidget1,Qt::Horizontal);
	QDockWidget * qdockwidget2 = new QDockWidget(u8"日志信息",this);
	QtLogWidget * widget_log = new QtLogWidget();
	qdockwidget2->setWidget(widget_log);
	splitDockWidget(qdockwidget1, qdockwidget2,Qt::Horizontal);
	QDockWidget * qdockwidget3 = new QDockWidget(u8"账户列表详细",this);
	QtAccountListDetailWidget * widget_accountlistdetail = new QtAccountListDetailWidget;
	qdockwidget3->setWidget(widget_accountlistdetail);
	//qtabwidget->addTab(qdockwidget3,"222");
	tabifyDockWidget(qdockwidget1, qdockwidget3);
	this->setTabPosition(Qt::TopDockWidgetArea, QTabWidget::North);
	m_docks.append(qdockwidget1);
	m_docks.append(qdockwidget2);
	QObject::connect(ui.action_D, SIGNAL(triggered()), this, SLOT(On_Menu_Log()));
	QObject::connect(ui.action_M, SIGNAL(triggered()), this, SLOT(On_Menu_AccountList()));
	QObject::connect(ui.action_T, SIGNAL(triggered()), this, SLOT(On_Menu_AccountDetail()));
	
}
void  CtpMonitorQT::On_Menu_AccountList() {
	QDockWidget * qdockwidget = new QDockWidget(this);
	QtAccountListDetailWidget * widget_accountlist = new QtAccountListDetailWidget;
	qdockwidget->setWidget(widget_accountlist);
	addDockWidget(Qt::LeftDockWidgetArea, qdockwidget);
}

void CtpMonitorQT::RemoveALLDock()
{
	for (int i = 0; i < m_docks.size(); i++) {
		removeDockWidget(m_docks[i]);
	}
}

void CtpMonitorQT::ShowDock(const QList<int>& index)
{
	if (index.isEmpty()) 
	{ 
		for (int i = 0; i<m_docks.size(); i++) {
			m_docks[i]->show();
		}
	}
	else 
	{ 
		foreach(int i, index) { m_docks[i]->show(); }
	}
}

void CtpMonitorQT::On_Menu_AccountDetail()
{
	QDockWidget * qdockwidget = new QDockWidget(this);
	QtAccountDetailWidget * widget_accountdetail = new QtAccountDetailWidget;
	qdockwidget->setWidget(widget_accountdetail);
	addDockWidget(Qt::LeftDockWidgetArea, qdockwidget);
}

void CtpMonitorQT::On_Menu_Log()
{
	QDockWidget * qdockwidget = new QDockWidget(this);
	QtLogWidget * logwidget = new QtLogWidget;
	qdockwidget->setWidget(logwidget);
	addDockWidget(Qt::LeftDockWidgetArea, qdockwidget);
}
