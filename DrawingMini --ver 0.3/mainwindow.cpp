#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
#include "drawingtools.h"
#include <QPainter>
#include <QStatusBar>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QColorDialog>
#include <QFile>
#include <QToolBar>
#include <QActionGroup>
#include <QLabel>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    this->statusBar()->show();
    this->setWindowTitle("绘图小程序");
    setWindowState(Qt::WindowMaximized);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);
    //将画笔粗细放到了左侧
    QWidget *leftPanel = new QWidget(centralWidget);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    DrawingWidget *drawwidget = new DrawingWidget(centralWidget);
    leftLayout->setContentsMargins(5, 5, 5, 5);

    QSlider *sizeSlider = new QSlider(Qt::Vertical, leftPanel);
    sizeSlider->setRange(1, 50);
    sizeSlider->setValue(3);
    leftLayout->addWidget(sizeSlider);

    mainLayout->addWidget(leftPanel, 0);
    mainLayout->addWidget(drawwidget, 1);

    connect(sizeSlider, &QSlider::valueChanged, sizeSlider, [drawwidget](int value) {
        drawwidget->pen->setSize(value);
    });

    //用工具栏来呈现工具
    QToolBar *toolBar = new QToolBar("主工具栏", this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction *penAction = new QAction(QIcon(":/icons/pen.png"), "铅笔 (P)", this);
    penAction->setShortcut(QKeySequence("Ctrl+P"));
    penAction->setToolTip("铅笔");
    penAction->setStatusTip("切换到铅笔");

    QAction *eraserAction = new QAction(QIcon(":/icons/eraser.png"), "橡皮擦 (E)", this);
    eraserAction->setShortcut(QKeySequence("Ctrl+E"));
    eraserAction->setToolTip("橡皮擦");
    eraserAction->setStatusTip("切换到橡皮擦");

    QAction *rectangleAction = new QAction(QIcon(":/icons/rectangle.png"), "矩形 (R)", this);
    rectangleAction->setShortcut(QKeySequence("Ctrl+R"));
    rectangleAction->setToolTip("矩形");
    rectangleAction->setStatusTip("切换到矩形");

    QAction *circleAction = new QAction(QIcon(":/icons/circle.png"), "圆 (C)", this);
    circleAction->setShortcut(QKeySequence("Ctrl+S"));
    circleAction->setToolTip("圆");
    circleAction->setStatusTip("切换到圆");

    QAction *lineAction = new QAction(QIcon(":/icons/line.png"), "直线 (L)", this);
    lineAction->setShortcut(QKeySequence("Ctrl+L"));
    lineAction->setToolTip("直线");
    lineAction->setStatusTip("切换到直线");

    QAction *blowupAction = new QAction(QIcon(":/icons/blowup.png"), "放大镜 (Z)", this);
    blowupAction->setToolTip("放大镜");
    blowupAction->setStatusTip("切换到放大镜（右键缩小）");

    QAction *paintAction = new QAction(QIcon(":/icons/paint.png"), "填充 (B)", this);
    paintAction->setShortcut(QKeySequence("Ctrl+B"));
    paintAction->setToolTip("填充");
    paintAction->setStatusTip("切换到填充");

    toolBar->addAction(penAction);
    toolBar->addAction(eraserAction);
    toolBar->addAction(paintAction);
    toolBar->addAction(blowupAction);
    toolBar->addAction(lineAction);
    toolBar->addAction(rectangleAction);
    toolBar->addAction(circleAction);


    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(penAction);
    toolGroup->addAction(eraserAction);
    toolGroup->addAction(rectangleAction);
    toolGroup->addAction(circleAction);
    toolGroup->addAction(lineAction);
    toolGroup->addAction(blowupAction);
    toolGroup->addAction(paintAction);

    connect(penAction, &QAction::triggered, penAction, [drawwidget]() {
        drawwidget->pen->setMode(0);;
    });
    connect(eraserAction, &QAction::triggered,eraserAction, [drawwidget]() {
        drawwidget->pen->setMode(1);
    });
    connect(rectangleAction, &QAction::triggered,rectangleAction, [drawwidget]() {
        drawwidget->pen->setMode(2);
    });
    connect(circleAction, &QAction::triggered,circleAction, [drawwidget]() {
        drawwidget->pen->setMode(3);
    });
    toolBar->addSeparator();  // 添加分隔线

    // 颜色选择动作
    QAction *colorAction = new QAction(QIcon(":/icons/color.png"), "颜色", this);
    colorAction->setToolTip("选择画笔颜色");
    connect(colorAction, &QAction::triggered, colorAction, [drawwidget,this]() {
        QColor newColor=QColorDialog::getColor(Qt::white, this);
        drawwidget->pen->setColor(newColor);
    });
    toolBar->addAction(colorAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
