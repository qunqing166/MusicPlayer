#ifndef PLAYLISTCONTENTVIEW_H
#define PLAYLISTCONTENTVIEW_H

#include <QWidget>
#include "../Model/PlayList.h"
#include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "PlayListView.h"
#include "PlayListEditor.h"
#include <QPointer>

//歌单内容界面, 包括歌单创建信息和包括的歌曲列表
class PlayListContentView:public QWidget
{
    Q_OBJECT

    //界面
    ImageLabel *imageLabel;
    QLabel *playListNameLabel;
    ImageLabel *userImage;
    QLabel *userNameLabel;
    QLabel *createTimeLabel;
    QPushButton *pbPlay;
    QPushButton *pbEdit;
    PlayListView *playListView;
    QPushButton *pbAdd;
    //歌单信息编辑器
    QPointer<PlayListEditor> playListEditor;
    //歌单数据
    Model::PlayList playList;

public:

    PlayListContentView(QWidget *parent = nullptr);
    
    void ShowPlayList(const Model::PlayList &info);

    PlayListView *getPlayListView() const;

private:
    void ObjectInit();
    void WidgetInit();
    void OnPbAddClicked();
    void OnEditPlayList(const Model::PlayList &info);
    Q_PROPERTY(PlayListView *playListView READ getPlayListView CONSTANT FINAL)

signals:
    void PlayListDataChanged();

};

#endif // PLAYLISTCONTENTVIEW_H
