#include "drawingtoolbar.h"
#include "drawingwidget.h"
#include <QAction>
#include <QIcon>

DrawingToolBar::DrawingToolBar(QWidget *parent) : QToolBar(parent)
{
    setWindowTitle("绘图工具栏");

    // 创建工具组
    toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true);
}

void DrawingToolBar::setupTools(DrawingWidget *drawingWidget)
{
    // 添加工具按钮
    QAction *penAction = new QAction(QIcon(":/icons/pen.png"), "铅笔 (P)", this);
    penAction->setShortcut(QKeySequence("Ctrl+P"));
    penAction->setToolTip("铅笔");
    penAction->setStatusTip("切换到铅笔");
    penAction->setCheckable(true);
    penAction->setData(0); // 铅笔模式

    QAction *eraserAction = new QAction(QIcon(":/icons/eraser.png"), "橡皮擦 (E)", this);
    eraserAction->setShortcut(QKeySequence("Ctrl+E"));
    eraserAction->setToolTip("橡皮擦");
    eraserAction->setStatusTip("切换到橡皮擦");
    eraserAction->setCheckable(true);
    eraserAction->setData(1); // 橡皮擦模式

    QAction *rectangleAction = new QAction(QIcon(":/icons/rectangle.png"), "矩形 (R)", this);
    rectangleAction->setToolTip("矩形");
    rectangleAction->setStatusTip("切换到矩形");
    rectangleAction->setCheckable(true);
    rectangleAction->setData(2); // 矩形模式

    QAction *circleAction = new QAction(QIcon(":/icons/circle.png"), "圆 (C)", this);
    circleAction->setToolTip("圆");
    circleAction->setStatusTip("切换到圆");
    circleAction->setCheckable(true);
    circleAction->setData(3); // 圆形模式

    QAction *lineAction = new QAction(QIcon(":/icons/line.png"), "直线 (L)", this);
    lineAction->setToolTip("直线");
    lineAction->setStatusTip("切换到直线");
    lineAction->setCheckable(true);
    lineAction->setData(4); // 直线模式

    QAction *paintAction = new QAction(QIcon(":/icons/paint.png"), "填充 (B)", this);
    paintAction->setShortcut(QKeySequence("Ctrl+B"));
    paintAction->setToolTip("填充");
    paintAction->setStatusTip("切换到填充");
    paintAction->setCheckable(true);
    paintAction->setData(5); // 填充模式

    // 添加动作到工具栏和动作组
    addAction(penAction);
    addAction(eraserAction);
    addAction(paintAction);
    addAction(lineAction);
    addAction(rectangleAction);
    addAction(circleAction);

    toolGroup->addAction(penAction);
    toolGroup->addAction(eraserAction);
    toolGroup->addAction(rectangleAction);
    toolGroup->addAction(circleAction);
    toolGroup->addAction(lineAction);
    toolGroup->addAction(paintAction);

    // 默认选中铅笔
    penAction->setChecked(true);

    // 连接工具切换信号
    connect(toolGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        emit toolModeChanged(action->data().toInt());
    });

    addSeparator();

    // 颜色选择动作
    colorAction = new QAction(QIcon(":/icons/color.png"), "颜色", this);
    colorAction->setToolTip("选择画笔颜色");
    addAction(colorAction);

    // 连接颜色选择信号
    connect(colorAction, &QAction::triggered, this, &DrawingToolBar::onColorSelected);

    // 连接工具栏信号到绘图控件
    connect(this, &DrawingToolBar::colorChanged, drawingWidget->pen, &DrawingTools::setColor);
    connect(this, &DrawingToolBar::toolModeChanged, drawingWidget->pen, &DrawingTools::setMode);
}

void DrawingToolBar::onColorSelected()
{
    QColor newColor = QColorDialog::getColor(Qt::white, this, "选择颜色");
    if (newColor.isValid()) {
        emit colorChanged(newColor);
    }
}
