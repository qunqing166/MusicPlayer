#pragma once

#include "Base.h"

namespace Model
{

class PlayListItem:public Base
{
    Q_OBJECT

    int musicId;

    Q_PROPERTY(int MusicId READ MusicId WRITE setMusicId NOTIFY MusicIdChanged FINAL)

public:
    PlayListItem(){}

    const static QString TableName;

    int MusicId(){return musicId;}
    void setMusicId(int value){musicId = value;}

signals:
    void MusicIdChanged();
};

inline const QString PlayListItem::TableName = "PlayList_";

}
