#include "drawingwidget.h"
#include "ui_drawingwidget.h"
#include "mainwindow.h"
#include <QStatusBar>
#include <QDebug>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawingWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);

    pen = new DrawingTools;

    backgroundImage = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    backgroundImage.fill(Qt::white);


    // 初始化绘画图层，填充为透明
    drawingImage = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    drawingImage.fill(QColor(0, 0, 0, 0));
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
        pen->DrawingEvent(drawingImage,backgroundImage,event,lastPoint,1);
        update();
        qDebug() << "Start drawing at:" << lastPoint;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        pen->DrawingEvent(drawingImage,backgroundImage,event,lastPoint);
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
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
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
    QImage newDrawingImage(event->size(), QImage::Format_ARGB32_Premultiplied);
    newDrawingImage.fill(QColor(0, 0, 0, 0));
    QPainter dwPainter(&newDrawingImage);
    dwPainter.drawImage(QPoint(0, 0), drawingImage);
    drawingImage = newDrawingImage;

    QWidget::resizeEvent(event);
}

void DrawingWidget::clear() {
    // 将绘画图层填充为透明
    drawingImage.fill(QColor(0, 0, 0, 0));
    // 重置绘图状态
    drawing = false;
    // 重置最后记录的鼠标点
    lastPoint = QPoint();
    // 触发重绘事件，更新界面
    update();
}

void DrawingWidget::setBackgroundImage(const QImage& image) {
    backgroundImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

void DrawingWidget::setDrawingImage(const QSize& size) {
    drawingImage = QImage(size, QImage::Format_ARGB32_Premultiplied);
    update();
}

void DrawingWidget::clearDrawingImage() {
    drawingImage.fill(QColor(0, 0, 0, 0));
    update();
}

QImage DrawingWidget::getBackgroundImage() const {
    return backgroundImage;
}

QImage DrawingWidget::getDrawingImage() const {
    return drawingImage;
}

