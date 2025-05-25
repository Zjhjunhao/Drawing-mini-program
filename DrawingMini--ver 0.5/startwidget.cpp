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
    leftPanel->setFixedWidth(250);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(50, 0, 0, 0);

    // QLabel *verticalLabel = new QLabel("未\n名\n画\n板", leftPanel);
    // verticalLabel->setAlignment(Qt::AlignCenter);
    // //字体
    // QFont verticalFont = verticalLabel->font();
    // verticalFont.setPointSize(60);
    // verticalFont.setBold(true);
    // verticalLabel->setFont(verticalFont);

    // //半透明背景
    // verticalLabel->setStyleSheet("background-color: rgba(255, 255, 255, 128);"
    //                              "border-radius: 8px;"
    //                              "padding: 10px;");

    QLabel *imageLabel = new QLabel(leftPanel);
    QPixmap pixmap(":/icons/topic.png"); // 替换为你的图片资源路径
    pixmap = pixmap.scaled(130, 380);
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);

    imageLabel->setStyleSheet("background-color: rgba(255, 255, 255, 144);"
                                 "border-radius: 8px;"
                                  "padding: 0px;");

    leftLayout->addWidget(imageLabel, 0, Qt::AlignCenter);

    //按钮
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addStretch();

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    buttonLayout->setContentsMargins(20, 0, 200, 200);
    buttonLayout->setSpacing(25);

    // 按钮
    newButton = new QPushButton("新建画布", rightPanel);
    openButton = new QPushButton("打开文件", rightPanel);

    // 设置按钮样式
    QString buttonStyle = R"(
        QPushButton {
            padding: 10px;
            font-size: 20px;
            min-width: 150px;
            font-family: "SimHei";
            font-weight: bold;
            color: #000000;

            /* 使用RGBA格式设置带透明度的渐变 */
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 rgba(255, 255, 255, 190),
                                              stop:1 rgba(224, 224, 224, 190));

            border: 1px solid rgba(170, 170, 170, 200);
            border-radius: 5px;
            border-bottom-color: rgba(136, 136, 136, 200);
            border-right-color: rgba(136, 136, 136, 200);
            border-left-color: rgba(255, 255, 255, 200);
            border-top-color: rgba(255, 255, 255, 200);
        }

        QPushButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 rgba(245, 245, 245, 240), /* 悬停时增加不透明度 */
                                              stop:1 rgba(208, 208, 208, 240));
            color: #000000;
        }

        QPushButton:pressed {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 rgba(208, 208, 208, 220),
                                              stop:1 rgba(245, 245, 245, 220));
            border-bottom-color: rgba(255, 255, 255, 200);
            border-right-color: rgba(255, 255, 255, 200);
            border-left-color: rgba(136, 136, 136, 200);
            border-top-color: rgba(136, 136, 136, 200);
        }
    )";
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
