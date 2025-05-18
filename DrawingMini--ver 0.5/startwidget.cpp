#include "startwidget.h"
#include <QVBoxLayout>
#include <QLabel>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent),
    background(":/icons/background.png")
{
    updateBackground();

    QVBoxLayout *layout = new QVBoxLayout(this);

    // 标题
    //QLabel *titleLabel = new QLabel("绘图小程序", this);
    //titleLabel->setAlignment(Qt::AlignCenter);
    // QFont titleFont = titleLabel->font();
    // titleFont.setPointSize(24);
    // titleLabel->setFont(titleFont);

    // 按钮
    newButton = new QPushButton("新建画布", this);
    openButton = new QPushButton("打开文件", this);

    // 设置按钮样式
    QString buttonStyle = "QPushButton { padding: 10px; font-size: 16px; min-width: 150px; }";
    newButton->setStyleSheet(buttonStyle);
    openButton->setStyleSheet(buttonStyle);

    // 添加到布局
    layout->addStretch();
    //layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(newButton, 0, Qt::AlignCenter);
    layout->addWidget(openButton, 0, Qt::AlignCenter);
    layout->addStretch();

    // 连接信号
    connect(newButton, &QPushButton::clicked, this, &StartWidget::newCanvasRequested);
    connect(openButton, &QPushButton::clicked, this, &StartWidget::openFileRequested);
}

void StartWidget::updateBackground()
{
    if (!background.isNull()) {
        QPalette palette;
        // 保持比例+填充整个区域（可能裁剪）

        palette.setBrush(QPalette::Window,
                         QBrush(background.scaled(size(),
                                                    Qt::KeepAspectRatioByExpanding,
                                                    Qt::SmoothTransformation)));
        setPalette(palette);
        setAutoFillBackground(true);
    }
}

void StartWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateBackground();
}

StartWidget::~StartWidget()
{
}
