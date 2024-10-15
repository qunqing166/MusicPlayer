#include "mainwindow.h"
#include <qfile.h>
#include <qdebug.h>
#include <QPainter>
#include <QDockWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
// #include "DataInfo/MusicInfo.h"
// #include "Service/MusicInfoService.h"
#include "Service/DataBaseSerice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    this->setMinimumSize(1000, 700);

    // setAttribute(Qt::WA_TransparentForMouseEvents, true);

    LoadStyleSheet();
    ObjectInit();
    WidgetInit();
    // this->setWindowFlag(Qt::FramelessWindowHint);
    // this->setAttribute(Qt::WA_StyledBackground);
    // this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明化
    // this->setContentsMargins(QMargins(0,0,0,0));

    connect(centarlWidget, &CentralWidget::Maximize, this, [&](){
        if(isShowMaximized)
            this->showNormal();
        else
            this->showMaximized();
        isShowMaximized = !isShowMaximized;
    });
    connect(centarlWidget, &CentralWidget::Minimize, this, [&](){this->showMinimized();});

    // connect(centarlWidget->getMainWidget()->getContentView()->getPlayListView(), &PlayListView::PlayMusic,
    //         playerController, &PlayerController::OpenNewMusic);
    connect(centarlWidget->getPlayerBar(), &PlayerBar::PlayStatusChanged,
            playerController, &PlayerController::ChangePlayStatus);

    connect(centarlWidget->getMainWidget()->getSideBar()->getSidePlayList(), &SidePlayList::PlayMusic,
            playerController, &PlayerController::OpenNewMusic);

    connect(playerController, &PlayerController::UpdatePlayBarStatus,
            centarlWidget->getPlayerBar(), &PlayerBar::SetMusicInfo);

    connect(playerController->MediaPlayer(), &QMediaPlayer::positionChanged,
            centarlWidget->getPlayerBar(), &PlayerBar::OnDurationChanged);
    // connect(centarlWidget->getPlayerBar(), &PlayerBar::PlayStatusChanged, this, [&]());
    // connect(centarlWidget->getPlayerBar())

    timer = new QTimer(this);
    // timer->setInterval(1000);
    // timer->start();
    // connect(timer, &QTimer::timeout, this, [&](){LoadStyleSheet();qDebug()<<"timerout";});
}

MainWindow::~MainWindow()
{}

void MainWindow::ObjectInit()
{
    centarlWidget = new CentralWidget(this);
    playerController = new PlayerController(this);
}

void MainWindow::WidgetInit()
{
    this->setCentralWidget(centarlWidget);
}

void MainWindow::TitleBarInit()
{

}

void MainWindow::LoadStyleSheet()
{
    QFile file(":/qss/styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        this->setStyleSheet(styleSheet);
    }
}


bool MainWindow::event(QEvent *event)
{
    // event->accept();
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        if(centarlWidget->IsInTitleBar(me->pos()))
        {
            isDragging = true;
            lastDraggedPos = me->globalPosition().toPoint();
        }
        else
            isDragging = false;
    }
    else if(event->type() == QEvent::MouseMove)
    {
        if(isDragging)
        {
            QMouseEvent *me = static_cast<QMouseEvent*>(event);
            QPoint dPos = me->globalPosition().toPoint() - lastDraggedPos;
            lastDraggedPos = me->globalPosition().toPoint();
            this->move(this->pos() + dPos);
            qDebug()<<dPos;
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        isDragging = false;
    }

    return QWidget::event(event);
}

// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     QPainter painter(this);

//     QPen pen;
//     pen.setWidth(2);
//     painter.setBrush(Qt::white);
//     painter.setPen(pen);

//     painter.setRenderHint(QPainter::SmoothPixmapTransform);
//     int radius = 15;
//     painter.drawRoundedRect(this->rect(), radius, radius);
// }
