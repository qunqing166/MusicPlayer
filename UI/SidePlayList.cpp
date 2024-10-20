#include "SidePlayList.h"
#include "../Service/MusicInfoService.h"
#include "SidePlayListItem.h"
// #include "../Service/BaseService.h"
// #include "../Dtos/PlayingRecordDto.h"
#include "../Service/PlayListItemService.h"
#include <QDir>
#include <QFile>
#include <QMouseEvent>

SidePlayList::SidePlayList(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("side_play_list");
    ObjectInit();

    //默认为播放列表
    currentList = "_Current";
    //初始化
    UpdateList(currentList);
    WidgetInit();
    DataInit();
    // QJsonObject json = QJsonDocument::fromJson()
}

SidePlayList::~SidePlayList()
{
}

void SidePlayList::UpdateList(const QString &tableName)
{
    this->musicInfos->clear();
    PlayListItemService service(tableName);
    *musicInfos = service.GetPlayingList();

    UpdateMap();
    UpdateWidget();
}

void SidePlayList::UpdateList(const QList<MusicDto> &musicList)
{
    musicInfos->clear();
    *musicInfos = musicList;

    PlayListItemService service("_Current");
    service.Clear();

    foreach (auto m, *musicInfos) {
        // service.Add(m);
        PlayListItemDto a;
        a.setMusicId(m.Id());
        service.Add(a);
    }

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
    emit CurrentPlayListChanged(index, list);
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
    QByteArray jsonStr;
    QFile file(QDir::currentPath() + "/start_up.json");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        // QTextStream in(&file);
        jsonStr = file.readAll();
        file.close();
    }
    else
    {
        qDebug()<<"file: start_up open fault";
        return;
    }

    QJsonObject jsonObj = QJsonDocument::fromJson(jsonStr).object();
    if(jsonObj.contains("current_playing_index"))
    {
        int currentIndex = jsonObj.value("current_playing_index").toInt();
        this->setCurrentRow(currentIndex);
        qDebug()<<"current index:"<<currentIndex;
    }
    else
    {
        qDebug()<<"no key";
    }
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
