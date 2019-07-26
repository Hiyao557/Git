#pragma once
#include<QPen>
#include<QPaintEvent>
#include <QWidget>
#include <QPainter>

class QAccount : public QWidget
{
	Q_OBJECT

private:
	int perset;
public:
	QAccount(QWidget *parent);
	~QAccount();
	void paintEvent(QPaintEvent *);
	void setPerset(int perset);
};
