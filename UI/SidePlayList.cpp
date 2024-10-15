#include "SidePlayList.h"
#include "../Service/MusicInfoService.h"
#include "SidePlayListItem.h"
// #include "../Service/BaseService.h"
// #include "../Dtos/PlayingRecordDto.h"
#include "../Service/PlayingRecordService.h"
#include <QMouseEvent>

SidePlayList::SidePlayList(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    ObjectInit();
    // DataInit();
    UpdateList("CurrentPlayList");
    WidgetInit();

    // connect(this, &QListWidget::doubleClicked, this, [&](const QModelIndex &index){
    //     emit PlayMusic(index.row(), musicInfos->at(index.row()));
    // });
}

void SidePlayList::UpdateList(const QString &tableName)
{
    this->musicInfos->clear();
    PlayingRecordService service(tableName);
    *musicInfos = service.GetPlayingList();

    UpdateMap();
    UpdateWidget();
}

void SidePlayList::UpdateList(const QList<MusicDto> &musicList)
{
    musicInfos->clear();
    *musicInfos = musicList;

    UpdateMap();
    UpdateWidget();
}

void SidePlayList::Add(const MusicDto &value)
{
    if(musicsMap->contains(value.Id()))
    {
        //如果歌曲在列表中, 将其更新到顶部
        int index = musicsMap->value(value.Id());
        musicInfos->remove(index);      //删除原来位置的数据
        musicInfos->push_front(value);  //插入第一位
    }
    else
    {
        musicInfos->push_front(value);
    }
    UpdateMap();
}

QString SidePlayList::PlayingListName() const
{
    return playingListName;
}

void SidePlayList::PlayNewList(const QString &name, int index, const QList<MusicDto> &list)
{
    if(playingListName == name)
    {
        PlayMusic(list.at(index));
        for(int i = 0; i < musicInfos->count(); i++)
        {
            if(musicInfos->at(i).Id() == list.at(index).Id())
            {
                this->setCurrentRow(i);
            }
        }
        return;
    }
    this->playingListName = name;
    this->UpdateList(list);
}

void SidePlayList::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void SidePlayList::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto index = this->indexAt(event->pos());
    this->setCurrentIndex(index);
    emit PlayMusic(musicInfos->at(index.row()));
}

void SidePlayList::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void SidePlayList::ObjectInit()
{
    musicInfos = new QList<MusicDto>();
    musicsMap = new QMap<int, int>();
}

void SidePlayList::WidgetInit()
{

}

void SidePlayList::DataInit()
{
    // BaseService<PlayingRecordDto> service;

    // PlayingRecordService service(PlayingCurrent);

    // // *musicInfos = service.GetPlayingList();

    // // MusicInfoService service;
    // auto infos = service.GetPlayingList();
    // *musicInfos = infos;

    // for(int i = 0; i < infos.count(); i++)
    // {
    //     QListWidgetItem *item = new QListWidgetItem(this);
    //     item->setSizeHint(QSize(200, 60));
    //     this->addItem(item);
    //     this->setItemWidget(item, new SidePlayListItem(musicInfos->at(i), this));
    // }
}

void SidePlayList::UpdateWidget()
{
    this->clear();
    for(int i = 0; i < musicInfos->count(); i++)
    {
        auto music = musicInfos->at(i);
        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(200, 60));
        this->addItem(item);
        this->setItemWidget(item, new SidePlayListItem(music, this));
    }
}

void SidePlayList::Delete(int index)
{
    musicInfos->remove(index);
    UpdateMap();
}

void SidePlayList::UpdateMap()
{
    //重置map
    musicsMap->clear();
    for(int i = 0; i < musicInfos->count(); i++)
    {
        musicsMap->insert(musicInfos->at(i).Id(), i);
    }
}
