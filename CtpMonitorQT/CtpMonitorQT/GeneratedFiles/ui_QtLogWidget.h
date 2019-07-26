/********************************************************************************
** Form generated from reading UI file 'QtLogWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLOGWIDGET_H
#define UI_QTLOGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLogWidget
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *QtLogWidget)
    {
        if (QtLogWidget->objectName().isEmpty())
            QtLogWidget->setObjectName(QString::fromUtf8("QtLogWidget"));
        QtLogWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(QtLogWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(QtLogWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        retranslateUi(QtLogWidget);

        QMetaObject::connectSlotsByName(QtLogWidget);
    } // setupUi

    void retranslateUi(QWidget *QtLogWidget)
    {
        QtLogWidget->setWindowTitle(QCoreApplication::translate("QtLogWidget", "QtLogWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtLogWidget: public Ui_QtLogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLOGWIDGET_H
