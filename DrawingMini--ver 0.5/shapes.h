#ifndef SHAPES_H
#define SHAPES_H
#include <QPainter>
#include <QDebug>
#include <QImage>

enum ShapeType { RECTANGLE, ELLIPSE, LINE, BADGE, PKUSTICKER };

class Shapes
{
protected:
    ShapeType type;
    QRectF rect;      // 图形边界
    QPoint lastPoint;
    QPoint nowPoint;
    bool selected;    // 是否选中
    bool hasPen; // 是否有对应画笔

    virtual void changeSelectedWidget(QImage& image)=0;


public:
    QPen pen;
    Shapes(ShapeType type,const QPoint& lastPoint,const QPoint& nowPoint);
    virtual void draw(QPainter& painter) = 0;
    virtual bool contains(const QPoint& point) = 0;
    virtual void move(const QPoint& last,const QPoint& now) = 0;
    virtual ~Shapes()=default;
    void setSelected(bool select,QImage& image);
    bool isSelected();
};

class Rectangle:public Shapes
{
public:
    Rectangle(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
    void changeSelectedWidget(QImage& image);
};

class Ellipse:public Shapes
{
public:
    Ellipse(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
    void changeSelectedWidget(QImage& image);
};

class Line:public Shapes
{
public:
    Line(const QPoint& lastPoint,const QPoint& nowPoint);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
    void changeSelectedWidget(QImage& image);
};

class PKUSticker : public Shapes
{
public:
    PKUSticker(const QPoint& lastPoint,const QPoint& nowPoint, const QImage& stickerImage);
    void draw(QPainter& painter);
    bool contains(const QPoint& point);
    void move(const QPoint& last,const QPoint& now);
    void changeSelectedWidget(QImage& image);

private:
    QImage stickerImage;
};
#endif // SHAPES_H
