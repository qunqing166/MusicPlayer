#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CentralWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QHBoxLayout* hLayout_1;
    QHBoxLayout* hLayout_2;
    QVBoxLayout* vLayout;
    QVBoxLayout* vLayout_2_1;

    CentralWidget *centarlWidget;

    bool isDragging;
    bool isShowMaximized = false;
    QPoint lastDraggedPos;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void WidgetInit();
    void TitleBarInit();
    void SelectBarInit();
    void MainWidgetInit();
    void LoadStyleSheet();

protected:
    virtual bool event(QEvent *event) override;


};

#endif // MAINWINDOW_H
