#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
#include "drawingtoolbar.h"
#include "startwidget.h"
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
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //开始界面
    startPage = new StartWidget(this);
    setCentralWidget(startPage);

    // 连接开始界面的信号到主窗口的槽
    connect(startPage, &StartWidget::newCanvasRequested, this, &MainWindow::onNewCanvasRequested);
    connect(startPage, &StartWidget::openFileRequested, this, &MainWindow::onOpenFileRequested);

    // 菜单栏
    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);

    setMouseTracking(true);
    this->setWindowTitle("未名画板");
    resize(1000, 600);
    ui->menubar->setVisible(false);
    ui->statusbar->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{
    if (drawwidget) {
        drawwidget->clear();
        qDebug("新建画布成功");
        this->setWindowTitle("新建画布");
    }else{
        qDebug("新建画布失败");
    }
}

void MainWindow::openActionSlot(bool firstTimeOpen = false)
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "选择一个文件",
        QDir::homePath(),
        "Images (*.png *.xpm *.jpg *.jpeg)"
        );

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
        return;
    }

    if (drawwidget) {
        if (firstTimeOpen) setupDrawingPage();
        QImage image(fileName);
        if (!image.isNull()) {
            drawwidget->setBackgroundImage(image, true);
            drawwidget->update();
            this->setWindowTitle("打开文件: " + fileName);
            ui->statusbar->setVisible(true);
            ui->menubar->setVisible(true);

            double scaleFactor = 0.5; // 缩放比例
            QSize scaledSize = image.size() * scaleFactor;
            scaledSize.setHeight(toolbarHeight + scaledSize.height());
            this->resize(scaledSize);

            // QScrollBar* hScroll = ui->horizontalScrollBar;
            // QScrollBar* vScroll = ui->verticalScrollBar;
            // hScroll->setMaximum(image.width() - drawwidget->width());
            // vScroll->setMaximum(image.height() - drawwidget->height());
        } else {
            QMessageBox::warning(this, "警告", "无法打开文件: " + fileName);
        }
    }
}

void MainWindow::saveActionSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    "Images (*.png *.xpm *.jpg)");
    if (fileName.isEmpty()) {
        return;
    }

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
            QMessageBox::warning(this, "警告", "文件保存失败，可能是文件权限问题或磁盘空间不足。");
        }
    } else {
        QMessageBox::warning(this, "警告", "绘图部件不存在，无法保存文件。");
    }
}

void MainWindow::onNewCanvasRequested(){
    ui->statusbar->setVisible(true);
    ui->menubar->setVisible(true);
    setWindowState(Qt::WindowMaximized);
    setupDrawingPage();
    newActionSlot();
}

void MainWindow::onOpenFileRequested(){
    // setupDrawingPage();
    openActionSlot(true);
}

void MainWindow::setupDrawingPage(){
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
    sizeSlider->setRange(2, 75);
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
    drawwidget = new DrawingWidget(centralWidget);

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

    connect(hScrollBar, &QScrollBar::valueChanged, drawwidget, [this, hScrollBar](int value) {
        double ratio = static_cast<double>(value) / static_cast<double>(hScrollBar->maximum() - hScrollBar->minimum());
        this->drawwidget->handleHorizontalScroll(ratio);
    });
    connect(vScrollBar, &QScrollBar::valueChanged, drawwidget, [this, vScrollBar](int value) {
        double ratio = static_cast<double>(value) / static_cast<double>(vScrollBar->maximum() - vScrollBar->minimum());
        this->drawwidget->handleVerticalScroll(ratio);
    });
    connect(drawwidget, &DrawingWidget::pageStepRatio, this, [vScrollBar, hScrollBar](double ratioH, double ratioV) {
        int maxH = hScrollBar->maximum() - hScrollBar->minimum();
        int maxV = vScrollBar->maximum() - vScrollBar->minimum();
        hScrollBar->setPageStep(qMax(1, static_cast<int>(maxH * ratioH)));
        vScrollBar->setPageStep(qMax(1, static_cast<int>(maxV * ratioV)));
    });
    connect(drawwidget, &DrawingWidget::pagePos, this, [vScrollBar, hScrollBar](double ratioH, double ratioV) {
        hScrollBar->blockSignals(true);
        vScrollBar->blockSignals(true);
        int maxH = hScrollBar->maximum() - hScrollBar->minimum();
        int maxV = vScrollBar->maximum() - vScrollBar->minimum();
        hScrollBar->setValue(static_cast<int>(maxH * ratioH));
        vScrollBar->setValue(static_cast<int>(maxV * ratioV));
        hScrollBar->blockSignals(false);
        vScrollBar->blockSignals(false);
    });
    connect(sizeSlider, &QSlider::valueChanged, sizeSlider, [this](int value) {
        drawwidget->pen->setSize(value);
        drawwidget->pen->setTextSize(value * 5); // 设置文本字体大小
    });
    // 使用自定义工具栏
    DrawingToolBar *toolBar = new DrawingToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);
    toolBar->setupTools(drawwidget);
    drawwidget->toolBar = toolBar;
    toolbarHeight = toolBar->sizeHint().height();

    QImage badgeImage(":/icons/pku.png"); // 加载北大特色贴图
    drawwidget->pen->setBadgeImage(badgeImage);
}
