#include "drawingtoolbar.h"
#include "drawingwidget.h"
#include <QAction>
#include <QIcon>
#include <QColorDialog>
#include <QToolButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>

DrawingToolBar::DrawingToolBar(QWidget *parent) : QToolBar(parent)
{
    setWindowTitle("绘图工具栏");

    //创建工具组
    toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true);
}

void DrawingToolBar::setupTools(DrawingWidget *drawingWidget)
{
    //添加工具按钮
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

    QAction *selectAction = new QAction(QIcon(":/icons/move.png"), "选择", this);
    selectAction->setToolTip("选择");
    selectAction->setStatusTip("切换到选择");
    selectAction->setCheckable(true);
    selectAction->setData(6); // 选择模式

    QAction *strawAction = new QAction(QIcon(":/icons/straw.png"), "着色器", this);
    strawAction->setToolTip("着色器");
    strawAction->setStatusTip("切换到着色器");
    strawAction->setCheckable(true);
    strawAction->setData(7); // 着色器模式

    QAction *textAction = new QAction(QIcon(":/icons/text.png"), "文本框", this);
    textAction->setToolTip("文本框");
    textAction->setStatusTip("切换到文本框");
    textAction->setCheckable(true);
    textAction->setData(8); // 文本框模式

    QAction *badgeAction = new QAction(QIcon(":/icons/pku.png"), "北大特色贴图", this);
    badgeAction->setToolTip("北大校徽");
    badgeAction->setStatusTip("切换到北大校徽");
    badgeAction->setCheckable(true);
    badgeAction->setData(9); // 校徽

    //添加动作
    addAction(penAction);
    addAction(eraserAction);
    addAction(paintAction);
    addAction(strawAction);
    addAction(textAction);
    addAction(lineAction);
    addAction(rectangleAction);
    addAction(circleAction);
    addAction(selectAction);
    addAction(badgeAction);

    toolGroup->addAction(penAction);
    toolGroup->addAction(eraserAction);
    toolGroup->addAction(strawAction);
    toolGroup->addAction(textAction);
    toolGroup->addAction(rectangleAction);
    toolGroup->addAction(circleAction);
    toolGroup->addAction(lineAction);
    toolGroup->addAction(paintAction);
    toolGroup->addAction(selectAction);
    toolGroup->addAction(badgeAction);

    //默认选中铅笔
    penAction->setChecked(true);

    //连接工具切换信号
    connect(toolGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        emit toolModeChanged(action->data().toInt());
    });

    // 设置固定宽度作为间隔
    QWidget* spacer = new QWidget(this);
    spacer->setFixedWidth(20);


    //添加基本颜色选择按钮
    addSeparator();

    addWidget(spacer);

    QFrame* indicatorFrame = new QFrame(this);
    indicatorFrame->setFrameShape(QFrame::Box);
    indicatorFrame->setFixedSize(25, 25);
    indicatorFrame->setLineWidth(2);

    //设置初始颜色
    updateCurrentColorIndicator(indicatorFrame);

    //连接颜色变化信号，更新指示器颜色
    connect(this, &DrawingToolBar::colorChanged, this, [indicatorFrame, this]() {
        updateCurrentColorIndicator(indicatorFrame);
    });
    addWidget(indicatorFrame);

    //添加空隙

    addWidget(spacer);

    addWidget(createColorPalette());

    addSeparator();

    //颜色选择动作
    colorAction = new QAction(QIcon(":/icons/color.png"), "颜色", this);
    colorAction->setToolTip("选择画笔颜色");
    addAction(colorAction);

    //连接颜色选择信号
    connect(colorAction, &QAction::triggered, this, &DrawingToolBar::onColorSelected);

    QWidget* spacerToEnd = new QWidget(this);
    spacerToEnd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(spacerToEnd);
    QAction *pkuIconAction = new QAction(QIcon(":/icons/pku.png"), "", this);
    pkuIconAction->setEnabled(false);
    pkuIconAction->setToolTip("北京大学");
    // connect(pkuIconAction, &QAction::triggered, this, [this]() {
    // });
    addAction(pkuIconAction);

    //连接工具栏信号到绘图控件
    connect(this, &DrawingToolBar::colorChanged, drawingWidget->pen, &DrawingTools::setColor);
    connect(this, &DrawingToolBar::toolModeChanged, drawingWidget->pen, &DrawingTools::setMode);
    setIconSize(QSize{32,32});

    // 工具栏背景
    // QString styleSheet = "QToolBar {"
    //                               "    background-image: url(:/icons/background.png);"
    //                               "    background-repeat: repeat-x;"
    //                               "    background-position: 0 -1000px;"
    //                               "}";
    // setStyleSheet(styleSheet);


}

