#ifndef SHAPES_H
#define SHAPES_H
#include <QPainter>
#include <QDebug>
#include <QImage>

enum ShapeType { RECTANGLE, ELLIPSE, LINE };

class Shapes
{
protected:
    ShapeType type;
    QRectF rect;      // 图形边界
    QPoint lastPoint;
    QPoint nowPoint;
    bool selected;    // 是否选中
    bool hasPen; // 是否有对应画笔


public:
    QPen pen;
    Shapes(ShapeType type,const QPoint& lastPoint,const QPoint& nowPoint);
    virtual void draw(QPainter& painter) = 0;
    virtual bool contains(const QPoint& point) = 0;
    virtual void move(const QPoint& last,const QPoint& now) = 0;
    virtual ~Shapes()=default;
    void setSelected();
    // void printQRectVertices() {
    //     int x = rect.x();
    //     int y = rect.y();
    //     int width = rect.width();
    //     int height = rect.height();

    //     // 左上角
    //     QPoint topLeft(x, y);
    //     // 右上角
    //     QPoint topRight(x + width - 1, y);
    //     // 左下角
    //     QPoint bottomLeft(x, y + height - 1);
    //     // 右下角
    //     QPoint bottomRight(x + width - 1, y + height - 1);

    //     qDebug() << "左上角坐标：" << topLeft;
    //     qDebug() << "右上角坐标：" << topRight;
    //     qDebug() << "左下角坐标：" << bottomLeft;
    //     qDebug() << "右下角坐标：" << bottomRight;
    // }
};

class Rectangle:public Shapes
{
public:
    Rectangle(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
};

class Ellipse:public Shapes
{
public:
    Ellipse(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
};

class Line:public Shapes
{
public:
    Line(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
};
#endif // SHAPES_H
