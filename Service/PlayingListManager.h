#pragma once

#include <QObject>
#include "../Model/Music.h"

class PlayingListManager:public QObject
{

    Q_OBJECT

    static PlayingListManager* instance;

    QList<Model::Music> musics;

    int index;

    Model::Music currentMusic;

    QString playListName;

public:
    PlayingListManager();

    static PlayingListManager* Instance();

    QList<Model::Music> Musics() const;
    void setMusics(const QList<Model::Music> &value);

    int Index() const;
    void setIndex(int value);

    Model::Music getMusic() const;
    void setMusic(const Model::Music &value);
    void setMusic(const QList<Model::Music> &list, const int &index);

    QString PlayListName() const;
    void setPlayListName(const QString &value);

signals:

    void MusicListChanged(const QList<Model::Music> &list);
    void MusicIndexChanged(const int &index);
    void CurrentMusicChanged(const Model::Music &music);

};


