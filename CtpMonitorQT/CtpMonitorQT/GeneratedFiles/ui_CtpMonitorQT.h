/********************************************************************************
** Form generated from reading UI file 'CtpMonitorQT.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTPMONITORQT_H
#define UI_CTPMONITORQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CtpMonitorQTClass
{
public:
    QAction *action_C;
    QAction *action_G;
    QAction *action_D;
    QAction *action_T;
    QAction *action_M;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_V;
    QMenu *menu_A;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CtpMonitorQTClass)
    {
        if (CtpMonitorQTClass->objectName().isEmpty())
            CtpMonitorQTClass->setObjectName(QStringLiteral("CtpMonitorQTClass"));
        CtpMonitorQTClass->resize(873, 700);
        QIcon icon;
        icon.addFile(QStringLiteral("logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CtpMonitorQTClass->setWindowIcon(icon);
        action_C = new QAction(CtpMonitorQTClass);
        action_C->setObjectName(QStringLiteral("action_C"));
        action_G = new QAction(CtpMonitorQTClass);
        action_G->setObjectName(QStringLiteral("action_G"));
        action_D = new QAction(CtpMonitorQTClass);
        action_D->setObjectName(QStringLiteral("action_D"));
        action_T = new QAction(CtpMonitorQTClass);
        action_T->setObjectName(QStringLiteral("action_T"));
        action_M = new QAction(CtpMonitorQTClass);
        action_M->setObjectName(QStringLiteral("action_M"));
        centralWidget = new QWidget(CtpMonitorQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CtpMonitorQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CtpMonitorQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 873, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_V = new QMenu(menuBar);
        menu_V->setObjectName(QStringLiteral("menu_V"));
        menu_A = new QMenu(menuBar);
        menu_A->setObjectName(QStringLiteral("menu_A"));
        CtpMonitorQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CtpMonitorQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CtpMonitorQTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CtpMonitorQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CtpMonitorQTClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_V->menuAction());
        menuBar->addAction(menu_A->menuAction());
        menu_V->addAction(action_D);
        menu_V->addAction(action_T);
        menu_V->addAction(action_M);

        retranslateUi(CtpMonitorQTClass);
        QObject::connect(CtpMonitorQTClass, SIGNAL(destroyed()), CtpMonitorQTClass, SLOT(close()));

        QMetaObject::connectSlotsByName(CtpMonitorQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *CtpMonitorQTClass)
    {
        CtpMonitorQTClass->setWindowTitle(QApplication::translate("CtpMonitorQTClass", "CtpMonitorQT", Q_NULLPTR));
        action_C->setText(QApplication::translate("CtpMonitorQTClass", "\350\264\246\346\210\267\345\210\227\350\241\250(&C)", Q_NULLPTR));
        action_G->setText(QApplication::translate("CtpMonitorQTClass", "\350\264\246\345\217\267\350\275\247\345\267\256\350\247\206\345\233\276(&G)", Q_NULLPTR));
        action_D->setText(QApplication::translate("CtpMonitorQTClass", "\350\276\223\345\207\272\347\252\227\345\217\243(&D)", Q_NULLPTR));
        action_T->setText(QApplication::translate("CtpMonitorQTClass", "\350\264\246\346\210\267\350\257\246\347\273\206\344\277\241\346\201\257\347\252\227\345\217\243(&T)", Q_NULLPTR));
        action_M->setText(QApplication::translate("CtpMonitorQTClass", "\350\264\246\346\210\267\345\210\227\350\241\250\350\257\246\347\273\206(&M)", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("CtpMonitorQTClass", "\347\263\273\347\273\237\350\256\276\347\275\256(&F)", Q_NULLPTR));
        menu_V->setTitle(QApplication::translate("CtpMonitorQTClass", "\350\247\206\345\233\276(&V)", Q_NULLPTR));
        menu_A->setTitle(QApplication::translate("CtpMonitorQTClass", "\345\205\263\344\272\216(&A)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CtpMonitorQTClass: public Ui_CtpMonitorQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTPMONITORQT_H
