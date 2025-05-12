#include "startwidget.h"
#include <QVBoxLayout>
#include <QLabel>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 标题
    QLabel *titleLabel = new QLabel("绘图小程序", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleLabel->setFont(titleFont);

    // 按钮
    newButton = new QPushButton("新建画布", this);
    openButton = new QPushButton("打开文件", this);

    // 设置按钮样式
    QString buttonStyle = "QPushButton { padding: 10px; font-size: 16px; min-width: 150px; }";
    newButton->setStyleSheet(buttonStyle);
    openButton->setStyleSheet(buttonStyle);

    // 添加到布局
    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(newButton, 0, Qt::AlignCenter);
    layout->addWidget(openButton, 0, Qt::AlignCenter);
    layout->addStretch();

    // 连接信号
    connect(newButton, &QPushButton::clicked, this, &StartWidget::newCanvasRequested);
    connect(openButton, &QPushButton::clicked, this, &StartWidget::openFileRequested);
}

StartWidget::~StartWidget()
{
}
