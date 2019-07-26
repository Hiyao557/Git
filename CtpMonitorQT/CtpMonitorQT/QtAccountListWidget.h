#pragma once

#include <QWidget>
#include "ui_QtAccountListWidget.h"

class QtAccountListWidget : public QWidget
{
	Q_OBJECT

public:
	QtAccountListWidget(QWidget *parent = Q_NULLPTR);
	~QtAccountListWidget();

private:
	Ui::QtAccountListWidget ui;
};
