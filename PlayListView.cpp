#include "PlayListView.h"
#include <QHBoxLayout>
// #include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include "PlayListItem.h"
#include "Service/MusicInfoService.h"
#include <QJsonArray>
#include "Service/MusicInfoService.h"

PlayListView::PlayListView(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_list_view");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ObjectInit();
    DataInit();
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

void PlayListView::DataInit()
{
    IBaseService<MusicInfo> *service = new MusicInfoService();
    Response<QList<MusicInfo>> m = service->GetAll();
    *musicInfos = m.Result();
}
