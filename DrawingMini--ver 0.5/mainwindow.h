#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include "startwidget.h"
#include "drawingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int toolbarHeight;

private slots:
    void newActionSlot();   //新建文件槽函数
    void openActionSlot(bool firstTimeOpen);  //打开文件槽函数
    void saveActionSlot();  //另存为文件槽函数
    void onNewCanvasRequested();
    void onOpenFileRequested();



private:
    Ui::MainWindow *ui;
    StartWidget *startPage;
    DrawingWidget *drawwidget;
    void setupDrawingPage();
};
#endif // MAINWINDOW_H
