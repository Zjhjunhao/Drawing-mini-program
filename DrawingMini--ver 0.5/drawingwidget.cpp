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
    int highResWidth = static_cast<int>(8*width());  // 更高的宽度
    int highResHeight = static_cast<int>(5.5*height()); // 更高的高度
    backgroundImage = QImage(highResWidth, highResHeight, QImage::Format_ARGB32_Premultiplied);
    backgroundImage.fill(Qt::white);

    drawingImage = QImage(highResWidth, highResHeight, QImage::Format_ARGB32_Premultiplied);
    drawingImage.fill(QColor(0, 0, 0, 0));

    shapeImage = QImage(highResWidth, highResHeight, QImage::Format_ARGB32_Premultiplied);
    shapeImage.fill(QColor(0, 0, 0, 0));
    originalImage = drawingImage.copy();

    // 初始化视口
    viewportX = 0;
    viewportY = 0;
    viewportWidth = static_cast<int>(originalImage.width());
    viewportHeight = static_cast<int>(originalImage.height());

    scaleFactor = 1;
    drawing = false;

    connect(pen,&DrawingTools::returnShape,this,[this](Shapes* shape){
        shapes.push_back(shape);
    });

    connect(this,&DrawingWidget::selectedShape,pen,&DrawingTools::setSelectedShape);
    connect(pen, &DrawingTools::toolModeChanged, this, &DrawingWidget::setCurrentToolMode);
    connect(pen, &DrawingTools::toolModeChanged, this, [this](int mode) {
        toolBar->setSelectedTool(mode);
        pen->setMode(mode);
    });
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
    const int maxX = qMax(0, (backgroundImage.width() - viewportWidth));
    const int maxY = qMax(0, (backgroundImage.height() - viewportHeight));
    viewportX = qBound(0, viewportX, maxX);
    viewportY = qBound(0, viewportY, maxY);
    int centerX = static_cast<int>(viewportX + viewportWidth / 2);
    int centerY = static_cast<int>(viewportY + viewportHeight / 2);
    viewportX = static_cast<int>(centerX - viewportWidth / 2);
    viewportY = static_cast<int>(centerY - viewportHeight / 2);
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = convertToOriginalCoordinates(event->pos());
        drawing = true;
        QImage tempShape=shapeImage.copy();
        if (pen->getmode() == 7) {
            pen->ColorPicker(drawingImage, shapeImage, lastPoint);
            qDebug() << "Color picked at:" << lastPoint;
            return;
        }
        if(pen->getmode()==6){
            tempShape.fill(QColor(0,0,0,0));// 先清空
            Shapes* temp=nullptr;
            for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {// 找最上层的
                if ((*it)->contains(lastPoint)) {
                    emit selectedShape(*it);
                    temp=(*it);
                    shapes.erase(it.base()-1);
                    break;
                }
            }
            QPainter painter(&tempShape);
            for(auto it=shapes.begin();it!=shapes.end();++it){
                painter.setPen((*it)->pen);
                (*it)->draw(painter);
            }
            if(temp!=nullptr){
                shapes.push_back(temp);
            }
        }
        QImage tempImage=drawingImage.copy();
        QPainter painter(&tempImage);
        if(pen->getmode()!=5){
            tempImage.fill(QColor(0,0,0,0));

            painter.drawImage(0,0,tempShape);
            painter.end();
            pen->DrawingEvent(tempImage, lastPoint, lastPoint, 1);
        }
        else{
            pen->DrawingEvent(drawingImage,shapeImage,lastPoint,lastPoint);
        }
        update();
        qDebug() << "Start drawing at:" << lastPoint;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentPoint = convertToOriginalCoordinates(event->pos());
    if ((event->buttons() & Qt::LeftButton) && drawing && pen->getmode()!=5) {// fill时不调用
        if(pen->getmode()==0){// pencil，普通绘画
            pen->DrawingEvent(drawingImage, currentPoint, lastPoint);
        }
        else if(pen->getmode()==1){// eraser,橡皮擦
            pen->DrawingEvent(drawingImage,shapeImage, currentPoint, lastPoint);
        }
        else{// 形状 or select
            pen->DrawingEvent(shapeImage, currentPoint, lastPoint);
        }
        update();
    }
    if(pen->getmode()==6){// 选择框逻辑
        bool flag=false;// 是否有对象被选中
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {// 找最上层的
            if ((*it)->contains(currentPoint)&&!flag) {
                (*it)->setSelected(true,shapeImage);
                flag=true;
            }
            else{
                (*it)->setSelected(false,shapeImage);
            }
        }
        update();
    }
    if (MainWindow *mainWin = qobject_cast<MainWindow*>(window())) {
        mainWin->statusBar()->showMessage(
            QString("坐标: (%1, %2)      画布大小：(%3, %4)").arg(currentPoint.x()).arg(currentPoint.y()).arg(backgroundImage.width()).arg(backgroundImage.height())
            );
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint currentPoint = convertToOriginalCoordinates(event->pos());
    if (event->button() == Qt::LeftButton && drawing) {
        if(pen->getmode()==0){// pencil，普通绘画
            pen->DrawingEvent(drawingImage, currentPoint, lastPoint,2);
        }
        else if(pen->getmode()==1){// eraser,橡皮擦
            pen->DrawingEvent(drawingImage,shapeImage, currentPoint, lastPoint);
        }
        else if(pen->getmode()==5){// fill,无事发生

        }
        else{// 形状
            pen->DrawingEvent(shapeImage, currentPoint, lastPoint,2);
        }
        drawing = false;
        QPainter painter(&originalImage);
        painter.drawImage(0,0,drawingImage);
        painter.drawImage(0,0,shapeImage);
        qDebug() << "Stop drawing";
    }
}

void DrawingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect viewportRect(viewportX, viewportY, viewportWidth, viewportHeight);
    painter.drawImage(rect(), backgroundImage, viewportRect);
    painter.drawImage(rect(), drawingImage, viewportRect);
    painter.drawImage(rect(), shapeImage, viewportRect);

}


void DrawingWidget::clear()
{
    // 清除绘图图像，将其填充为透明色
    drawingImage.fill(QColor(0, 0, 0, 0));
    shapeImage.fill(QColor(0,0,0,0));
    originalImage = drawingImage.copy();

    // 重置背景图像为初始状态（白色）
    backgroundImage = QImage(backgroundImage.size(), QImage::Format_ARGB32_Premultiplied);
    backgroundImage.fill(Qt::white);

    // 重置绘图状态为未绘图
    drawing = false;

    // 重置最后一个鼠标点的坐标
    lastPoint = QPoint();

    // 重置视口到初始状态
    viewportX = 0;
    viewportY = 0;
    viewportWidth = static_cast<int>(originalImage.width());
    viewportHeight = static_cast<int>(originalImage.height());

    // 调整视口以确保在有效范围内
    adjustViewport();

    // 重置缩放比例
    scaleFactor = 1;

    // 发送信号更新滚动条的页面步长和位置
    double rX = static_cast<double>(viewportX) / (originalImage.width() - viewportWidth);
    double rY = static_cast<double>(viewportY) / (originalImage.height() - viewportHeight);
    double rH = static_cast<double>(viewportWidth) / originalImage.width();
    double rV = static_cast<double>(viewportHeight) / originalImage.height();
    emit pagePos(rX, rY);
    emit pageStepRatio(rH, rV);

    // 清空形状列表
    shapes.clear();

    // 更新绘图区域
    update();
}

void DrawingWidget::setBackgroundImage(const QImage& image, bool keepOriginalSize)
{
    if (keepOriginalSize) {
        // 保持原始尺寸
        backgroundImage = image.copy();

        // 重置画布尺寸
        originalImage = QImage(image.size(), QImage::Format_ARGB32_Premultiplied);
        originalImage.fill(QColor(0, 0, 0, 0));
        drawingImage = originalImage.copy();

        // 初始化视口
        viewportWidth = static_cast<int>(image.width());
        viewportHeight = static_cast<int>(image.height());
        viewportX = static_cast<int>((image.width() - viewportWidth) / 2);
        viewportY = static_cast<int>((image.height() - viewportHeight) / 2);
    } else {
        // 缩放适应现有画布
        backgroundImage = image.scaled(originalImage.size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
    }

    adjustViewport();
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

    } else {
        if(event->modifiers() & Qt::ShiftModifier){
            int scrollDistance = -1*event->angleDelta().y() / 6;
            viewportX += scrollDistance;
            viewportX = qBound(0, viewportX, originalImage.width() - viewportWidth);
        }
        else{
            int scrollDistance = -1*event->angleDelta().y() / 8;
            viewportY += scrollDistance;
            viewportY = qBound(0, viewportY, originalImage.height() - viewportHeight);
        }
    }
    double rX = static_cast<double>(viewportX) / (originalImage.width()-viewportWidth);
    double rY = static_cast<double>(viewportY) / (originalImage.height()-viewportHeight);
    double rH = static_cast<double>(viewportWidth) / originalImage.width();
    double rV = static_cast<double>(viewportHeight) / originalImage.height();
    emit pagePos(rX,rY);
    emit pageStepRatio(rH,rV);
    update();
    event->accept();
}

void DrawingWidget::handleHorizontalScroll(double ratio)
{
    viewportX = static_cast<int>(((originalImage.width())-viewportWidth)*ratio);
    adjustViewport();
    update();
}

void DrawingWidget::handleVerticalScroll(double ratio)
{
    viewportY = static_cast<int>(((originalImage.height())-viewportHeight)*ratio);
    adjustViewport();
    update();
}

void DrawingWidget::setCurrentToolMode(int mode)
{
    pen->setMode(mode);
}
