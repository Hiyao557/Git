#include "QtAccountListWidget.h"
#include "UserManager.h"
using namespace Monitor;
QtAccountListWidget::QtAccountListWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    auto users=	UserManager::GetInstance()->GetUserMap();
    for (auto user : users) {
	QListWidgetItem *item = new QListWidgetItem;
	item->setText(QString(user.first.c_str()));
	ui.listWidget->addItem(item);
    }

}

QtAccountListWidget::~QtAccountListWidget()
{


}
