/********************************************************************************
** Form generated from reading UI file 'drawingwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGWIDGET_H
#define UI_DRAWINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawingWidget
{
public:

    void setupUi(QWidget *DrawingWidget)
    {
        if (DrawingWidget->objectName().isEmpty())
            DrawingWidget->setObjectName("DrawingWidget");
        DrawingWidget->resize(441, 302);

        retranslateUi(DrawingWidget);

        QMetaObject::connectSlotsByName(DrawingWidget);
    } // setupUi

    void retranslateUi(QWidget *DrawingWidget)
    {
        DrawingWidget->setWindowTitle(QCoreApplication::translate("DrawingWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawingWidget: public Ui_DrawingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGWIDGET_H
