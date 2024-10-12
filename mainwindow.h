#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CentralWidget.h"
// #include "DataInfo/MusicInfo.h"
#include "Service/DataBaseSerice.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Service/PlayerController.h"
#include "UI/ClickedEventFilter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CentralWidget *centarlWidget;

    bool isDragging;
    bool isShowMaximized = false;
    QPoint lastDraggedPos;

    // QMediaPlayer *mediaPlayer;
    // QAudioOutput *audioOutput;

    PlayerController *playerController;


    // DataBaseSerice<MusicInfo> *dbService;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void ObjectInit();
    void WidgetInit();
    void TitleBarInit();
    void SelectBarInit();
    void MainWidgetInit();
    void LoadStyleSheet();

protected:
    virtual bool event(QEvent *event) override;
};

#endif // MAINWINDOW_H
