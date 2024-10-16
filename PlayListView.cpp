#include "PlayListView.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "PlayListItem.h"
#include "Service/BaseService.h"
#include "Service/MusicInfoService.h"
#include <QJsonArray>
#include "Service/MusicInfoService.h"
#include "Service/MusicService.h"
#include <QEvent>
#include <QMouseEvent>

PlayListView::PlayListView(QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_list_view");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ShowPlayList("我喜欢");
    UpdateWidget();
}

void PlayListView::ShowPlayList(QString playListName)
{
    this->listName = playListName;
    musics.clear();
    // BaseService<MusicDto> service;
    MusicService service;
    musics = service.GetAllByTableName(playListName);
    UpdateWidget();
}

void PlayListView::Add(const MusicDto &value)
{
    //如果已在列表中存在, 直接返回
    foreach(auto m, musics)
    {
        //对本地音乐来说, 路径是唯一的
        if(m.MusicPath() == value.MusicPath())
        {
            qDebug()<<"已存在";
            return;
        }
    }
    //插入至列表最前方
    // musics.push_front(value);
    // UpdateWidget();
    // BaseService<MusicDto> service;
    MusicService service;
    //添加至数据库
    service.Add(value);

    musics = service.GetAllByTableName(this->listName);
    UpdateWidget();
    // service.
}

void PlayListView::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void PlayListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    // qDebug()<<"double clicked";
    auto index = this->indexAt(event->pos());
    this->setCurrentIndex(index);
    // emit PlayMusic(index.row(), musics.at(index.row()));
    emit UpdatePlayingList(this->listName, index.row(), musics);
}

void PlayListView::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void PlayListView::UpdateWidget()
{
    this->clear();
    for(int i = 0; i < musics.count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(200, 60));
        this->addItem(item);
        this->setItemWidget(item, new PlayListItem(musics.at(i), i + 1, this));
    }
}

void PlayListView::OnPlayMusic(const MusicDto &music)
{
    for(int i = 0; i < musics.count(); i++)
    {
        if(musics.at(i).Id() == music.Id())
        {
            this->setCurrentRow(i);
        }
    }
}
