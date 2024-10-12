#include "SidePlayListBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>

int SidePlayListBar::getDWidth() const
{
    return dWidth;
}

void SidePlayListBar::setDWidth(int newWidth)
{
    dWidth = newWidth;
    this->move(QPoint(parentGeo.width() - dWidth, 0));
}

SidePlayListBar::SidePlayListBar(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(maxWidth, 500);
    this->setObjectName("widget_test");

    ObjectInit();
    WidgetInit();

    //默认关闭
    this->hide();

    //定时器结束才更新状态
    connect(geoAnima, &QPropertyAnimation::finished, this, &SidePlayListBar::OnAnimationFinished);
    //当界面显示时, 开始检测全局的鼠标事件
    connect(clickFilter, &ClickedEventFilter::MousePressed, this, &SidePlayListBar::OnMousePressed);
    //界面内的关闭按钮
    connect(pbClose, &QPushButton::clicked, this, &SidePlayListBar::Close);
}

void SidePlayListBar::Open(QRect geo)
{
    this->parentGeo = geo;
    this->setFixedHeight(parentGeo.height());
    geoAnima->setStartValue(0);
    geoAnima->setEndValue(maxWidth);
    this->show();
    geoAnima->start();
}

void SidePlayListBar::ObjectInit()
{
    pbClose = new QPushButton("X", this);
    geoAnima = new QPropertyAnimation(this, "DWidth");
    geoAnima->startTimer(1000);
    clickFilter = new ClickedEventFilter(this);
}

void SidePlayListBar::WidgetInit()
{
    int size = 30;
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("side_bar_title");
    hLayout1->addWidget(widget);

    pbClose->setFixedSize(size, size);
    hLayout1->addWidget(pbClose);
}

void SidePlayListBar::OnAnimationFinished()
{
    isOpen = !isOpen;
    if(!isOpen)
    {
        this->hide();
        qApp->removeEventFilter(clickFilter);
    }
    else
    {
        qApp->installEventFilter(clickFilter);
    }
}

void SidePlayListBar::OnMousePressed(const QPoint &pos)
{
    if(!(this->rect().contains(this->mapFromGlobal(pos))))
    {
        if(isOpen)this->Close();
    }
}

void SidePlayListBar::Open(int height)
{
    this->setFixedHeight(height);
    this->setDWidth(this->width());
    geoAnima->setStartValue(0);
    geoAnima->setEndValue(maxWidth);
    // this->show();
    geoAnima->start();
    isOpen = true;
}

void SidePlayListBar::Close()
{
    geoAnima->setStartValue(maxWidth);
    geoAnima->setEndValue(0);
    geoAnima->start();
}
