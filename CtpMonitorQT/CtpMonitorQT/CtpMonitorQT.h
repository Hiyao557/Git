#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CtpMonitorQT.h"


class CtpMonitorQT : public QMainWindow
{
	Q_OBJECT

public:
	CtpMonitorQT(QWidget *parent = Q_NULLPTR);
	void RemoveALLDock();
	void ShowDock(const QList<int>& index = QList<int>());

private:
	Ui::CtpMonitorQTClass ui;
	QList<QDockWidget*> m_docks;
	public slots:
	void On_Menu_AccountList();//’Àªß∏≈¿¿
	void On_Menu_AccountDetail();//’ÀªßœÍœ∏
	void On_Menu_Log();//log
};
