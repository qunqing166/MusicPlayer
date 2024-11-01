#include "SidePlayListItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

SidePlayListItem::SidePlayListItem(int index, const MusicDto &info, QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    ObjectInit();
    this->SetMusicInfo(info);
    this->index->setText(QString::number(index));
    WidgetInit();
}

void SidePlayListItem::SetMusicInfo(const MusicDto &info)
{
    this->info = info;
    image->SetPixmap(info.CoverImagePath());
    musicName->setText(info.MusicName());
    singers->setText(info.Singers());
}

void SidePlayListItem::ObjectInit()
{
    index = new QLabel(this);
    index->setFixedWidth(20);
    index->setObjectName("PlayListItem_otherLabel");

    int size = 50;
    image = new ImageLabel(this, info.CoverImagePath());
    image->setFixedSize(size, size);

    musicName = new QLabel(this);
    singers = new QLabel(this);

    int buttonSize = 30;
    pbMore = new QPushButton(this);
    pbMore->setFixedSize(buttonSize, buttonSize);
    pbMore->setIcon(QIcon(":/scr/icon/more.png"));

    pbDel = new QPushButton(this);
    pbDel->setFixedSize(buttonSize, buttonSize);
    pbDel->setIcon(QIcon(":/scr/icon/close.png"));

    pbMore->setObjectName("side_list_btn");
    pbDel->setObjectName("side_list_btn");
}

void SidePlayListItem::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(10,0,10,0);
    this->setLayout(hLayout);

    hLayout->addWidget(index);
    hLayout->addWidget(image);

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    hLayout->addLayout(vLayout1);
    vLayout1->addWidget(musicName);
    vLayout1->addWidget(singers);

    hLayout->addWidget(pbMore, Qt::AlignRight);
    hLayout->addWidget(pbDel, Qt::AlignRight);
}
