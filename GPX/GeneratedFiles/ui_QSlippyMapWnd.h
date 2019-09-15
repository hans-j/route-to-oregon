/********************************************************************************
** Form generated from reading UI file 'QSlippyMapWnd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSLIPPYMAPWND_H
#define UI_QSLIPPYMAPWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSlippyMapWnd
{
public:

    void setupUi(QWidget *QSlippyMapWnd)
    {
        if (QSlippyMapWnd->objectName().isEmpty())
            QSlippyMapWnd->setObjectName(QString::fromUtf8("QSlippyMapWnd"));
        QSlippyMapWnd->resize(400, 300);

        retranslateUi(QSlippyMapWnd);

        QMetaObject::connectSlotsByName(QSlippyMapWnd);
    } // setupUi

    void retranslateUi(QWidget *QSlippyMapWnd)
    {
        QSlippyMapWnd->setWindowTitle(QApplication::translate("QSlippyMapWnd", "Route to Oregon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QSlippyMapWnd: public Ui_QSlippyMapWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSLIPPYMAPWND_H
