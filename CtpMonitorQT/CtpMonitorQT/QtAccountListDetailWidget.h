#pragma once

#include <QWidget>
#include "ui_QtAccountListDetailWidget.h"
#include "HxEventEngine.h"
using namespace CTPTOOL;
class QtAccountListDetailWidget : public QWidget,HxDealer
{
	Q_OBJECT

public:
	QtAccountListDetailWidget(QWidget *parent = Q_NULLPTR);
	~QtAccountListDetailWidget();
	QSize sizeHint() const
	{
		return QSize(500, 900); /* 在这里定义dock的初始大小 */
	}
	void OnHxEvent(eventstruct event);
	public slots:
	void OnUserStatusChange(string  userid);
    signals:
	void userstatuschange(string userid);
private:
	Ui::QtAccountListDetailWidget ui;
};
