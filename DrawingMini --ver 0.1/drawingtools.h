#ifndef DRAWINGTOOLS_H
#define DRAWINGTOOLS_H
#include<QColor>
#include<QPainter>

class DrawingTools
{
public:
    DrawingTools();
    QPen getPen(QColor color);
    int getMode();

private:
    QColor color;
    int size;
    int mode;//0-> pencil,1->eraser,...
    QPen pen;
    QPen Pencil();
    QPen Eraser(QColor color);


public slots:
    void setColor(QColor color);
    void setSize(int size);
    void setMode(int mode);//不同的num对应不同的画笔工具，由界面中选择按钮发出signal

};

#endif // DRAWINGTOOLS_H
