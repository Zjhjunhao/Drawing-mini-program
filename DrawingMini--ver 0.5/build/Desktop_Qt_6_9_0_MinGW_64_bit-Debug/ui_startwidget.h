/********************************************************************************
** Form generated from reading UI file 'startwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWIDGET_H
#define UI_STARTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWidget
{
public:

    void setupUi(QWidget *StartWidget)
    {
        if (StartWidget->objectName().isEmpty())
            StartWidget->setObjectName("StartWidget");
        StartWidget->resize(400, 300);

        retranslateUi(StartWidget);

        QMetaObject::connectSlotsByName(StartWidget);
    } // setupUi

    void retranslateUi(QWidget *StartWidget)
    {
        StartWidget->setWindowTitle(QCoreApplication::translate("StartWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWidget: public Ui_StartWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWIDGET_H
