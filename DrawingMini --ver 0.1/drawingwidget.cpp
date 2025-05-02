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

    pen = new DrawingTools;
    // 初始化背景图层，填充为白色
    backgroundImage = QImage(size(), QImage::Format_RGB32);
    backgroundImage.fill(Qt::white);
    // 初始化绘画图层，填充为透明
    drawingImage = QImage(size(), QImage::Format_RGB32);
    drawingImage.fill(QColor(254,254,254,0));
}

DrawingWidget::~DrawingWidget()
{
    delete ui;
    delete pen;
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
        QPainter painter(&drawingImage);
        painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

        QColor bgColor = backgroundImage.pixelColor(event->pos());
        painter.setPen(pen->getPen(bgColor));

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
    // 先绘制背景图层
    painter.drawImage(0, 0, backgroundImage);
    // 再绘制绘画图层
    painter.drawImage(0, 0, drawingImage);
}

void DrawingWidget::resizeEvent(QResizeEvent *event) {
    // 调整背景图层大小
    QImage newBackgroundImage(event->size(), QImage::Format_RGB32);
    newBackgroundImage.fill(Qt::white);
    QPainter bgPainter(&newBackgroundImage);
    bgPainter.drawImage(QPoint(0, 0), backgroundImage);
    backgroundImage = newBackgroundImage;

    // 调整绘画图层大小
    QImage newDrawingImage(event->size(), QImage::Format_RGB32);
    newDrawingImage.fill(QColor(254,254,254,0));
    QPainter dwPainter(&newDrawingImage);
    dwPainter.drawImage(QPoint(0, 0), drawingImage);
    drawingImage = newDrawingImage;

    QWidget::resizeEvent(event);
}
