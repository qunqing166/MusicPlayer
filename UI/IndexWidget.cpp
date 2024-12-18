#include "IndexPlayListItem.h"
#include "IndexWidget.h"

#include <QHBoxLayout>
#include <QLabel>
// #include "MoreMenu.h"
#include <QVBoxLayout>
#include "ImageLabel.h"
#include "PlayListView.h"
#include "../Service/PlayListItemService.h"
#include "../Service/PlayListService.h"
#include "../Service/PlayerController.h"

using namespace Model;
using namespace Service;

IndexWidget::IndexWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("IndexWidget");

    ObjectInit();
    WidgetInit();
    SetCurrentMusicInfo(PlayerController::Instance()->CurrentMusic());
    SetCurrentPlayList();
    SetPlayList();
    UpdatePlayListWidget();

    connect(PlayerController::Instance(), &PlayerController::CurrentMusicChanged, this, &IndexWidget::SetCurrentMusicInfo);
}

void IndexWidget::SetCurrentMusicInfo(const Music &music)
{
    imageLabel->SetPixmap(music.CoverImagePath());
    label1->setText(QString("歌名: %1").arg(music.MusicName()));
    label2->setText(QString("作者: ").arg(music.Singers()));
    label3->setText(QString("歌词: 当前无歌词"));
}

void IndexWidget::SetCurrentPlayList()
{
    PlayListItemService service("_Current");
    QList<Music> musics = service.GetPlayingList();
    playList->SetPlayList(musics);
}

void IndexWidget::OnCurrentPlayListChanged(int index, const QList<Music> &list)
{
    playList->SetPlayList(list);
    playList->setCurrentRow(index);
}


void IndexWidget::SetPlayList()
{
    PlayListService service;
    myPlayList = service.GetPlayListFromUser();
    UpdatePlayListWidget();
}

void IndexWidget::ObjectInit()
{
    QFont font;
    font.setPixelSize(15);

    imageLabel = new ImageLabel(this);

    label1 = new QLabel("歌名", this);
    label1->setObjectName("IndexWidget_MusicName");
    label2 = new QLabel("作者", this);
    label1->setObjectName("IndexWidget_Singer");
    label3 = new QLabel("歌词: 当前无歌词", this);
    label1->setObjectName("IndexWidget_text");
    playList = new PlayListView("_Current", this);
    listWidget = new QListWidget(this);

    label1->setFont(font);
    label2->setFont(font);
    label3->setFont(font);
}

void IndexWidget::WidgetInit()
{

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);

    vLayout->addWidget(new QLabel("正在播放  >", this));
    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    int imageSize = 150;

    hLayout1->addWidget(imageLabel);
    imageLabel->setFixedSize(imageSize, imageSize);
    imageLabel->SetRadius(15);
    imageLabel->SetPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp");

    QVBoxLayout *vLayout1_1 = new QVBoxLayout(this);
    vLayout1_1->setAlignment(Qt::AlignTop);
    hLayout1->addLayout(vLayout1_1);

    vLayout1_1->addWidget(label1);
    vLayout1_1->addWidget(label2);
    vLayout1_1->addWidget(label3);

    QFrame *frame1 = new QFrame(this);
    frame1->setStyleSheet("background-color:rgb(205, 207, 208);");
    frame1->setFixedHeight(1);
    vLayout->addWidget(frame1);

    vLayout->addWidget(new QLabel("歌单  >", this));


    vLayout->addWidget(listWidget);
    listWidget->setObjectName("IndexWidget_listWidget");
    listWidget->setFlow(QListView::LeftToRight);
    listWidget->setFixedHeight(200);

    QFrame *frame2 = new QFrame(this);
    frame2->setStyleSheet("background-color:rgb(205, 207, 208);");
    frame2->setFixedHeight(1);
    vLayout->addWidget(frame2);

    vLayout->addWidget(new QLabel("正在播放歌单  >", this));

    playList->ResetHeight();
    vLayout->addWidget(playList, Qt::AllButtons);

}

void IndexWidget::UpdatePlayListWidget()
{
    listWidget->clear();
    for(int i = 0; i < this->myPlayList.count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(listWidget);
        IndexPlayListItem *itemWidget = new IndexPlayListItem(this->myPlayList.at(i), this);
        listWidget->addItem(item);
        listWidget->setItemWidget(item, itemWidget);
        item->setSizeHint(QSize(itemWidget->Width() + 20, itemWidget->Width() + 20));
        
        connect(itemWidget, &IndexPlayListItem::OpenPlayList, this, [&](const PlayList &info){
            emit OpenPlayList(info);
        });
    }
}
