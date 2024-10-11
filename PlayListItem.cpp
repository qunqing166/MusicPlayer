#include "PlayListItem.h"
#include <QHBoxLayout>

MusicInfo PlayListItem::getMusicInfo() const
{
    return musicInfo;
}

PlayListItem::PlayListItem(MusicInfo value, QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->musicInfo = value;
    ObjectInit();
    WidgetInit();
}

void PlayListItem::ObjectInit()
{
    static int id = 1;
    int height = 40;
    index = new QLabel(this);
    index->setText(QString::number(id));
    index->setFixedSize(25, height);
    id++;
    image = new ImageLabel(this);
    image->setFixedSize(height, height);
    // image->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"));
    image->SetPixmap(this->musicInfo.coverImagePath);

    songName = new QLabel(this);
    // songName->setText("liyue 璃月");
    songName->setText(this->musicInfo.musicName);

    singers = new QLabel(this);
    // singers->setText("陈致逸, mihoyo");
    singers->setText(this->musicInfo.singers);

    album = new QLabel(this);
    // album->setText("皎月云间之梦");
    album->setText(this->musicInfo.album);

    duration = new QLabel(this);
    // duration->setText("04:00");
    duration->setText(this->musicInfo.duration.toString("mm:ss"));

    pbMore = new QPushButton(this);
    pbMore->setFixedSize(height, height);
    // pbMore->setIcon(QIcon(":/scr/icon/more.png"));
    pbMore->setIcon(QIcon(this->musicInfo.musicPath));
}

void PlayListItem::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);

    hLayout->addWidget(index);
    hLayout->addWidget(image);
    hLayout->addWidget(songName, 3);
    hLayout->addWidget(singers, 2);
    hLayout->addWidget(album, 2);
    hLayout->addWidget(duration, 1);
    hLayout->addWidget(pbMore, 1);
}


