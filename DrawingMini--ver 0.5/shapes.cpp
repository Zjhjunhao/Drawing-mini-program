#include "shapes.h"

Shapes::Shapes(ShapeType type,const QPoint& lastPoint,const QPoint& nowPoint,QImage& image):
    type(type),lastPoint(lastPoint),nowPoint(nowPoint),selected(false),background(image){}

void Shapes::setSelected(){selected=true;}

Rectangle::Rectangle(const QPoint& lastPoint,const QPoint& nowPoint,QImage& image):Shapes(RECTANGLE,lastPoint,nowPoint,image)
{
    rect=QRect(lastPoint,nowPoint);
}

void Rectangle::draw(QPainter& painter){
    painter.drawRect(rect.normalized());
}

bool Rectangle::contains(const QPoint& point){
    return rect.contains(point);
}

void Rectangle::move(const QPoint& last,const QPoint& now){
    // qDebug()<<last<<now;
    // qDebug()<<lastPoint<<nowPoint;
    // printQRectVertices();
    lastPoint+=(now-last);
    nowPoint+=(now-last);
    // qDebug()<<lastPoint<<nowPoint;
    rect=QRect(lastPoint,nowPoint);
    // printQRectVertices();
}

Ellipse::Ellipse(const QPoint& lastPoint,const QPoint& nowPoint,QImage& image):Shapes(ELLIPSE,lastPoint,nowPoint,image)
{
    int dx=lastPoint.x()-nowPoint.x();
    int dy=lastPoint.y()-nowPoint.y();
    int r=std::sqrt(dx*dx+dy*dy);
    rect=QRect(lastPoint.x()-r,lastPoint.y()-r,2*r,2*r);
}

void Ellipse::draw(QPainter& painter){
    painter.drawEllipse(rect.normalized());
}

bool Ellipse::contains(const QPoint& point){
    return rect.contains(point);
}

void Ellipse::move(const QPoint& last,const QPoint& now){
    lastPoint+=(now-last);
    nowPoint+=(now-last);
    int dx=lastPoint.x()-nowPoint.x();
    int dy=lastPoint.y()-nowPoint.y();
    int r=std::sqrt(dx*dx+dy*dy);
    rect=QRect(lastPoint.x()-r,lastPoint.y()-r,2*r,2*r);
}

Line::Line(const QPoint& lastPoint,const QPoint& nowPoint,QImage& image):Shapes(LINE,lastPoint,nowPoint,image)
{
    rect=QRect(lastPoint,nowPoint);
}

void Line::draw(QPainter& painter){
    painter.drawLine(lastPoint,nowPoint);
}
bool Line::contains(const QPoint& point){
    return rect.contains(point);
}

void Line::move(const QPoint& last,const QPoint& now){
    lastPoint+=(now-last);
    nowPoint+=(now-last);
    rect=QRect(lastPoint,nowPoint);
}