void DrawingToolBar::updateCurrentColorIndicator(QFrame* indicatorFrame)
{
    // 设置颜色指示器的背景色
    QString styleSheet = QString("background-color: %1;").arg(currentColor.name());
    indicatorFrame->setStyleSheet(styleSheet);
    indicatorFrame->setToolTip(QString("当前颜色: %1").arg(currentColor.name()));
}

QWidget* DrawingToolBar::createColorPalette()
{
    QWidget* paletteWidget = new QWidget(this);
    //QHBoxLayout* layout = new QHBoxLayout(paletteWidget);
    QGridLayout* layout = new QGridLayout(paletteWidget);
    layout->setContentsMargins(8, 5, 8, 5);
    layout->setSpacing(4);

    //创建颜色按钮组
    QButtonGroup* colorButtonGroup = new QButtonGroup(this);
    colorButtonGroup->setExclusive(true);

    //定义基本颜色列表
    QList<QColor> basicColors = {
        Qt::black, Qt::white, Qt::red, Qt::green, Qt::blue,
        Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkGray,
        Qt::lightGray, QColor(255, 165, 0), // 橙色
        QColor(128, 0, 128), // 紫色
        QColor(255, 192, 203) // 粉色
    };

    //创建颜色按钮
    // for (const QColor& color : basicColors) {
    //     QToolButton* colorButton = new QToolButton(paletteWidget);
    //     colorButton->setFixedSize(25, 25);
    //     colorButton->setCheckable(true);
    //     colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(color.name()));
    //     colorButton->setToolTip(color.name());
    //     QString colorName = color.name();
    //     colorButton->setStatusTip(QString("切换到%1").arg(colorName));

    //     // 存储颜色信息
    //     colorButton->setProperty("color", color);

    //     // 添加到布局和按钮组
    //     layout->addWidget(colorButton);
    //     colorButtonGroup->addButton(colorButton);

    //     // 连接按钮点击事件
    //     connect(colorButton, &QToolButton::clicked, this, [this, colorButton]() {
    //         QColor selectedColor = colorButton->property("color").value<QColor>();
    //         currentColor = selectedColor;
    //         emit colorChanged(selectedColor);
    //     });
    // }
    int colorsPerRow = (basicColors.size() + 1) / 2;

    for (int i = 0; i < basicColors.size(); ++i) {
        const QColor& color = basicColors[i];
        QToolButton* colorButton = new QToolButton(paletteWidget);
        colorButton->setFixedSize(20, 20);
        colorButton->setCheckable(true);
        //colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(color.name()));
        QString styleSheet = QString(
                                 "QToolButton {"
                                 "    background-color: %1;"
                                 "    border: 1px solid #888;"
                                 "    border-radius: 3px;"
                                 "}"
                                 "QToolButton:checked {"
                                 "    border: 2px solid #333;"
                                 "}"
                                 "QToolButton:hover {"
                                 "    border: 2px solid #555;"
                                 "    transform: scale(1.1);"
                                 "}"
                                 ).arg(color.name());
        colorButton->setStyleSheet(styleSheet);
        colorButton->setToolTip(color.name());
        colorButton->setStatusTip(QString("切换到%1").arg(color.name()));

        colorButton->setProperty("color", color);

        int row = i / colorsPerRow;
        int col = i % colorsPerRow;

        //添加到布局和按钮组
        layout->addWidget(colorButton, row, col);
        colorButtonGroup->addButton(colorButton);

        //连接按钮点击事件
        connect(colorButton, &QToolButton::clicked, this, [this, colorButton]() {
            QColor selectedColor = colorButton->property("color").value<QColor>();
            currentColor = selectedColor;
            emit colorChanged(selectedColor);
        });
    }
    return paletteWidget;
}

void DrawingToolBar::onColorSelected()
{
    QColor newColor = QColorDialog::getColor(currentColor, this, "选择颜色");
    if (newColor.isValid()) {
        currentColor = newColor;
        emit colorChanged(newColor);
    }
}

//得到mode的工具并高亮其图标
void DrawingToolBar::setSelectedTool(int mode, QColor newColor)
{
    currentColor = newColor;
    emit colorChanged(newColor);
    foreach (QAction* action, toolGroup->actions()) {
        if (action->data().toInt() == mode) {
            action->setChecked(true);
            break;
        }
    }
}
