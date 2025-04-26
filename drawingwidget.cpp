#include "drawingwidget.h"
#include "ui_drawingwidget.h"
#include "mainwindow.h"
#include <QStatusBar>
DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawingWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

DrawingWidget::~DrawingWidget()
{
    delete ui;
}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
        qDebug() << "Start drawing at:" << lastPoint;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
    if (MainWindow *mainWin = qobject_cast<MainWindow*>(window())) {
        mainWin->statusBar()->showMessage(
            QString("坐标: (%1, %2)").arg(event->pos().x()).arg(event->pos().y())
            );
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        qDebug() << "Stop drawing";
    }
}

void DrawingWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void DrawingWidget::resizeEvent(QResizeEvent *event) {
    if (width() > image.width() || height() > image.height()) {
        QImage newImage(event->size(), QImage::Format_RGB32);
        newImage.fill(Qt::white);
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), image);
        image = newImage;
    }
    QWidget::resizeEvent(event);
}
