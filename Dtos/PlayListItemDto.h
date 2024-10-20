#pragma once

#include "BaseDto.h"

class PlayListItemDto:public BaseDto
{
    Q_OBJECT

    int musicId;

    Q_PROPERTY(int MusicId READ MusicId WRITE setMusicId NOTIFY MusicIdChanged FINAL)

public:
    PlayListItemDto();

    const static QString TableName;

    int MusicId(){return musicId;}
    void setMusicId(int value){musicId = value;}

signals:
    void MusicIdChanged();
};

inline const QString PlayListItemDto::TableName = "PlayList_";
