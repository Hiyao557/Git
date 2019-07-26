/********************************************************************************
** Form generated from reading UI file 'QtAccountListWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTACCOUNTLISTWIDGET_H
#define UI_QTACCOUNTLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtAccountListWidget
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *QtAccountListWidget)
    {
        if (QtAccountListWidget->objectName().isEmpty())
            QtAccountListWidget->setObjectName(QString::fromUtf8("QtAccountListWidget"));
        QtAccountListWidget->resize(400, 300);
        gridLayout = new QGridLayout(QtAccountListWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(QtAccountListWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(QtAccountListWidget);

        QMetaObject::connectSlotsByName(QtAccountListWidget);
    } // setupUi

    void retranslateUi(QWidget *QtAccountListWidget)
    {
        QtAccountListWidget->setWindowTitle(QCoreApplication::translate("QtAccountListWidget", "QtAccountListWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtAccountListWidget: public Ui_QtAccountListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTACCOUNTLISTWIDGET_H
