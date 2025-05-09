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
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);

    setMouseTracking(true);
    this->statusBar()->show();
    this->setWindowTitle("绘图小程序");
    setWindowState(Qt::WindowMaximized);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 左侧面板
    QWidget *leftPanel = new QWidget(centralWidget);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(5, 5, 5, 5);

    QSlider *sizeSlider = new QSlider(Qt::Vertical, leftPanel);
    sizeSlider->setRange(1, 50);
    sizeSlider->setValue(3);
    leftLayout->addWidget(sizeSlider);

    // 滑块样式
    sizeSlider->setStyleSheet(R"(
        QSlider::groove:vertical {
            background: #E0E0E0;
            width: 6px;
            border-radius: 3px;
        }
        QSlider::handle:vertical {
            background: #2196F3;
            height: 16px;
            margin: 0 -5px;
            border-radius: 8px;
        }
    )");

    // 创建绘图区域和滚动条
    DrawingWidget *drawwidget = new DrawingWidget(centralWidget);

    QScrollBar *hScrollBar = new QScrollBar(Qt::Horizontal, centralWidget);
    hScrollBar->setMaximum(1000);
    hScrollBar->setMinimum(0);
    hScrollBar->setPageStep(1000);
    QScrollBar *vScrollBar = new QScrollBar(Qt::Vertical, centralWidget);
    vScrollBar->setMaximum(1000);
    vScrollBar->setMinimum(0);
    vScrollBar->setPageStep(1000);

    // 右侧垂直布局 (绘图区 + 水平滚动条)
    QWidget *rightWidget = new QWidget(centralWidget);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    rightLayout->addWidget(drawwidget, 1); // 绘图区占主要空间
    rightLayout->addWidget(hScrollBar, 0); // 水平滚动条

    // 将组件添加到主水平布局
    mainLayout->addWidget(leftPanel, 0);     // 左侧面板
    mainLayout->addWidget(rightWidget, 1);   // 右侧区域(绘图区+水平滚动条)
    mainLayout->addWidget(vScrollBar, 0);

    connect(sizeSlider, &QSlider::valueChanged,drawwidget, [drawwidget](int value) {
        drawwidget->pen->setSize(value);
    });
    connect(hScrollBar,&QScrollBar::valueChanged,drawwidget,[drawwidget,hScrollBar](int value){
        double ratio = static_cast<double>(value) / static_cast<double>(hScrollBar->maximum()-hScrollBar->minimum());
        drawwidget->handleHorizontalScroll(ratio);
    });
    connect(vScrollBar,&QScrollBar::valueChanged,drawwidget,[drawwidget,vScrollBar](int value){
        double ratio = static_cast<double>(value) / static_cast<double>(vScrollBar->maximum()-vScrollBar->minimum());
        drawwidget->handleVerticalScroll(ratio);
    });
    connect(drawwidget, &DrawingWidget::pageStepRatio, this, [vScrollBar, hScrollBar](double ratioH, double ratioV) {
        // 根据水平和垂直比例设置滚动条的pageStep
        int maxH = hScrollBar->maximum() - hScrollBar->minimum();
        int maxV = vScrollBar->maximum() - vScrollBar->minimum();
        hScrollBar->setPageStep(qMax(1, static_cast<int>(maxH * ratioH)));
        vScrollBar->setPageStep(qMax(1, static_cast<int>(maxV * ratioV)));
    });
    connect(drawwidget, &DrawingWidget::pagePos, this, [vScrollBar, hScrollBar](double ratioH, double ratioV) {
        // 根据水平和垂直比例设置滚动条的pageStep
        hScrollBar->blockSignals(true);
        vScrollBar->blockSignals(true);
        int maxH = hScrollBar->maximum() - hScrollBar->minimum();
        int maxV = vScrollBar->maximum() - vScrollBar->minimum();
        hScrollBar->setValue(static_cast<int>(maxH * ratioH));
        vScrollBar->setValue(static_cast<int>(maxV * ratioV));
        hScrollBar->blockSignals(false);
        vScrollBar->blockSignals(false);
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
    //rectangleAction->setShortcut(QKeySequence("Ctrl+R"));
    rectangleAction->setToolTip("矩形");
    rectangleAction->setStatusTip("切换到矩形");

    QAction *circleAction = new QAction(QIcon(":/icons/circle.png"), "圆 (C)", this);
    //circleAction->setShortcut(QKeySequence("Ctrl+S"));
    circleAction->setToolTip("圆");
    circleAction->setStatusTip("切换到圆");

    QAction *lineAction = new QAction(QIcon(":/icons/line.png"), "直线 (L)", this);
    //lineAction->setShortcut(QKeySequence("Ctrl+L"));
    lineAction->setToolTip("直线");
    lineAction->setStatusTip("切换到直线");

    QAction *paintAction = new QAction(QIcon(":/icons/paint.png"), "填充 (B)", this);
    paintAction->setShortcut(QKeySequence("Ctrl+B"));
    paintAction->setToolTip("填充");
    paintAction->setStatusTip("切换到填充");

    toolBar->addAction(penAction);
    toolBar->addAction(eraserAction);
    toolBar->addAction(paintAction);
    toolBar->addAction(lineAction);
    toolBar->addAction(rectangleAction);
    toolBar->addAction(circleAction);


    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(penAction);
    toolGroup->addAction(eraserAction);
    toolGroup->addAction(rectangleAction);
    toolGroup->addAction(circleAction);
    toolGroup->addAction(lineAction);
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
    connect(lineAction, &QAction::triggered,lineAction, [drawwidget]() {
        drawwidget->pen->setMode(4);
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

void MainWindow::newActionSlot()
{
    QWidget *centralWidget = this->centralWidget();
    QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (mainLayout) {
        for (int i = 0; i < mainLayout->count(); ++i) {
            QLayoutItem *item = mainLayout->itemAt(i);
            DrawingWidget *drawwidget = qobject_cast<DrawingWidget*>(item->widget());
            if (drawwidget) {
                drawwidget->clear();
                break;
            }
        }
    }
    this->setWindowTitle("新建画布");
}

void MainWindow::openActionSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个文件",
                                                    QCoreApplication::applicationFilePath(),
                                                    "Images (*.png *.xpm *.jpg)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else {
        QWidget *centralWidget = this->centralWidget();
        QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
        if (mainLayout) {
            for (int i = 0; i < mainLayout->count(); ++i) {
                QLayoutItem *item = mainLayout->itemAt(i);
                DrawingWidget *drawwidget = qobject_cast<DrawingWidget*>(item->widget());
                if (drawwidget) {
                    QImage image(fileName);
                    if (!image.isNull()) {
                        drawwidget->setBackgroundImage(image);
                        drawwidget->setDrawingImage(drawwidget->size());
                        drawwidget->clearDrawingImage();
                        drawwidget->update();
                        this->setWindowTitle("打开文件: " + fileName);
                    } else {
                        QMessageBox::warning(this, "警告", "无法打开文件");
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::saveActionSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件",
                                                    QCoreApplication::applicationFilePath(),
                                                    "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        QWidget *centralWidget = this->centralWidget();
        QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
        if (mainLayout) {
            for (int i = 0; i < mainLayout->count(); ++i) {
                QLayoutItem *item = mainLayout->itemAt(i);
                DrawingWidget *drawwidget = qobject_cast<DrawingWidget*>(item->widget());
                if (drawwidget) {
                    QImage combinedImage(drawwidget->size(), QImage::Format_ARGB32_Premultiplied);
                    combinedImage.fill(Qt::transparent);
                    QPainter painter(&combinedImage);
                    painter.drawImage(0, 0, drawwidget->getBackgroundImage());
                    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                    painter.drawImage(0, 0, drawwidget->getDrawingImage());
                    if (combinedImage.save(fileName)) {
                        QMessageBox::information(this, "提示", "文件保存成功");
                        this->setWindowTitle("保存文件: " + fileName);
                    } else {
                        QMessageBox::warning(this, "警告", "文件保存失败");
                    }
                    break;
                }
            }
        }
    }
}
