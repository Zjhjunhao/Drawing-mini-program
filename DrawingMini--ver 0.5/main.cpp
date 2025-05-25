#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/mainwindow.jpg"));
    MainWindow w;
    w.show();
    return a.exec();
}
