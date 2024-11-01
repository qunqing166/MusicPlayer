#include "mainwindow.h"

#include <QFile>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(1000, 700);

    LoadStyleSheet();
    ObjectInit();
    WidgetInit();

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明化

    //最大化
    connect(centarlWidget, &CentralWidget::Maximize, this, [&](){
        if(isShowMaximized)
            this->showNormal();
        else
            this->showMaximized();
        isShowMaximized = !isShowMaximized;
    });
    //最小化
    connect(centarlWidget, &CentralWidget::Minimize, this, [&](){this->showMinimized();});
}

MainWindow::~MainWindow()
{
    PlayerController::Instance()->~PlayerController();
}

void MainWindow::ObjectInit()
{
    //提前加载音乐控制器
    PlayerController::Instance();
    centarlWidget = new CentralWidget(this);
}

void MainWindow::WidgetInit()
{
    this->setCentralWidget(centarlWidget);
    this->setContentsMargins(10,10,10,10);

    //阴影
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(200, 200, 200));
    this->setGraphicsEffect(shadowEffect);
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
