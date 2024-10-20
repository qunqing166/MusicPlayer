#ifndef PLAYLISTCONTENTVIEW_H
#define PLAYLISTCONTENTVIEW_H

#include <QWidget>
#include "Dtos/PlayListDto.h"
#include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "PlayListView.h"
#include "UI/PlayListEditor.h"
#include <QPointer>

//歌单内容界面, 包括歌单创建信息和包括的歌曲列表
class PlayListContentView:public QWidget
{
    Q_OBJECT

    ImageLabel *imageLabel;
    QLabel *sheetTitleLabel;
    ImageLabel *userImage;
    QLabel *userNameLabel;
    QLabel *createTimeLabel;
    QPushButton *pbPlay;
    QPushButton *pbEdit;
    PlayListView *playListView;
    QPushButton *pbAdd;

    PlayListDto playList;

    QPointer<PlayListEditor> playListEditor;

public:
    PlayListContentView(QWidget *parent = nullptr);
    PlayListContentView(const PlayListDto &info, QWidget *parent = nullptr);
    void ShowPlayList(const PlayListDto &info);

    PlayListView *getPlayListView() const;

private:
    void ObjectInit();
    void WidgetInit();
    void OnPbAddClicked();
    void OnEditPlayList(const PlayListDto &info);
    Q_PROPERTY(PlayListView *playListView READ getPlayListView CONSTANT FINAL)

signals:
    void PlayListDataChanged();

};

#endif // PLAYLISTCONTENTVIEW_H
