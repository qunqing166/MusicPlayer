#include "SidePlayListBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include "SidePlayList.h"

int SidePlayListBar::getDWidth() const
{
    return dWidth;
}

void SidePlayListBar::setDWidth(int newWidth)
{
    dWidth = newWidth;
    this->move(QPoint(parentGeo.width() - dWidth, 5));
    // qDebug()<<dWidth;
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

    connect(pbRecord, &QPushButton::clicked, this, &SidePlayListBar::OnPbRecordClicked);

    connect(pbCrt, &QPushButton::clicked, this, &SidePlayListBar::OnPbCrtClicked);
}

void SidePlayListBar::Open(QRect geo)
{
    //移至最上层
    this->raise();
    //获取父窗口数据, 根据父窗口设置height, 并启动动画
    this->parentGeo = geo;
    this->setFixedHeight(parentGeo.height() - 5);
    geoAnima->setStartValue(0);
    geoAnima->setEndValue(maxWidth);
    this->show();
    geoAnima->start();
}

void SidePlayListBar::ObjectInit()
{
    pbClose = new QPushButton(this);
    pbClose->setIcon(QIcon(":/scr/icon/close.png"));
    geoAnima = new QPropertyAnimation(this, "DWidth");
    geoAnima->startTimer(1000);
    clickFilter = new ClickedEventFilter(this);
    sidePlayList = new SidePlayList(this);
}

void SidePlayListBar::WidgetInit()
{
    int size = 40;
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("side_bar_title");
    hLayout1->addWidget(widget);

    pbClose->setFixedSize(size, size);
    pbClose->setObjectName("side_bar_btn_close");
    hLayout1->addWidget(pbClose);

    QHBoxLayout *hLayout1_1 = new QHBoxLayout(this);
    hLayout1_1->setContentsMargins(5,5,5,5);
    widget->setLayout(hLayout1_1);

    pbCrt = new QPushButton("当前播放", this);
    pbCrt->setFixedHeight(size - 10);
    pbCrt->setCheckable(true);
    pbCrt->setChecked(true);

    pbRecord = new QPushButton("播放历史", this);
    pbRecord->setFixedHeight(size - 10);
    pbRecord->setObjectName("side_bar_button_1");
    pbCrt->setObjectName("side_bar_button_1");
    hLayout1_1->addWidget(pbCrt);
    hLayout1_1->addWidget(pbRecord);

    QLabel *labelNumber = new QLabel("总共0首", this);
    QPushButton *pbClear = new QPushButton("清空列表", this);

    pbClear->setObjectName("side_bar_btn_clear");

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    hLayout2->addWidget(labelNumber);
    hLayout2->addWidget(pbClear);
    vLayout->addLayout(hLayout2);

    vLayout->addWidget(sidePlayList);

    //阴影
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(200, 200, 200));
    this->setGraphicsEffect(shadowEffect);
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

void SidePlayListBar::OnPbRecordClicked()
{
    pbCrt->setChecked(false);
    pbCrt->setCheckable(false);
    pbRecord->setCheckable(true);
    pbRecord->setChecked(true);
    // emit OpenRecordList("RecordPlayList");
    sidePlayList->UpdateList("RecordPlayList");
}

void SidePlayListBar::OnPbCrtClicked()
{
    pbRecord->setChecked(false);
    pbRecord->setCheckable(false);
    pbCrt->setCheckable(true);
    pbCrt->setChecked(true);
    // emit OpenRecordList("CurrentPlayList");
    sidePlayList->UpdateList("CurrentPlayList");
}

void SidePlayListBar::Close()
{
    geoAnima->setStartValue(maxWidth);
    geoAnima->setEndValue(0);
    geoAnima->start();
}

SidePlayList *SidePlayListBar::getSidePlayList() const
{
    return sidePlayList;
}

void SidePlayListBar::SetListCurrentIndex(int index)
{
    this->sidePlayList->setCurrentRow(index);
}
