#include "drawingtools.h"
#include <QDebug>
#include <cmath>
#include <stack>

DrawingTools::DrawingTools(QWidget *parent)
    : QWidget{parent}
{
    this->color = Qt::black;
    this->size = 5;
    this->mode = 0; // 默认模式为铅笔
    this->pen = Pencil();
    this->lastUsedMode = 0;
    shape=nullptr;
    setMouseTracking(true);
    this->textSize = 200; // 默认字体大小
}

void DrawingTools::setColor(QColor color) {
    this->color = color;
}

void DrawingTools::setSize(int size) {
    this->size = size;
}

void DrawingTools::setSelectedShape(Shapes* p){
    qDebug()<<"got it!";
    this->shape=p;
}

QPen DrawingTools::Pencil() {
    return QPen(this->color, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QPen DrawingTools::Eraser() {
    QPen epen=QPen(Qt::transparent, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    return epen;
}

QPen DrawingTools::ShapePen(){
    return QPen(this->color, this->size, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
}

void DrawingTools::setMode(int mode) {
    if (this->mode != 7) {
        lastUsedMode = this->mode;
    }
    this->mode=mode;
}

void DrawingTools::setPen() {
    switch (mode) {
    case 0:
        pen=Pencil();
        break;
    case 1:
        pen=Eraser();
        break;
    default:
        pen=ShapePen();
    }
}

void DrawingTools::setTextSize(int size) {
    this->textSize = size;
}

QColor DrawingTools::getColor(){
    return this->color;
}

void DrawingTools::DrawingEvent(QImage& drawingImage,QPoint& nowPoint,QPoint& lastPoint,int type){
    setPen();
    QPainter painter(&drawingImage);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform,size!=2);
    painter.setPen(pen);
    if(this->mode==0){//pencil
        QPoint alignedLastPoint(lastPoint.x() + 0.5, lastPoint.y() + 0.5);
        QPoint alignedNowPoint(nowPoint.x() + 0.5, nowPoint.y() + 0.5);
        painter.drawLine(alignedLastPoint, alignedNowPoint);
        //painter.drawLine(lastPoint, nowPoint);
        lastPoint = nowPoint;
        painter.end();
    }
    else if (this->mode == 8) { //文本框
        textPosition = nowPoint;

        painter.setFont(QFont("Arial", textSize));
        painter.setPen(color);
        painter.drawText(textPosition, text);
        painter.end();
    }
    else{//shapes
        if(type==1){//MousePressEvent中传入未绘制前的画布，需保存
            this->tempImage=drawingImage.copy();
            return;
        }
        if(mode==6&&shape!=nullptr){// select mode
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawImage(0, 0, tempImage);
            shape->move(lastPoint,nowPoint);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.setPen(shape->pen);
            shape->draw(painter);
            lastPoint=nowPoint;
            if(type==2){
                painter.end();
                shape->setSelected(false,drawingImage);
                tempImage = drawingImage.copy();
                shape=nullptr;
            }
        }
        else{
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawImage(0, 0, tempImage);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            ShapeDrawing(painter,nowPoint,lastPoint);
            if(type==2&&shape != nullptr){
                painter.end();
                emit returnShape(shape);
                shape->setSelected(false,drawingImage);
                tempImage = drawingImage.copy();
            }
            else{
                delete shape;
            }
            shape=nullptr;
        }
    }
}

void DrawingTools::DrawingEvent(QImage& drawingImage,QImage& shapeImage,QPoint& nowPoint,QPoint& lastPoint){
    setPen();
    if(mode==5){//fill
        QImage temp=drawingImage.copy();
        QPainter painter(&temp);
        painter.drawImage(0,0,shapeImage);
        painter.end();
        scanLineFill(drawingImage,temp,nowPoint);
    }
    else{// eraser
        QPainter painter(&drawingImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
        painter.setPen(pen);
        painter.drawLine(lastPoint, nowPoint);
        painter.end();
        painter.begin(&shapeImage);
        painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.setPen(pen);
        painter.drawLine(lastPoint, nowPoint);
        painter.end();
        lastPoint = nowPoint;
    }
}

void DrawingTools::ColorPicker(QImage& drawingImage,QImage& shapeImage,QPoint& nowPoint){
    if (nowPoint.x() >= 0 && nowPoint.x() < drawingImage.width() &&
        nowPoint.y() >= 0 && nowPoint.y() < drawingImage.height()) {
        QRgb pixelShapeColor = shapeImage.pixel(nowPoint);
        QRgb pixelColor = drawingImage.pixel(nowPoint);
        QColor selectedColor(pixelColor);
        QColor selectedShapeColor(pixelShapeColor);
        //qDebug() << selectedShapeColor.name();
        if(selectedShapeColor.name() == "#000000"){
            this->color = selectedColor;
        }else{
            this->color = selectedShapeColor;
        }

        if (lastUsedMode != 7) {
            emit toolModeChanged(lastUsedMode);
        }
    }
}

void DrawingTools::setText(QString t)
{
    text = t;
}

void DrawingTools::ShapeDrawing(QPainter& painter,QPoint& nowPoint,QPoint& lastPoint){
    switch (mode) {
    case 2:{
        shape=new Rectangle(lastPoint,nowPoint);
        break;
    }
    case 3:{
        shape=new Ellipse(lastPoint,nowPoint);
        break;
    }
    case 4:{
        shape=new Line(lastPoint,nowPoint);
        break;
    }
    case 9:{
        shape =new PKUSticker(lastPoint,nowPoint,badgeImage);
        break;
    }
    case 10:{
        shape =new PKUSticker(lastPoint,nowPoint,boyaImage);
        break;
    }
    default:return;
    }
    shape->draw(painter);
}

int DrawingTools::getmode(){
    return mode;
}

inline bool isSameColor(const QColor &c1, const QColor &c2) {
    int dr = qAbs(c1.red() - c2.red());
    int dg = qAbs(c1.green() - c2.green());
    int db = qAbs(c1.blue() - c2.blue());
    int da = qAbs(c1.alpha()-c2.alpha());
    return (dr + dg + db+da)<=30;
}

void DrawingTools::scanLineFill(QImage &drawingImage,QImage& composedImage, QPoint& point){
    const QColor &targetColor=composedImage.pixelColor(point);
    const QColor &replaceColor=color;
    int x=point.x();
    int y=point.y();

    if (targetColor == replaceColor)
        return;
    std::stack<std::pair<int, int>> pixelStack;
    pixelStack.push({x, y});
    while (!pixelStack.empty()) {
        auto [currentX, currentY] = pixelStack.top();
        pixelStack.pop();
        // 向上填充
        int y1 = currentY;
        while (y1 >= 0 && isSameColor(composedImage.pixelColor(currentX, y1), targetColor)) {
            drawingImage.setPixelColor(currentX, y1, replaceColor);  // 直接修改像素
            composedImage.setPixelColor(currentX, y1, replaceColor);
            y1--;
        }
        y1++;

        // 向下填充
        int y2 = currentY + 1;
        while (y2 < drawingImage.height() && isSameColor(composedImage.pixelColor(currentX, y2), targetColor)) {
            drawingImage.setPixelColor(currentX, y2, replaceColor);  // 直接修改像素
            composedImage.setPixelColor(currentX, y1, replaceColor);
            y2++;
        }
        y2--;
        // 处理左右边界
        for (int dir : {-1, 1}) {
            int xDir = currentX + dir;
            if (xDir < 0 || xDir >= drawingImage.width())
                continue;

            for (int yScan = y1; yScan <= y2; yScan++) {
                if (isSameColor(composedImage.pixelColor(xDir, yScan), targetColor)) {
                    if ((yScan == y1 || !isSameColor(composedImage.pixelColor(xDir, yScan - 1), replaceColor)) &&
                        (yScan == y2 || !isSameColor(composedImage.pixelColor(xDir, yScan + 1), replaceColor))) {
                        pixelStack.push({xDir, yScan});
                    }
                }
            }
        }

    }
}

void DrawingTools::setPKUImage(const QImage& badgeimage, const QImage& boyaimage)
{
    badgeImage = badgeimage;
    boyaImage = boyaimage;
}
