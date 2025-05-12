#ifndef DRAWINGTOOLBAR_H
#define DRAWINGTOOLBAR_H

#include <QToolBar>
#include <QActionGroup>
#include <QSlider>
#include <QColorDialog>

class DrawingWidget;

class DrawingToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit DrawingToolBar(QWidget *parent = nullptr);
    void setupTools(DrawingWidget *drawingWidget);

signals:
    void colorChanged(const QColor &color);
    void toolModeChanged(int mode);
    void penSizeChanged(int size);

private slots:
    void onColorSelected();

private:
    QActionGroup *toolGroup;
    QAction *colorAction;
};

#endif // DRAWINGTOOLBAR_H
