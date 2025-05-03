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
    this->setCentralWidget(centralWidget);



    //仅供调试用，实际界面中应进行修改
    //********************
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    DrawingWidget *drawwidget = new DrawingWidget(centralWidget);

    //QPushButton用于选择工具
    QButtonGroup *group = new QButtonGroup(this);
    QPushButton *penButton = new QPushButton("pencil", centralWidget);
    QPushButton *eraserButton = new QPushButton("eraser", centralWidget);
    QPushButton *rectangleButton = new QPushButton("rectangle", centralWidget);
    QPushButton *circleButton = new QPushButton("circle", centralWidget);
    group->addButton(penButton);
    group->addButton(eraserButton);
    group->addButton(rectangleButton);
    group->addButton(circleButton);
    group->setExclusive(true);
    // 连接按钮点击信号
    connect(penButton, &QPushButton::clicked,penButton, [drawwidget]() {
        drawwidget->pen->setMode(0);//pencil工具
    });
    connect(eraserButton, &QPushButton::clicked,eraserButton, [drawwidget]() {
        drawwidget->pen->setMode(1);//eraser工具
    });
    connect(rectangleButton, &QPushButton::clicked,rectangleButton, [drawwidget]() {
        drawwidget->pen->setMode(2);//rectangle工具
    });
    connect(circleButton, &QPushButton::clicked,circleButton, [drawwidget]() {
        drawwidget->pen->setMode(3);//circle工具
    });

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QString buttonStyleSheet = "QPushButton { color: black; background-color: white; }";
    penButton->setStyleSheet(buttonStyleSheet);
    eraserButton->setStyleSheet(buttonStyleSheet);
    rectangleButton->setStyleSheet(buttonStyleSheet);
    circleButton->setStyleSheet(buttonStyleSheet);

    buttonLayout->addWidget(penButton);
    buttonLayout->addWidget(eraserButton);
    buttonLayout->addWidget(rectangleButton);
    buttonLayout->addWidget(circleButton);

    // 创建 QSlider 用于调整粗细
    QSlider *sizeSlider = new QSlider(Qt::Horizontal, centralWidget);
    sizeSlider->setRange(1, 50);
    sizeSlider->setValue(3);

    // 连接滑块值改变信号到槽函数
    connect(sizeSlider, &QSlider::valueChanged,sizeSlider, [drawwidget](int value) {
        drawwidget->pen->setSize(value);
    });

    //创建QPushButton用于颜色选择
    QPushButton *colorChoose=new QPushButton("color",centralWidget);
    colorChoose->setStyleSheet(buttonStyleSheet);
    connect(colorChoose,&QPushButton::clicked,colorChoose,[drawwidget,this](){
        QColor newColor=QColorDialog::getColor(Qt::white, this);
        drawwidget->pen->setColor(newColor);
    });

    layout->addLayout(buttonLayout);
    layout->addWidget(colorChoose);
    layout->addWidget(sizeSlider);
    layout->addWidget(drawwidget);

    //********************



}

MainWindow::~MainWindow()
{
    delete ui;
}
