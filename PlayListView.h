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

private:
    void ObjectInit();
    void WidgetInit();
    void DataInit();
};

#endif // PLAYLISTVIEW_H
