#include "shapes.h"

Shapes::Shapes(ShapeType type,const QPoint& lastPoint,const QPoint& nowPoint):
    type(type),lastPoint(lastPoint),nowPoint(nowPoint),selected(false),hasPen(false),pen(QPen()){}

void Shapes::setSelected(bool select,QImage& image){
    selected=select;
    changeSelectedWidget(image);
}

Rectangle::Rectangle(const QPoint& lastPoint,const QPoint& nowPoint):Shapes(RECTANGLE,lastPoint,nowPoint)
{
    rect=QRect(lastPoint,nowPoint);
}

void Rectangle::draw(QPainter& painter){
    if(!hasPen){
        pen=(painter.pen());
        hasPen=true;
    }
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawRect(rect.normalized());
}

bool Rectangle::contains(const QPoint& point){
    return rect.contains(point);
}

void Rectangle::move(const QPoint& last,const QPoint& now){
    lastPoint+=(now-last);
    nowPoint+=(now-last);
    rect=QRect(lastPoint,nowPoint);
}

void Rectangle::changeSelectedWidget(QImage& image){
    QPainter painter(&image);
    if(selected){
        QPen tmppen;
        tmppen.setWidth(3);
        tmppen.setStyle(Qt::CustomDashLine);
        tmppen.setDashPattern({5,5});
        tmppen.setColor([this](){
            int luminance = qGray(this->pen.color().rgb());
            // 简单阈值（通常取128，但可根据需要调整）
            return luminance > 128 ? Qt::black : Qt::white;
        }());
        painter.setPen(tmppen);
        painter.drawRect(rect.normalized());
    }
    else{
        painter.setPen(pen);
        painter.drawRect(rect.normalized());
    }
}

Ellipse::Ellipse(const QPoint& lastPoint,const QPoint& nowPoint):Shapes(ELLIPSE,lastPoint,nowPoint)
{
    int dx=lastPoint.x()-nowPoint.x();
    int dy=lastPoint.y()-nowPoint.y();
    int r=std::sqrt(dx*dx+dy*dy);
    rect=QRect(lastPoint.x()-r,lastPoint.y()-r,2*r,2*r);
}

void Ellipse::draw(QPainter& painter){
    if(!hasPen){
        pen=(painter.pen());
        hasPen=true;
    }
    painter.setCompositionMode(QPainter::CompositionMode_Source);
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

void Ellipse::changeSelectedWidget(QImage& image){
    QPainter painter(&image);
    if(selected){
        QPen tmppen;
        tmppen.setWidth(3);
        tmppen.setStyle(Qt::CustomDashLine);
        tmppen.setDashPattern({5,5});
        tmppen.setColor([this](){
            int luminance = qGray(this->pen.color().rgb());
            // 简单阈值（通常取128，但可根据需要调整）
            return luminance > 128 ? Qt::black : Qt::white;
        }());
        painter.setPen(tmppen);
        painter.drawEllipse(rect.normalized());
    }
    else{
        painter.setPen(pen);
        painter.drawEllipse(rect.normalized());
    }
}

Line::Line(const QPoint& lastPoint,const QPoint& nowPoint):Shapes(LINE,lastPoint,nowPoint)
{
    rect=QRect(lastPoint,nowPoint);
}

void Line::draw(QPainter& painter){
    if(!hasPen){
        pen=(painter.pen());
        hasPen=true;
    }
    painter.setCompositionMode(QPainter::CompositionMode_Source);
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

void Line::changeSelectedWidget(QImage& image){
    QPainter painter(&image);
    if(selected){
        QPen tmppen;
        tmppen.setWidth(3);
        tmppen.setStyle(Qt::CustomDashLine);
        tmppen.setDashPattern({5,5});
        tmppen.setColor([this](){
            int luminance = qGray(this->pen.color().rgb());
            // 简单阈值（通常取128，但可根据需要调整）
            return luminance > 128 ? Qt::black : Qt::white;
        }());
        painter.setPen(tmppen);
        painter.drawLine(lastPoint,nowPoint);
    }
    else{
        painter.setPen(pen);
        painter.drawLine(lastPoint,nowPoint);
    }
}
