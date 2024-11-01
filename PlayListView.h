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

    //获取音乐控制器，播放音乐
    void PlayMusic();
    //相应菜单操作
    void OnMenuOperateTrigger(const MusicDto &music, const MenuOperate &op);

};

#endif // PLAYLISTVIEW_H
