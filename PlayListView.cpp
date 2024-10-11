#include "PlayListView.h"
#include <QHBoxLayout>
// #include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include "PlayListItem.h"
#include "Service/MusicInfoService.h"
#include <QJsonArray>
#include "Service/MusicInfoService.h"
// #include "Service/BaseService.h"
// #include "Service/PlayListInfoService.h"

PlayListView::PlayListView(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_list_view");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ObjectInit();
    ShowPlayList("我喜欢");
    WidgetInit();

    connect(this, &PlayListView::doubleClicked, this, [&](const QModelIndex &index){
        emit PlayMusic(musicInfos->at(index.row()));
    });
}

void PlayListView::ShowPlayList(QString playListName)
{
    MusicInfoService service;
    Response<QList<MusicInfo>> m = service.GetAll(playListName, PlayList);
    musicInfos->clear();
    this->clear();
    *musicInfos = m.Result();
    WidgetInit();
}

void PlayListView::ObjectInit()
{
    musicInfos = new QList<MusicInfo>();
}

void PlayListView::WidgetInit()
{
    for(int i = 0; i < musicInfos->count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(200, 60));
        this->addItem(item);
        this->setItemWidget(item, new PlayListItem(musicInfos->at(i), this));
    }
}
