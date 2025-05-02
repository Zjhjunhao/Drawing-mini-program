#include "drawingtools.h"
#include <QDebug>

DrawingTools::DrawingTools() {
    this->color = Qt::black;
    this->size = 3;
    this->mode = 0; // 默认模式为铅笔
    this->pen = QPen(this->color, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QPen DrawingTools::getPen(QImage image) {
    switch (mode) {
    case 0:
        return Pencil();
    case 1:
        return Eraser(image);
    default:
        qDebug() << "Undefined type of pen";
        return this->pen;
    }
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

QPen DrawingTools::Eraser(QImage image) {
    QPen epen=QPen(Qt::transparent, this->size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    epen.setBrush(image);
    return epen;
}

void DrawingTools::setMode(int mode) {
    switch (mode) {
    case 0:
        this->mode = 0;
        break;
    case 1:
        this->mode = 1;
        break;
    default:
        qDebug() << "Undefined type of pen";
    }
}

int DrawingTools::getMode() {
    return this->mode;
}
