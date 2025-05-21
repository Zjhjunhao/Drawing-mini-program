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
    shape=nullptr;
    setMouseTracking(true);
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

void DrawingTools::DrawingEvent(QImage& drawingImage,QPoint& nowPoint,QPoint& lastPoint,int type){
    setPen();
    QPainter painter(&drawingImage);
    //painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform,size!=2);
    painter.setPen(pen);
    if(this->mode==0){//pencil or eraser
        QPoint alignedLastPoint(lastPoint.x() + 0.5, lastPoint.y() + 0.5);
        QPoint alignedNowPoint(nowPoint.x() + 0.5, nowPoint.y() + 0.5);
        painter.drawLine(alignedLastPoint, alignedNowPoint);
        //painter.drawLine(lastPoint, nowPoint);
        lastPoint = nowPoint;
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
                shape->setSelected(false,drawingImage);
                shape=nullptr;
            }
        }
        else{
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawImage(0, 0, tempImage);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            ShapeDrawing(painter,nowPoint,lastPoint);
            if(type==2&&shape != nullptr){
                emit returnShape(shape);
                shape->setSelected(false,drawingImage);
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
    default:return;
    }
    shape->draw(painter);
}

int DrawingTools::getmode(){
    return mode;
}

