#pragma once

#include <QWidget>
#include "ui_QtLogWidget.h"
#include "HxEventEngine.h"
using namespace CTPTOOL;

class QtLogWidget : public QWidget,HxDealer
{
	Q_OBJECT

public:
	QtLogWidget(QWidget *parent = Q_NULLPTR);
	~QtLogWidget();
	QSize sizeHint() const
	{
		return QSize(100 ,900); /* �����ﶨ��dock�ĳ�ʼ��С */
	};
	void OnHxEvent(eventstruct event);
public slots:
	void OnAppendLog(QString log);
signals:
	void appendlog(QString log);

private:
	Ui::QtLogWidget ui;
};
