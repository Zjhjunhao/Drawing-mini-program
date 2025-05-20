#include "startwidget.h"
#include <QVBoxLayout>
#include <QLabel>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent),
    background(":/icons/background.png")
{
    updateBackground();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *leftPanel = new QWidget(this);
    leftPanel->setFixedWidth(200);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(40, 0, 0, 0);

    QLabel *verticalLabel = new QLabel("未\n名\n画\n板", leftPanel);
    verticalLabel->setAlignment(Qt::AlignCenter);
    //字体
    QFont verticalFont = verticalLabel->font();
    verticalFont.setPointSize(60);
    verticalFont.setBold(true);
    verticalLabel->setFont(verticalFont);

    //半透明背景
    verticalLabel->setStyleSheet("background-color: rgba(255, 255, 255, 128);"
                                 "border-radius: 8px;"
                                 "padding: 10px;");

    leftLayout->addWidget(verticalLabel, 0, Qt::AlignCenter);

    //按钮
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addStretch();

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    buttonLayout->setContentsMargins(20, 0, 200, 200);
    buttonLayout->setSpacing(10);

    // 按钮
    newButton = new QPushButton("新建画布", rightPanel);
    openButton = new QPushButton("打开文件", rightPanel);

    // 设置按钮样式
    QString buttonStyle = "QPushButton { padding: 10px; font-size: 16px; min-width: 150px; }";
    newButton->setStyleSheet(buttonStyle);
    openButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(openButton);
    rightLayout->addLayout(buttonLayout);
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);

    //连接信号
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
