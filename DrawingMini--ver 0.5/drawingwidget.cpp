#include "drawingwidget.h"
#include "ui_drawingwidget.h"
#include "mainwindow.h"
#include <QStatusBar>
#include <QDebug>
#include <QScrollBar>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawingWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);

    pen = new DrawingTools;
    int highResWidth = 4*int(width());  // 更高的宽度
    int highResHeight = 3*int(height()); // 更高的高度
    backgroundImage = QImage(highResWidth, highResHeight, QImage::Format_ARGB32_Premultiplied);
    backgroundImage.fill(Qt::white);

    // 增大绘画图像尺寸
    drawingImage = QImage(highResWidth, highResHeight, QImage::Format_ARGB32_Premultiplied);
    drawingImage.fill(QColor(0, 0, 0, 0));
    originalImage = drawingImage.copy();

    // 初始化视口
    viewportX = 0;
    viewportY = 0;
    viewportWidth = originalImage.width();
    viewportHeight = originalImage.height();

    scaleFactor = 1;
    drawing = false;
}

DrawingWidget::~DrawingWidget()
{
    delete ui;
    delete pen;
}

QPoint DrawingWidget::convertToOriginalCoordinates(const QPoint& point)
{
    double scaleX = static_cast<double>(viewportWidth) / width();
    double scaleY = static_cast<double>(viewportHeight) / height();
    int originalX = static_cast<int>(viewportX + point.x() * scaleX);
    int originalY = static_cast<int>(viewportY + point.y() * scaleY);
    return QPoint(originalX, originalY);
}

void DrawingWidget::adjustViewport()
{
    viewportX = qBound(0, viewportX, originalImage.width() - viewportWidth);
    viewportY = qBound(0, viewportY, originalImage.height() - viewportHeight);
    int centerX = viewportX + viewportWidth / 2;
    int centerY = viewportY + viewportHeight / 2;
    viewportX = centerX - viewportWidth / 2;
    viewportY = centerY - viewportHeight / 2;
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = convertToOriginalCoordinates(event->pos());
        drawing = true;

        // 获取 globalPos
        QPointF globalPos = event->globalPosition();

        // 创建 QMouseEvent 对象
        QMouseEvent convertedEvent(event->type(), QPointF(lastPoint), QPointF(), globalPos, event->button(), event->buttons(), event->modifiers(), Qt::MouseEventSource::MouseEventNotSynthesized);

        pen->DrawingEvent(drawingImage, backgroundImage, &convertedEvent, lastPoint, 1);
        update();
        qDebug() << "Start drawing at:" << lastPoint;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPoint currentPoint = convertToOriginalCoordinates(event->pos());

        // 获取 globalPos
        QPointF globalPos = event->globalPosition();

        // 创建 QMouseEvent 对象
        QMouseEvent convertedEvent(event->type(), QPointF(currentPoint), QPointF(), globalPos, event->button(), event->buttons(), event->modifiers(), Qt::MouseEventSource::MouseEventNotSynthesized);

        pen->DrawingEvent(drawingImage, backgroundImage, &convertedEvent, lastPoint);
        update();
    }
    if (MainWindow *mainWin = qobject_cast<MainWindow*>(window())) {
        mainWin->statusBar()->showMessage(
            QString("坐标: (%1, %2)").arg(event->pos().x()).arg(event->pos().y())
            );
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        originalImage = drawingImage.copy();
        qDebug() << "Stop drawing";
    }
}

void DrawingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect viewportRect(viewportX, viewportY, viewportWidth, viewportHeight);
    painter.drawImage(rect(), backgroundImage, viewportRect);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(rect(), drawingImage, viewportRect);
}


void DrawingWidget::clear()
{
    drawingImage.fill(QColor(0, 0, 0, 0));
    drawing = false;
    lastPoint = QPoint();
    update();
}

void DrawingWidget::setBackgroundImage(const QImage& image)
{
    backgroundImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

void DrawingWidget::setDrawingImage(const QSize& size)
{
    drawingImage = QImage(size, QImage::Format_ARGB32_Premultiplied);
    update();
}

void DrawingWidget::clearDrawingImage()
{
    drawingImage.fill(QColor(0, 0, 0, 0));
    update();
}

QImage DrawingWidget::getBackgroundImage() const
{
    return backgroundImage;
}

QImage DrawingWidget::getDrawingImage() const
{
    return drawingImage;
}

void DrawingWidget::wheelEvent(QWheelEvent *event)
{
    const double scaleStep = 0.1;
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            viewportWidth = static_cast<int>(viewportWidth / (1 + scaleStep));
            viewportHeight = static_cast<int>(viewportHeight / (1 + scaleStep));
        } else {
            viewportWidth = static_cast<int>(viewportWidth * (1 + scaleStep));
            viewportHeight = static_cast<int>(viewportHeight * (1 + scaleStep));
        }
        viewportWidth = qBound(1, viewportWidth, originalImage.width());
        viewportHeight = qBound(1, viewportHeight, originalImage.height());
        adjustViewport();
        update();
        event->accept();
    } else {
        QWidget::wheelEvent(event);
    }
}
