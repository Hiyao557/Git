/********************************************************************************
** Form generated from reading UI file 'QtAccountDetailWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTACCOUNTDETAILWIDGET_H
#define UI_QTACCOUNTDETAILWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "QAccount.h"

QT_BEGIN_NAMESPACE

class Ui_QtAccountDetailWidget
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_usr;
    QTabWidget *tabWidget_3;
    QWidget *tab_10;
    QGridLayout *gridLayout_6;
    QTableWidget *tableWidget_2;
    QWidget *tab_11;
    QGridLayout *gridLayout_8;
    QTableWidget *tableWidget_7;
    QTabWidget *tabWidget_2;
    QWidget *tab_8;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget;
    QWidget *tab_9;
    QGridLayout *gridLayout_7;
    QTableWidget *tableWidget_6;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_3;
    QAccount *widget;
    QPushButton *pushButton;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget_4;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget_5;

    void setupUi(QWidget *QtAccountDetailWidget)
    {
        if (QtAccountDetailWidget->objectName().isEmpty())
            QtAccountDetailWidget->setObjectName(QString::fromUtf8("QtAccountDetailWidget"));
        QtAccountDetailWidget->resize(1100, 664);
        gridLayout = new QGridLayout(QtAccountDetailWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget_usr = new QTableWidget(QtAccountDetailWidget);
        if (tableWidget_usr->columnCount() < 2)
            tableWidget_usr->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_usr->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_usr->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget_usr->setObjectName(QString::fromUtf8("tableWidget_usr"));
        tableWidget_usr->setMaximumSize(QSize(357, 16777215));

        gridLayout->addWidget(tableWidget_usr, 0, 0, 5, 1, Qt::AlignLeft);

        tabWidget_3 = new QTabWidget(QtAccountDetailWidget);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tab_10 = new QWidget();
        tab_10->setObjectName(QString::fromUtf8("tab_10"));
        gridLayout_6 = new QGridLayout(tab_10);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tableWidget_2 = new QTableWidget(tab_10);
        if (tableWidget_2->columnCount() < 10)
            tableWidget_2->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(9, __qtablewidgetitem11);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

        gridLayout_6->addWidget(tableWidget_2, 0, 0, 1, 1);

        tabWidget_3->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName(QString::fromUtf8("tab_11"));
        gridLayout_8 = new QGridLayout(tab_11);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        tableWidget_7 = new QTableWidget(tab_11);
        if (tableWidget_7->columnCount() < 8)
            tableWidget_7->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_7->setHorizontalHeaderItem(7, __qtablewidgetitem19);
        tableWidget_7->setObjectName(QString::fromUtf8("tableWidget_7"));

        gridLayout_8->addWidget(tableWidget_7, 0, 0, 1, 1);

        tabWidget_3->addTab(tab_11, QString());

        gridLayout->addWidget(tabWidget_3, 1, 4, 1, 1);

        tabWidget_2 = new QTabWidget(QtAccountDetailWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        gridLayout_5 = new QGridLayout(tab_8);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableWidget = new QTableWidget(tab_8);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem28);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_5->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        gridLayout_7 = new QGridLayout(tab_9);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        tableWidget_6 = new QTableWidget(tab_9);
        if (tableWidget_6->columnCount() < 5)
            tableWidget_6->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(2, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(3, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(4, __qtablewidgetitem33);
        tableWidget_6->setObjectName(QString::fromUtf8("tableWidget_6"));

        gridLayout_7->addWidget(tableWidget_6, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_9, QString());

        gridLayout->addWidget(tabWidget_2, 1, 3, 1, 1);

        tabWidget = new QTabWidget(QtAccountDetailWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget_3 = new QTableWidget(tab);
        if (tableWidget_3->columnCount() < 7)
            tableWidget_3->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem40);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));

        gridLayout_2->addWidget(tableWidget_3, 1, 0, 1, 1);

        widget = new QAccount(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(281, 0));

        gridLayout_2->addWidget(widget, 1, 1, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(509, 16777215));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1, Qt::AlignLeft);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidget_4 = new QTableWidget(tab_2);
        if (tableWidget_4->columnCount() < 8)
            tableWidget_4->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(7, __qtablewidgetitem48);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));

        gridLayout_3->addWidget(tableWidget_4, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableWidget_5 = new QTableWidget(tab_3);
        if (tableWidget_5->columnCount() < 7)
            tableWidget_5->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(4, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(5, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(6, __qtablewidgetitem55);
        tableWidget_5->setObjectName(QString::fromUtf8("tableWidget_5"));

        gridLayout_4->addWidget(tableWidget_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 2, 3, 1, 2);


        retranslateUi(QtAccountDetailWidget);

        tabWidget_3->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtAccountDetailWidget);
    } // setupUi

    void retranslateUi(QWidget *QtAccountDetailWidget)
    {
        QtAccountDetailWidget->setWindowTitle(QCoreApplication::translate("QtAccountDetailWidget", "QtAccountDetailWidget", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_usr->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("QtAccountDetailWidget", "\347\224\250\346\210\267ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_usr->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("QtAccountDetailWidget", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\345\271\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\214\202\345\215\225\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\234\252\346\210\220\344\272\244\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(8);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("QtAccountDetailWidget", "\350\257\246\347\273\206\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(9);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\272\244\346\230\223\346\211\200", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_10), QCoreApplication::translate("QtAccountDetailWidget", "\346\211\200\346\234\211\345\247\224\346\211\230\345\215\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_7->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_7->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_7->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_7->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\345\271\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_7->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_7->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\234\252\346\210\220\344\272\244\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_7->horizontalHeaderItem(6);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_7->horizontalHeaderItem(7);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\346\227\266\351\227\264", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_11), QCoreApplication::translate("QtAccountDetailWidget", "\346\234\252\346\210\220\344\272\244\345\215\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\212\245\345\215\225\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\345\271\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\272\244\346\230\223\346\211\200", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\346\230\216\347\273\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_6->horizontalHeaderItem(0);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_6->horizontalHeaderItem(1);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_6->horizontalHeaderItem(2);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\345\271\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_6->horizontalHeaderItem(3);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\345\235\207\344\273\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_6->horizontalHeaderItem(4);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\346\211\213\346\225\260", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\345\220\210\350\256\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\200\273\346\214\201\344\273\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\214\201\344\273\223\345\235\207\344\273\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\235\240\346\235\206\347\216\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("QtAccountDetailWidget", "\350\264\247\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_3->horizontalHeaderItem(6);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("QtAccountDetailWidget", "\350\264\247\345\200\274\345\215\240\346\257\224", nullptr));
        pushButton->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\257\274\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QtAccountDetailWidget", "\346\214\201\344\273\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\230\250\347\273\223\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\344\273\223\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\265\256\345\212\250\347\233\210\344\272\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_4->horizontalHeaderItem(7);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\272\244\346\230\223\346\211\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QtAccountDetailWidget", "\346\214\201\344\273\223\346\230\216\347\273\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\210\220\344\272\244\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\220\210\347\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\271\260\345\215\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("QtAccountDetailWidget", "\346\211\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget_5->horizontalHeaderItem(4);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("QtAccountDetailWidget", "\345\274\200\344\273\223\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget_5->horizontalHeaderItem(5);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\277\235\350\257\201\351\207\221", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget_5->horizontalHeaderItem(6);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("QtAccountDetailWidget", "\344\272\244\346\230\223\346\211\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("QtAccountDetailWidget", "\347\273\204\345\220\210\346\214\201\344\273\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtAccountDetailWidget: public Ui_QtAccountDetailWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTACCOUNTDETAILWIDGET_H
