#include "mainwindow.h"
#include "TitleBar.h"
#include "SelectBar.h"
#include <qfile.h>
#include <qdebug.h>
#include <QPainter>
#include <QDockWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    this->setMinimumSize(1000, 600);
    centarlWidget = new CentralWidget(this);
    this->setCentralWidget(centarlWidget);
    // this->setWindowFlag(Qt::FramelessWindowHint);
    // this->setAttribute(Qt::WA_StyledBackground);
    // this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明化
    // this->setContentsMargins(QMargins(0,0,0,0));
    LoadStyleSheet();
    // WidgetInit();
    // connect(centarlWidget, &CentralWidget::LocationChanged, this, [&](QPoint dPos){
    //     this->move(this->pos() + dPos);
    // });
    // QDockWidget *dockWidget = new QDockWidget(this);
    connect(centarlWidget, &CentralWidget::Maximize, this, [&](){
        if(isShowMaximized)
            this->showNormal();
        else
            this->showMaximized();
        isShowMaximized = !isShowMaximized;
    });
    connect(centarlWidget, &CentralWidget::Minimize, this, [&](){this->showMinimized();});

}

MainWindow::~MainWindow()
{}

void MainWindow::WidgetInit()
{
    hLayout_1 = new QHBoxLayout(this);
    hLayout_2 = new QHBoxLayout(this);
    vLayout = new QVBoxLayout(this);
    vLayout_2_1 = new QVBoxLayout(this);
    QWidget* mainWidget = new QWidget(this);
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(vLayout);
    // this->setLayout(vLayout);
    vLayout->addLayout(hLayout_1);
    vLayout->addLayout(hLayout_2);
    vLayout->setAlignment(Qt::AlignTop);
    SelectBar* selectBar = new SelectBar(this);
    hLayout_2->addWidget(selectBar);
    hLayout_2->addLayout(vLayout_2_1);
    TitleBar* titleBar = new TitleBar(this);
    hLayout_1->addWidget(titleBar);

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
