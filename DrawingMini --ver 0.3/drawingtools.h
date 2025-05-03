#ifndef DRAWINGTOOLS_H
#define DRAWINGTOOLS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>

class DrawingTools : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingTools(QWidget *parent = nullptr);
    void DrawingEvent(QImage& drawingImage,QImage& backgroundImage,
                      QMouseEvent *event,QPoint& lastPoint,int type=0);//type代表是在MousePressEvent还是MouseMoveEvent中调用的，绘制形状时有用

private:
    QColor color;
    int size;
    int mode;//0-> pencil,1->eraser,others->shapes

    QPen pen;
    QPen Pencil();
    QPen Eraser(QImage& image);
    QPen ShapePen();
    void setPen(QImage& image);

    QImage tempImage;//临时保存drawingImage,绘制形状时有用

    void ShapeDrawing(QPainter& painter,QMouseEvent *event,QPoint& lastPoint);//形状绘制

public slots:
    void setColor(QColor color);
    void setSize(int size);
    void setMode(int mode);//不同的num对应不同的画笔工具，由界面中选择按钮发出signal
};

#endif // DRAWINGTOOLS_H
