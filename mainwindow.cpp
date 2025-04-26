#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
#include <QPainter>
#include <QStatusBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    this->statusBar()->show();
    this->setWindowTitle("绘图小程序");
    this->resize(800,600);
    DrawingWidget *drawwidget = new DrawingWidget;
    this->setCentralWidget(drawwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


