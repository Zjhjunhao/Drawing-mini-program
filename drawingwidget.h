#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::DrawingWidget *ui;
    //是否画画
    bool drawing;
    //记录鼠标坐标
    QPoint lastPoint;
    //画布
    QImage image;
};

#endif // DRAWINGWIDGET_H
