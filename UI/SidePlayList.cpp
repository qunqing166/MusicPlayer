#include "SidePlayList.h"
#include "SidePlayListItem.h"
#include "../Service/PlayListItemService.h"
#include <QDir>
#include <QFile>
#include <QMouseEvent>
#include "../Service/PlayerController.h"

SidePlayList::SidePlayList(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("side_play_list");
    ObjectInit();

    //初始化
    UpdateList("_Current");
    WidgetInit();
    DataInit();
    // QJsonObject json = QJsonDocument::fromJson()
    // connect(PlayerController::Instance(), &PlayerController::CurrentMusicListChanged,
    //         this, &SidePlayList::OnCurrentMusicListChanged);
    connect(PlayerController::Instance(), &PlayerController::CurrentMusicIndexChanged,
            this, &SidePlayList::setCurrentMusicIndex);
    connect(PlayerController::Instance(), &PlayerController::CurrentMusicChanged, this, [&](const MusicDto &music){
        for(int i = 0; i < musics.count(); i++)
        {
            if(musics.at(i).Id() == music.Id())
            {
                this->setCurrentRow(i);
                break;
            }
        }
    });
}

SidePlayList::~SidePlayList()
{
}

void SidePlayList::UpdateList(const QString &tableName)
{
    //清除原来的数据
    musics.clear();

    PlayListItemService service(tableName);

    if(tableName == "_Current")
    {
        musics = service.GetPlayingList();
        //更新视图
        UpdateWidget();
        //显示正在播放
    }
    else if(tableName == "_Record")
    {
        musics = service.GetPlayingList("UpdateTime");
        UpdateWidget();
    }

    auto music = PlayerController::Instance()->CurrentMusic();
    for(int i = 0; i < musics.count(); i++)
    {
        if(musics.at(i).Id() == music.Id())
        {
            this->setCurrentRow(i);
            break;
        }
    }
}

void SidePlayList::UpdateList(const QList<MusicDto> &musicList)
{
    musics.clear();
    musics = musicList;

    PlayListItemService service("_Current");
    service.Clear();

    foreach (auto m, musics) {
        // service.Add(m);
        PlayListItemDto a;
        a.setMusicId(m.Id());
        service.Add(a);
    }
    UpdateWidget();
}

void SidePlayList::Add(const MusicDto &value)
{

}

QString SidePlayList::PlayingListName() const
{
    return playingListName;
}

void SidePlayList::setCurrentMusicIndex(int index)
{
    currentMusicIndex = index;
}

void SidePlayList::PlayNewList(const QString &name, int index, const QList<MusicDto> &list)
{
    // if(playingListName == name)
    // {
    //     PlayMusic(list.at(index));
    //     for(int i = 0; i < musicInfos->count(); i++)
    //     {
    //         if(musicInfos->at(i).Id() == list.at(index).Id())
    //         {
    //             this->setCurrentRow(i);
    //         }
    //     }
    //     return;
    // }
    // this->playingListName = name;
    // this->UpdateList(list);
    // emit CurrentPlayListChanged(index, list);
}

void SidePlayList::OnCurrentMusicListChanged(const QList<MusicDto> &list, int index)
{
    currentMusicIndex = index;
}

void SidePlayList::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void SidePlayList::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto index = this->indexAt(event->pos());
    this->setCurrentIndex(index);
    PlayerController::Instance()->setCurrentMusicIndex(index.row());
}

void SidePlayList::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void SidePlayList::ObjectInit()
{
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
    for(int i = 0; i < musics.count(); i++)
    {
        auto music = musics.at(i);
        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(200, 60));
        this->addItem(item);
        this->setItemWidget(item, new SidePlayListItem(i + 1, music, this));
    }

    auto crtMusic = PlayerController::Instance()->CurrentMusic();
    for(int i = 0; i < musics.count(); i++)
    {
        if(musics.at(i).Id() == crtMusic.Id())
        {
            this->setCurrentRow(i);
            break;
        }
    }
}

void SidePlayList::Delete(int index)
{
    musics.remove(index);
}

