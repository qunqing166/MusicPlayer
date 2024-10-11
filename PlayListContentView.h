#ifndef PLAYLISTCONTENTVIEW_H
#define PLAYLISTCONTENTVIEW_H

#include <QWidget>
#include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "DataInfo/PlayListInfo.h"
#include "PlayListView.h"

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

public:
    PlayListContentView(QWidget *parent = nullptr);
    void ShowPlayList(const PlayListInfo &info);

    PlayListView *getPlayListView() const;

private:
    void ObjectInit();
    void WidgetInit();
    Q_PROPERTY(PlayListView *playListView READ getPlayListView CONSTANT FINAL)
};

#endif // PLAYLISTCONTENTVIEW_H
