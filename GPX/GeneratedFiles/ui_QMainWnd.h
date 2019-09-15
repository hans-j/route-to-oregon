/********************************************************************************
** Form generated from reading UI file 'QMainWnd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWND_H
#define UI_QMAINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qslippymapwnd.h"

QT_BEGIN_NAMESPACE

class Ui_QMainWndClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditLaenge;
    QLineEdit *lineEditName;
    QSlippyMapWnd *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QMainWndClass)
    {
        if (QMainWndClass->objectName().isEmpty())
            QMainWndClass->setObjectName(QString::fromUtf8("QMainWndClass"));
        QMainWndClass->resize(600, 400);
        centralWidget = new QWidget(QMainWndClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditLaenge = new QLineEdit(centralWidget);
        lineEditLaenge->setObjectName(QString::fromUtf8("lineEditLaenge"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditLaenge->sizePolicy().hasHeightForWidth());
        lineEditLaenge->setSizePolicy(sizePolicy);
        lineEditLaenge->setMinimumSize(QSize(100, 0));
        lineEditLaenge->setMaximumSize(QSize(100, 16777215));
        lineEditLaenge->setReadOnly(true);

        horizontalLayout->addWidget(lineEditLaenge);

        lineEditName = new QLineEdit(centralWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);


        verticalLayout->addLayout(horizontalLayout);

        widget = new QSlippyMapWnd(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(widget);


        horizontalLayout_2->addLayout(verticalLayout);

        QMainWndClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QMainWndClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 18));
        QMainWndClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QMainWndClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QMainWndClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QMainWndClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QMainWndClass->setStatusBar(statusBar);

        retranslateUi(QMainWndClass);

        QMetaObject::connectSlotsByName(QMainWndClass);
    } // setupUi

    void retranslateUi(QMainWindow *QMainWndClass)
    {
        QMainWndClass->setWindowTitle(QApplication::translate("QMainWndClass", "QMainWnd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMainWndClass: public Ui_QMainWndClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWND_H
