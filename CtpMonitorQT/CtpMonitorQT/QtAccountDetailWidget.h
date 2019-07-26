#pragma once

#include <QWidget>
#include "ui_QtAccountDetailWidget.h"

class QtAccountDetailWidget : public QWidget
{
	Q_OBJECT

public:
	QtAccountDetailWidget(QWidget *parent = Q_NULLPTR);
	~QtAccountDetailWidget();

private:
	Ui::QtAccountDetailWidget ui;
private slots:
	void OnListClicked(QTableWidgetItem* item);
	void ExportFile();

};
