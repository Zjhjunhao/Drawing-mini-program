#ifndef DRAWINGTOOLBAR_H
#define DRAWINGTOOLBAR_H

#include "qframe.h"
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
    QWidget* createColorPalette();
    void setSelectedTool(int mode, QColor newColor);
    void updateCurrentColorIndicator(QFrame* indicatorFrame);

signals:
    void colorChanged(const QColor &color);
    void toolModeChanged(int mode);
    void penSizeChanged(int size);
    void shapeDeleted();



private slots:
    void onColorSelected();

private:
    QActionGroup *toolGroup;
    QAction *colorAction;
    QColor currentColor;
    QAction *deleteAction;
};

#endif // DRAWINGTOOLBAR_H
