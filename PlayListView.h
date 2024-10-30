#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QListWidget>
#include "Dtos/MusicDto.h"
#include "UI/MoreMenu.h"

//歌曲列表显示的列表
class PlayListView:public QListWidget
{
    Q_OBJECT

    QString listName;
    //歌单列表
    QList<MusicDto> musics;

public:
    PlayListView(const QString &listName, QWidget *parent = nullptr);
    //根据分类名查询歌单列表
    void ShowPlayList(QString playListName);
    void Add(const MusicDto &value);
    void Delete(int id);
    QString ListName() const{return listName;}
    QList<MusicDto> Musics() const{return musics;}

    void OnPlayList();
    void ResetHeight();
    void SetPlayList(const QList<MusicDto> &list);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    void ObjectInit();
    void UpdateWidget();

    void PlayMusic();

    void OnMenuOperateTrigger(const MusicDto &music, const MenuOperate &op);

// public slots:
//     void OnPlayMusic(const MusicDto &music);

// signals:
//     //播放音乐, 传入音乐信息
//     void UpdatePlayingList(const QString &listName, int index, const QList<MusicDto> &list);
};

#endif // PLAYLISTVIEW_H
