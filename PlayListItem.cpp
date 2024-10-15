#include "PlayListItem.h"
#include <QHBoxLayout>

MusicDto PlayListItem::getMusicInfo() const
{
    return musicInfo;
}

PlayListItem::PlayListItem(const MusicDto &value, int index, QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->musicInfo = value;
    this->index = index;
    ObjectInit();
    WidgetInit();
}

void PlayListItem::ObjectInit()
{
    // static int id = 1;
    int height = 40;
    indexLabel = new QLabel(this);
    indexLabel->setText(QString::number(this->index));
    indexLabel->setFixedSize(25, height);
    image = new ImageLabel(this);
    image->setFixedSize(height, height);
    image->SetPixmap(this->musicInfo.CoverImagePath());

    songName = new QLabel(this);
    songName->setText(this->musicInfo.MusicName());
    songName->setMaximumWidth(150);

    singers = new QLabel(this);
    singers->setText(this->musicInfo.Singers());

    album = new QLabel(this);
    album->setText(this->musicInfo.Album());

    duration = new QLabel(this);
    duration->setText(this->musicInfo.Duration());

    pbMore = new QPushButton(this);
    pbMore->setFixedSize(height, height);
    pbMore->setIcon(QIcon(this->musicInfo.MusicPath()));
}

void PlayListItem::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);

    hLayout->addWidget(indexLabel);
    hLayout->addWidget(image);
    hLayout->addWidget(songName, 3);
    hLayout->addWidget(singers, 2);
    hLayout->addWidget(album, 2);
    hLayout->addWidget(duration, 1);
    hLayout->addWidget(pbMore, 1);
}


