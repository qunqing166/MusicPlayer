#include "PlayListView.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Dtos/PlayListItemDto.h"
#include "PlayListItem.h"
#include <QJsonArray>
#include "Service/PlayListItemService.h"
#include <QEvent>
#include <QMouseEvent>

PlayListView::PlayListView(const QString &listName, QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_list_view");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    this->listName = listName;

    ShowPlayList(listName);
    UpdateWidget();
}

void PlayListView::ShowPlayList(QString playListName)
{
    this->listName = playListName;
    musics.clear();

    PlayListItemService service(playListName);
    musics = service.GetPlayingList();
    UpdateWidget();
}

void PlayListView::Add(const MusicDto &value)
{
    BaseService<MusicDto> service;
    PlayListItemService service1(this->ListName());

    //查看数据库中是否保存过该音乐, 通过路径判断是否冲突
    if(!service.IsExist(QString("MusicPath = '%1'").arg(value.MusicPath())))
    {
        qDebug()<<"存在于数据库";
        //数据库中没有就加入数据库
        service.Add(value);
    }
    //获取在数据库中的信息
    MusicDto music = service.GetOneByParameter(QString("MusicPath = '%1'").arg(value.MusicPath()));
    //判断歌单内是否保存过
    if(service1.IsExist(QString("MusicId = %1").arg(music.Id())))
    {
        //有就不做处理
        return;
    }
    else
    {
        qDebug()<<"不存在于歌单";
        //添加至歌单
        PlayListItemDto aa;
        aa.setMusicId(music.Id());
        service1.Add(aa);
    }
    //刷新数据
    ShowPlayList(this->listName);
}

void PlayListView::OnPlayList()
{
    emit UpdatePlayingList(this->listName, 0, musics);
}

void PlayListView::ResetHeight()
{
    this->setFixedHeight(70 * this->count());
}

void PlayListView::SetPlayList(const QList<MusicDto> &list)
{
    this->musics = list;
    UpdateWidget();
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
