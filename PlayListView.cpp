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



    // connect(this, &PlayListView::doubleClicked, this, [&](const QModelIndex &index){
    //     emit PlayMusic(index.row(), musics.at(index.row()));
    // });
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
    musics.push_front(value);
    UpdateWidget();
    BaseService<MusicDto> service;
    service.Add(value);
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
