#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "drawingtools.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class DrawingWidget;
}

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    ~DrawingWidget();
    // 画笔
    DrawingTools *pen;
    void clear();
    // 添加公共访问函数
    void setBackgroundImage(const QImage& image);
    void setDrawingImage(const QSize& size);
    void clearDrawingImage();
    QImage getBackgroundImage() const;
    QImage getDrawingImage() const;




protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::DrawingWidget *ui;
    // 是否画画
    bool drawing;
    // 记录鼠标坐标
    QPoint lastPoint;
    // 背景图层
    QImage backgroundImage;
    // 绘画图层
    QImage drawingImage;
};

#endif // DRAWINGWIDGET_H
