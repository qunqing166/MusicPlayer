#include "PlayListItem.h"
#include "PlayListView.h"
#include "Service/PlayListItemService.h"
#include "Service/PlayerController.h"
#include <QMouseEvent>

using namespace Service;

PlayListView::PlayListView(const QString &listName, QWidget *parent):QListWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("PlayListView");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    this->listName = listName;

    ShowPlayList(listName);
    UpdateWidget();
    
    connect(PlayerController::Instance(), &PlayerController::CurrentMusicChanged, this, [&](const Model::Music &music){
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

void PlayListView::ShowPlayList(QString playListName)
{
    this->listName = playListName;
    musics.clear();

    PlayListItemService service(playListName);
    musics = service.GetPlayingList();
    UpdateWidget();
}

void PlayListView::Add(const Model::Music &value)
{
    BaseService<Model::Music> service;
    PlayListItemService service1(this->ListName());

    //查看数据库中是否保存过该音乐, 通过路径判断是否冲突
    if(!service.IsExist("MusicPath", value.MusicPath()))
    {
        qDebug()<<"存在于数据库";
        //数据库中没有就加入数据库
        service.Add(value);
    }
    //获取在数据库中的信息
    Model::Music music = service.GetOneByParameter("MusicPath", value.MusicPath());
    //判断歌单内是否保存过
    if(service1.IsExist("MusicId", music.Id()))
    {
        //有就不做处理
        return;
    }
    else
    {
        qDebug()<<"不存在于歌单";
        //添加至歌单
        Model::PlayListItem aa;
        aa.setMusicId(music.Id());
        service1.Add(aa);
    }
    //刷新数据
    ShowPlayList(this->listName);
}

void PlayListView::OnPlayList()
{
    if(this->musics.count() > 0)
    {
        PlayerController::Instance()->setCurrentMusicList(musics, 0);
        setCurrentRow(0);
    }
}

void PlayListView::ResetHeight()
{
    this->setFixedHeight(70 * this->count());
}

void PlayListView::SetPlayList(const QList<Model::Music> &list)
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
    auto index = this->indexAt(event->pos());

    this->setCurrentRow(index.row());

    this->PlayMusic();
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
        UI::PlayListItem *itemWidget = new UI::PlayListItem(musics.at(i), i + 1, this);
        this->setItemWidget(item, itemWidget);

        connect(itemWidget, &UI::PlayListItem::MenuOperateTrigger, this, &PlayListView::OnMenuOperateTrigger);
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

void PlayListView::PlayMusic()
{
    PlayerController *controller = PlayerController::Instance();
    controller->setCurrentMusicList(this->musics, this->currentRow());
}

void PlayListView::OnMenuOperateTrigger(const Model::Music &music, const MenuOperate &op)
{
    if(op == Play)
    {
        for(int i = 0; i < musics.count(); i++)
        {
            if(music.Id() == musics.at(i).Id())
            {
                setCurrentRow(i);
                break;
            }
        }

        this->PlayMusic();
    }
    else if(op == AddToNext)
    {
        PlayerController::Instance()->AddToPlayList(music);
    }
    else if(op == Remove)
    {
        PlayListItemService service(this->ListName());
        service.DeleteByParameter("MusicId", music.Id());
        ShowPlayList(this->ListName());
    }
}
