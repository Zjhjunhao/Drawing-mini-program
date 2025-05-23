#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "drawingtools.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include "drawingtoolbar.h"
#include <QInputDialog>

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
    DrawingToolBar *toolBar;
    void clear();
    // 添加公共访问函数
    void setBackgroundImage(const QImage& image, bool keepOriginalSize = false);
    void setDrawingImage(const QSize& size);
    void clearDrawingImage();
    QImage getBackgroundImage() const;
    QImage getDrawingImage() const;
    void updateScaledImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void wheelEvent(QWheelEvent *event) override;

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
    // 形状图层
    QImage shapeImage;
    // 原始绘画图层的备份
    QImage originalImage;
    // 缩放比例
    double scaleFactor;
    // 形状列表
    std::vector<Shapes*>shapes;

    // 视口相关成员变量
    int viewportX;
    int viewportY;
    int viewportWidth;
    int viewportHeight;

    // 私有辅助函数声明
    QPoint convertToOriginalCoordinates(const QPoint& point);
    void adjustViewport();

public slots:
    // 滑动条拖动的槽函数
    void handleHorizontalScroll(double ratio);
    void handleVerticalScroll(double ratio);
    void setCurrentToolMode(int mode);

signals:
    void pageStepRatio(double ratioH,double ratioV);
    void pagePos(double ratioH, double ratioV);
    void selectedShape(Shapes* p);
};

#endif // DRAWINGWIDGET_H
