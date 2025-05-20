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

void DrawingTools::DrawingEvent(QImage& drawingImage,QImage& backgroundImage,QPoint& nowPoint,QPoint& lastPoint,int type){
    setPen(backgroundImage);
    QPainter painter(&drawingImage);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setPen(pen);
    if(this->mode==0){//pencil or eraser
        painter.drawLine(lastPoint, nowPoint);
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
                shape=nullptr;
            }
        }
        else{
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.drawImage(0, 0, tempImage);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            ShapeDrawing(painter,nowPoint,lastPoint,type);

        }
    }
}

void DrawingTools::DrawingEvent(QImage& drawingImage,QImage& backgroundImage,QImage& shapeImage,QPoint& nowPoint,QPoint& lastPoint){
    setPen(backgroundImage);
    QPainter painter1(&drawingImage);
    QPainter painter2(&shapeImage);
    painter1.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter1.setPen(pen);
    painter2.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter2.setPen(pen);
    painter1.drawLine(lastPoint, nowPoint);
    painter2.drawLine(lastPoint, nowPoint);
    lastPoint = nowPoint;
}

void DrawingTools::ShapeDrawing(QPainter& painter,QPoint& nowPoint,QPoint& lastPoint,int flag){
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
    if(flag==2){// MouseReleaseEvent中调用，需传回Shape的指针
        emit returnShape(shape);
    }
    else{
        delete shape;
    }
    shape=nullptr;
}

int DrawingTools::getmode(){
    return mode;
}

