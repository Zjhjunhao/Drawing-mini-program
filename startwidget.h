#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QPushButton>
#include <QWidget>
namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

signals:
    void newCanvasRequested();
    void openFileRequested();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void updateBackground();

private:
    Ui::StartWidget *ui;
    QPushButton *newButton;
    QPushButton *openButton;
    QPixmap background;
};

#endif // STARTWIDGET_H
