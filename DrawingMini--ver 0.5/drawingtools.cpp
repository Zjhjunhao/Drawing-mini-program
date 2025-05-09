#include "drawingtools.h"
#include <QDebug>
#include<cmath>

DrawingTools::DrawingTools(QWidget *parent)
    : QWidget{parent}
{
    this->color = Qt::black;
    this->size = 5;
    this->mode = 0; // 默认模式为铅笔
    this->pen = Pencil();
    setMouseTracking(true);
}

void DrawingTools::setColor(QColor color) {
    this->color = color;
}

void DrawingTools::setSize(int size) {
    this->size = size;
}

QPen DrawingTools::Pencil() {
    return QPen(this->color, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QPen DrawingTools::Eraser(QImage& image) {
    QPen epen=QPen(Qt::transparent, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    epen.setBrush(image);
    return epen;
}

QPen DrawingTools::ShapePen(){
    return QPen(this->color, this->size, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
}

void DrawingTools::setMode(int mode) {
    this->mode=mode;
}

void DrawingTools::setPen(QImage& image) {
    switch (mode) {
    case 0:
        pen=Pencil();
        break;
    case 1:
        pen=Eraser(image);
        break;
    default:
        pen=ShapePen();
    }
}

void DrawingTools::DrawingEvent(QImage& drawingImage,QImage& backgroundImage,QMouseEvent *event,QPoint& lastPoint,int type){
    setPen(backgroundImage);
    QPainter painter(&drawingImage);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setPen(pen);
    if(this->mode==0||this->mode==1){//pencil or eraser
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
    }
    else{//shapes
        if(type==1){//MousePressEvent中传入未绘制前的画布，需保存
            this->tempImage=drawingImage.copy();
            return;
        }
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawImage(0, 0, tempImage);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        ShapeDrawing(painter,event,lastPoint);
    }
}

void DrawingTools::ShapeDrawing(QPainter& painter,QMouseEvent *event,QPoint& lastPoint){
    switch (mode) {
    case 2:{
        QRect rect(lastPoint, event->pos());
        painter.drawRect(rect.normalized());
        break;
    }
    case 3:{
        int dx=lastPoint.x()-event->pos().x();
        int dy=lastPoint.y()-event->pos().y();
        int r=std::sqrt(dx*dx+dy*dy);
        QRectF rect(lastPoint.x()-r,lastPoint.y()-r,2*r,2*r);
        painter.drawEllipse(rect.normalized());
        break;
    }
    case 4:{
        painter.drawLine(lastPoint, event->pos());
        break;
    }
    }
}

int DrawingTools::getmode(){
    return mode;
}

