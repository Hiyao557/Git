#include "QtAccountDetailWidget.h"
#include "UserManager.h"
#include "CtpRuntime.h"
#include "QFileDialog.h"
#include <fstream>
#include <QTextStream>
using namespace Monitor;

QtAccountDetailWidget::QtAccountDetailWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto users = UserManager::GetInstance()->GetUserMap();
	int RowCount = 0;
	ui.tableWidget_usr->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget_usr->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_usr->verticalHeader()->setVisible(false);
	ui.tableWidget_usr->horizontalHeader()->setVisible(false);
	for (auto user : users) {
		ui.tableWidget_usr->insertRow(RowCount);
		ui.tableWidget_usr->setItem(RowCount, 0, new QTableWidgetItem(QString("%1").arg(user.first.c_str())));
		ui.tableWidget_usr->setItem(RowCount, 1, new QTableWidgetItem(QString("%1").arg(user.second->username.c_str())));
		RowCount++;
	}

	QObject::connect(ui.tableWidget_usr, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(OnListClicked(QTableWidgetItem*)));
	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ExportFile()));

}
bool Complare(const CThostFtdcInvestorPositionDetailField& postioncom, const CThostFtdcInvestorPositionDetailField& postioncom1) {

	if (postioncom.Direction == '0' && postioncom1.Direction != '0') {
		return true;
	}
	else if(postioncom.Direction=='0'&&postioncom1.Direction=='0'){
		if(strcmp(postioncom.InstrumentID, postioncom1.InstrumentID) > 0)
			return true;
		return false;

	}
	else {

		return false;
	}

}

