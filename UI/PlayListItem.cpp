#include "PlayListItem.h"
#include <QHBoxLayout>

using namespace Model;
using namespace UI;

Music PlayListItem::getMusicInfo() const
{
    return musicInfo;
}

PlayListItem::PlayListItem(const Music &value, int index, QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->musicInfo = value;
    this->index = index;
    ObjectInit();
    WidgetInit();

    connect(pbMore, &QPushButton::clicked, this, [&](){
        menu = MoreMenu::Instance();//new MoreMenu();
        menu->move(QCursor::pos());
        menu->show();
        connect(menu, &MoreMenu::Operate, this, [&](const MenuOperate &op){
            emit MenuOperateTrigger(this->musicInfo, op);
            menu->disconnect();
            menu->hide();
        });
    });
}


void PlayListItem::ObjectInit()
{
    // static int id = 1;
    int height = 40;
    indexLabel = new QLabel(this);
    indexLabel->setText(QString::number(this->index));
    indexLabel->setFixedSize(25, height);
    indexLabel->setObjectName("PlayListItem_otherLabel");

    image = new ImageLabel(this, musicInfo.CoverImagePath());
    image->setFixedSize(height, height);
    image->SetPixmap(this->musicInfo.CoverImagePath());

    songName = new QLabel(this);
    songName->setText(this->musicInfo.MusicName());
    songName->setContentsMargins(10,0,0,0);

    songName->setObjectName("PlayListItem_musicName");

    singers = new QLabel(this);
    singers->setText(this->musicInfo.Singers());

    singers->setObjectName("PlayListItem_otherLabel");

    album = new QLabel(this);
    album->setText(this->musicInfo.Album());
    album->setObjectName("PlayListItem_otherLabel");

    duration = new QLabel(this);
    duration->setText(this->musicInfo.Duration());
    duration->setObjectName("PlayListItem_otherLabel");

    pbMore = new QPushButton(this);
    pbMore->setFixedSize(height, height);
    pbMore->setIcon(QIcon(this->musicInfo.MusicPath()));

    pbMore->setObjectName("list_more_btn");
    pbMore->setIcon(QIcon(":/scr/icon/more.png"));

    if(musicInfo.Singers().isEmpty())
    {
        singers->hide();
        album->hide();
    }
}

void PlayListItem::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    // hLayout->setContentsMargins(0,0,0,0);
    this->setLayout(hLayout);
    hLayout->setSpacing(0);
    hLayout->addWidget(indexLabel);
    hLayout->addWidget(image);
    if(this->musicInfo.Singers().isEmpty())
    {
        hLayout->addWidget(songName, 11);
    }
    else
    {
        hLayout->addWidget(songName, 4);
        hLayout->addWidget(new QLabel(this), 1);
        hLayout->addWidget(singers, 3, Qt::AlignLeft);
        hLayout->addWidget(album, 3);
    }

    hLayout->addWidget(duration, 1);
    hLayout->addWidget(new QLabel(this), 1);
    hLayout->addWidget(pbMore, 1);
}


