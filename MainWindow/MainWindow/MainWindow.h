#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include<QWidget>
#include<string>

using namespace std;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	QSize sizeHint() const
	{
		return QSize(500, 900);								//定义界面大小
	}

	//void OnHxEvent(eventstruct event);

//public slots:
//	void OnUserStatusChange(string userid);
//
//signals:
//	void UserStatusChange(string userid);
//
private:
	Ui::Form ui;
};
