#pragma once

#include <QObject>
#include "../Dtos/MusicDto.h"

class PlayingListManager:public QObject
{

    Q_OBJECT

    static PlayingListManager* instance;

    QList<MusicDto> musics;

    int index;

    MusicDto currentMusic;

    QString playListName;

public:
    PlayingListManager();

    static PlayingListManager* Instance();

    QList<MusicDto> Musics() const;
    void setMusics(const QList<MusicDto> &value);

    int Index() const;
    void setIndex(int value);

    MusicDto Music() const;
    void setMusic(const MusicDto &value);
    void setMusic(const QList<MusicDto> &list, const int &index);

    QString PlayListName() const;
    void setPlayListName(const QString &value);

signals:

    void MusicListChanged(const QList<MusicDto> &list);
    void MusicIndexChanged(const int &index);
    void CurrentMusicChanged(const MusicDto &music);

};


