#include "QtAccountListDetailWidget.h"
#include "UserManager.h"
#include "TraderSpi.h"
using namespace Monitor;
using namespace CTP;
QtAccountListDetailWidget::QtAccountListDetailWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	map<string, CtpUser*>  vector_user = UserManager::GetInstance()->GetUserMap();
	int rowindex = 0;
	for (auto it : vector_user) {
		auto user = it.second;
		char str_rowindex[11];
		memset(str_rowindex, rowindex + 1, sizeof(str_rowindex));
		sprintf(str_rowindex, "%d", rowindex);
		int RowCount = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(RowCount);
		ui.tableWidget->setItem(RowCount,0,new QTableWidgetItem(QString(u8"未连接")));
		ui.tableWidget->setItem(RowCount,1,new QTableWidgetItem(QString(it.second->userid.c_str())));
		ui.tableWidget->setItem(RowCount,2,new QTableWidgetItem(QString(it.second->username.c_str())));
		ui.tableWidget->setItem(RowCount,3,new QTableWidgetItem(QString("%1").arg(it.second->staticright)));
		ui.tableWidget->setItem(RowCount,4,new QTableWidgetItem(QString("%1").arg(it.second->dynicright)));
		ui.tableWidget->setItem(RowCount,5,new QTableWidgetItem(QString("%1").arg(it.second->margin)));
		ui.tableWidget->setItem(RowCount,6,new QTableWidgetItem(QString("%1").arg(it.second->deposti)));
		ui.tableWidget->setItem(RowCount,7,new QTableWidgetItem(QString("%1").arg(it.second->withdraw)));
		ui.tableWidget->setItem(RowCount,8,new QTableWidgetItem(QString("%1").arg(it.second->closeprofit)));
		ui.tableWidget->setItem(RowCount,9,new QTableWidgetItem(QString("%1").arg(it.second->postionprofit)));
		ui.tableWidget->setItem(RowCount,10,new QTableWidgetItem(QString("%1").arg(it.second->updatetime.c_str())));
		ui.tableWidget->setItem(RowCount,11,new QTableWidgetItem(QString("%1").arg(it.second->availablemoney)));
		//	list_account.SetItemText(rowindex,colindex++,user.)
		rowindex++;
	}
	QObject::connect(this, SIGNAL(userstatuschange(string)), this, SLOT(OnUserStatusChange(string)));
	CTraderSpi::event.Adddealer(this);

}

QtAccountListDetailWidget::~QtAccountListDetailWidget()
{
	CTraderSpi::event.Movedealer(this);

}

void QtAccountListDetailWidget::OnHxEvent(eventstruct event)
{
	if (event.type == eventtype::accountchange) {
		emit userstatuschange(event.message);
	}
}

void QtAccountListDetailWidget::OnUserStatusChange(string userid)
{
	map<string, CtpUser*>  vector_user = UserManager::GetInstance()->GetUserMap();
	int rowindex = 0;
	for (auto it : vector_user) {
		if (userid.compare(it.first) != 0)
		{
			rowindex++;
			continue;
		}
		auto user = it.second;
		//list_account.InsertItem(rowindex, str_rowindex);
		int colindex = 0;
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(user->connectstatus == true ? u8"已连接" : u8"未连接"));
		colindex++;
		colindex++;
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->staticright,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->dynicright,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->margin,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->deposti,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->withdraw,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->closeprofit,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->postionprofit,'f',2)));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString("%1").arg(user->updatetime.c_str())));
		ui.tableWidget->setItem(rowindex, colindex++, new QTableWidgetItem(QString::number(user->availablemoney, 'f', 2)));
		rowindex++;

	}

}
