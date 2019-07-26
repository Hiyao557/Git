#include "MainWindow.h"
#include<QMenu>
#include<QMenuBar>
#include <QToolBar> 
#include <QKeySequence>
#include<QMessageBox>
#include<QLabel>
#include<QFileDialog>
#include<QColorDialog>
#include<qdockwidget.h>
#include"CustomTradeSpi.h"

CThostFtdcTraderApi *g_pTradeUserApi;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	char *id = "9999";
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	int RowCount = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(RowCount);
	
	ui.tableWidget->setItem(RowCount, 0, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 1, new QTableWidgetItem(QString(g_pTradeUserApi->));
	ui.tableWidget->setItem(RowCount, 2, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 3, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 4, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 5, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 6, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 7, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 8, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 9, new QTableWidgetItem(QString("0")));
	ui.tableWidget->setItem(RowCount, 10, new QTableWidgetItem(QString("0")));
	//QDockWidget * qdockwidget3 = new QDockWidget(u8"�˻��б���ϸ", this);
	

	//ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch); //����Ӧ�п�

	ui.tableWidget->verticalHeader()->sizeHint();
		//->setResizeMode(QHeaderView::Stretch); //����Ӧ�и�


	//MainWindow * widget_accountlistdetail = new MainWindow;
	//qdockwidget3->setWidget(this);
	
	//QObject::connect(this, SIGNAL(triggered()), this, SLOT(On_Menu_AccountDetail()));
}



MainWindow::~MainWindow()
{

}