void QtAccountDetailWidget::OnListClicked(QTableWidgetItem* item)
{
	int row =item->row();
	QString id = ui.tableWidget_usr->item(row, 0)->text();
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->clearContents();
	int RowCount = ui.tableWidget->rowCount();
	 
	auto user=UserManager::GetInstance()->GetUser(id.toStdString());
	for (auto trade : user->tradelist) {
		ui.tableWidget->insertRow(RowCount);
		int columindex = 0;
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(trade.OrderRef));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(trade.InstrumentID));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(QString(trade.Direction==THOST_FTDC_D_Buy?u8"买":u8"卖")));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(QString(trade.OffsetFlag==THOST_FTDC_OF_Open?u8"开":u8"平")));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(trade.Price)));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(trade.Volume)));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(QString("%1  %2").arg(trade.TradeDate,trade.TradeTime)));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(trade.TradeID));
		ui.tableWidget->setItem(RowCount, columindex++, new QTableWidgetItem(trade.ExchangeID));
		RowCount++;
	}

	list<CThostFtdcTradeField> listcom;
	//listj.sort(CmpTrade);
	for (auto &trade : user->tradelist) {
		bool hastradecom = false;
		for (auto&tradecom : listcom) {
			if (strcmp(tradecom.InstrumentID, trade.InstrumentID) == 0 && tradecom.Direction == tradecom.Direction&&tradecom.OffsetFlag == tradecom.OffsetFlag) {
				hastradecom = true;
				tradecom.Price = (tradecom.Volume*tradecom.Price + trade.Volume*trade.Price) / (tradecom.Volume + tradecom.Volume);
				tradecom.Volume += trade.Volume;
				
			}
		}
		if (hastradecom == false)
		{
			listcom.push_back(trade);
		}

	}
	ui.tableWidget_6->setRowCount(0);
	ui.tableWidget_6->clearContents();
	 RowCount = ui.tableWidget_6->rowCount();
	for (auto trade : listcom) {
		ui.tableWidget_6->insertRow(RowCount);
		int columindex = 0;
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(trade.InstrumentID));
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(QString(trade.Direction == THOST_FTDC_D_Buy ? u8"买" : u8"卖")));
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(QString(trade.OffsetFlag == THOST_FTDC_OF_Open ? u8"开" : u8"平")));
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(trade.Price)));
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(trade.Volume)));
		ui.tableWidget_6->setItem(RowCount, columindex++, new QTableWidgetItem(trade.ExchangeID));
		RowCount++;
	}
	ui.tableWidget_2->setRowCount(0);
	ui.tableWidget_2->clearContents();
	RowCount = 0;
	for (auto order : user->orderlist) {
		ui.tableWidget_2->insertRow(RowCount);
		int columindex = 0;
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(order.OrderRef));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(order.InstrumentID));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString(order.Direction==THOST_FTDC_D_Buy?u8"买":u8"卖")));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString(order.CombOffsetFlag[0]==THOST_FTDC_OF_Open?u8"开":u8"平")));
		switch(order.OrderStatus)
		{
		case THOST_FTDC_OST_AllTraded:
		   ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(u8"全部成交"));
		   break;
		case THOST_FTDC_OST_PartTradedQueueing:
			ui.tableWidget_2->setItem(RowCount,columindex++,new QTableWidgetItem(u8"部分成交还在队列中"));
			break;
		case THOST_FTDC_OST_PartTradedNotQueueing:
			ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(u8"部分成交不在队列中"));
			break;
		case THOST_FTDC_OST_NoTradeQueueing:
			ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(u8"未成交还在队列中"));
			break;
		case THOST_FTDC_OST_Canceled:
			ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(u8"撤单"));
			break;
		default:
			ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(u8"未知"));
			break;
		}
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(order.LimitPrice)));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(order.VolumeTotalOriginal)));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(order.VolumeTraded)));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(QString::fromLocal8Bit(order.StatusMsg)));
		ui.tableWidget_2->setItem(RowCount, columindex++, new QTableWidgetItem(order.ExchangeID));
	}

	list<CThostFtdcInvestorPositionDetailField> listj = user->postionlist;
	list<CThostFtdcInvestorPositionDetailField> listpostioncom;
	//listj.sort(CmpTrade);

	

	for (auto &trade : listj) {
		bool hastradecom = false;
		for (auto&tradecom : listpostioncom) {
			if (strcmp(tradecom.InstrumentID, trade.InstrumentID) == 0 && tradecom.Direction == tradecom.Direction) {
				hastradecom = true;
				tradecom.Volume += trade.Volume;
				trade.OpenPrice = (tradecom.Volume*tradecom.OpenPrice + trade.Volume*trade.OpenPrice) / (tradecom.Volume + tradecom.Volume);
			}
		}
		if (hastradecom == false)
		{

			CTraderSpi* a = CtpRuntime::GetInstance()->userspimap[id.toStdString()];
			

			listpostioncom.push_back(trade);
		}
	}
	double directlong = 0.0;
	double directshort = 0.0;
	
	for (auto&postioncom : listpostioncom) {
		int multi = CtpRuntime::GetInstance()->userspimap[id.toStdString()]->instrumentmap[postioncom.InstrumentID].VolumeMultiple;
		if (postioncom.Direction == THOST_FTDC_D_Buy) 
		{
			directlong += postioncom.OpenPrice*multi*postioncom.Volume;
		}
		else 
		{
			directshort += postioncom.OpenPrice*multi*postioncom.Volume;
		}
	}
	if (directshort != 0||directlong!=0) {
		ui.widget->setPerset(directlong /(directshort+directlong) * 100);
		ui.widget->update();
	}
	if (directshort == 0 && directlong == 0) {
		ui.widget->setPerset(0);
		ui.widget->update();
	}
	
	ui.tableWidget_3->setRowCount(0);
	ui.tableWidget_3->clearContents();
	 RowCount= ui.tableWidget_3->rowCount();
	 listpostioncom.sort(Complare);
	for (auto postion : listpostioncom) {
		ui.tableWidget_3->insertRow(RowCount);
		int columindex = 0;
	    ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(postion.InstrumentID));
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString(postion.Direction==THOST_FTDC_D_Buy?u8"买":u8"卖")));
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.Volume)));
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.OpenPrice)));
		CTraderSpi* a = CtpRuntime::GetInstance()->userspimap[id.toStdString()];
		int multi = CtpRuntime::GetInstance()->userspimap[id.toStdString()]->instrumentmap[postion.InstrumentID].VolumeMultiple;
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(multi)));
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(multi*postion.OpenPrice*postion.Volume,'f',2)));
		ui.tableWidget_3->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(multi*postion.OpenPrice*postion.Volume*100/(directlong+directshort))));



	}

	ui.tableWidget_4->setRowCount(0);
	ui.tableWidget_4->clearContents();
	RowCount = ui.tableWidget_4->rowCount();
	for (auto postion : user->postionlist) {
		ui.tableWidget_4->insertRow(RowCount);
		if (postion.Volume == 0)
			continue;
		int columindex = 0;
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(postion.TradeID));
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(postion.InstrumentID));
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString(postion.Direction == THOST_FTDC_D_Buy ? u8"买" : u8"卖")));
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.Volume)));
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.OpenPrice)));
		//ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.CloseVolume)));
		//columindex++;
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString("%1").arg(postion.OpenDate)));
		ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.PositionProfitByTrade)));
		ui.tableWidget_4->setItem(RowCount,columindex++,new QTableWidgetItem(QString("%1").arg(postion.ExchangeID)));
	}

	ui.tableWidget_5->setRowCount(0);
	ui.tableWidget_5->clearContents();
	for (auto postioncom : user->postioncom) {
		// if(postioncom.)
		ui.tableWidget_5->insertRow(RowCount);
		int columindex = 0;
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(postioncom.TradeID));
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(postioncom.CombInstrumentID));
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(QString(postioncom.Direction == THOST_FTDC_D_Buy ? u8"买" : u8"卖")));
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postioncom.TotalAmt)));
		//ui.tableWidget_4->setItem(RowCount, columindex++, new QTableWidgetItem(QString::number(postion.CloseVolume)));
		//columindex++;
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(QString("%1").arg(postioncom.OpenDate)));

		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(QString("%1").arg(postioncom.Margin)));
		ui.tableWidget_5->setItem(RowCount, columindex++, new QTableWidgetItem(QString("%1").arg(postioncom.ExchangeID)));
	}




}
QtAccountDetailWidget::~QtAccountDetailWidget()
{
}

void QtAccountDetailWidget::ExportFile()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		QString::fromLocal8Bit("文件另存为"),
		"",
		tr("(*.csv)"));

	QFile file(fileName);
	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		QTextStream fout(&file);
		for (int i = 0; i<ui.tableWidget_3->rowCount(); i++) {
			for (int j = 0; j<ui.tableWidget_3->columnCount(); j++) {
				if (ui.tableWidget_3->item(i, j) != NULL) {               //一定要先判断非空，否则会报错
					fout << ui.tableWidget_3->item(i, j)->text();
					if (j != 6) {
						fout << ",";
					}
					else {
						fout << endl;
					}
				}
			}
		}
	}
	else
	{
		
	}
	file.close();
	

}
