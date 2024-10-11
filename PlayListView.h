#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QListWidget>
#include "DataInfo/MusicInfo.h"

class PlayListView:public QListWidget
{
    Q_OBJECT

    QList<MusicInfo> *musicInfos;

public:
    PlayListView(QWidget *parent = nullptr);
    void ShowPlayList(QString playListName);

private:
    void ObjectInit();
    void WidgetInit();

signals:
    void PlayMusic(const MusicInfo &info);
};

#endif // PLAYLISTVIEW_H
