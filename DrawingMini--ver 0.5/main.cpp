#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    a.setStyleSheet("QWidget#StartWidget{"
                    "    border-image: url(:/icons/background.jpg) 0 0 0 0 stretch stretch;"
                    "}");
    QPixmap pixmap(":/icons/background.jpg");
    if (pixmap.isNull()) {
        qDebug() << "Failed to load background image!";
    } else {
        qDebug() << "Image loaded successfully. Size:" << pixmap.size();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
