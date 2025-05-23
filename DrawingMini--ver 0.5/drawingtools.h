#ifndef DRAWINGTOOLS_H
#define DRAWINGTOOLS_H

#include "shapes.h"

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>

class DrawingTools : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingTools(QWidget *parent = nullptr);
    void DrawingEvent(QImage& drawingImage,
                      QPoint& nowPoint,QPoint& lastPoint,int type=0);//type代表是在MousePressEvent还是MouseMoveEvent中调用的，绘制形状时有用
    void DrawingEvent(QImage& drawingImage,QImage& shapeImage,
                      QPoint& nowPoint,QPoint& lastPoint);// 重载使用橡皮时调用的函数
    int getmode();
    void ColorPicker(QImage& drawingImage,QImage& shapeImage,QPoint& nowPoint);
    QColor getColor();
    void setText(QString t);
    void setTextSize(int size); //设置文本字体大小

private:
    QColor color;
    int size;
    int mode;//0-> pencil,1->eraser,others->shapes
    QPen pen;
    QPen Pencil();
    QPen Eraser();
    QPen ShapePen();
    void setPen();
    int lastUsedMode; //记录上一次的模式
    Shapes* shape;

    QImage tempImage;//临时保存drawingImage,绘制形状时有用

    void ShapeDrawing(QPainter& painter,QPoint& nowPoint,QPoint& lastPoint);//形状绘制
    void scanLineFill(QImage &drawingImage,QImage& composedImage, QPoint& point);

    //文本框相关
    QString text;
    QPoint textPosition;
    int textSize;

public slots:
    void setColor(QColor color);
    void setSize(int size);
    void setMode(int mode);//不同的num对应不同的画笔工具，由界面中选择按钮发出signal
    void setSelectedShape(Shapes* p);

signals:
    void returnShape(Shapes* p);
    void toolModeChanged(int mode);
};

#endif // DRAWINGTOOLS_H
